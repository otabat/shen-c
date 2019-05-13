#include "reader.h"

static size_t reader_buffer_allocation_size = 4;

static inline size_t get_reader_buffer_allocation_size ()
{
  return reader_buffer_allocation_size;
}

static void append_read_kl_object (KLObject* object,
                                   KLObject** head_list_object_ref,
                                   KLObject** tail_list_object_ref)
{
  KLObject* head_list_object = *head_list_object_ref;
  KLObject* tail_list_object = *tail_list_object_ref;
  KLObject* list_object = CONS(object, NULL);

  if (is_null(tail_list_object)) {
    head_list_object = list_object;
  } else {
    set_tail_kl_list(tail_list_object, list_object);
  }

  tail_list_object = list_object;
  *head_list_object_ref = head_list_object;
  *tail_list_object_ref = tail_list_object;
}

static KLObject* read_string_string (FILE* file)
{
  char c;
  KLObject* string_object = NULL;
  bool is_string_opened = false;
  size_t string_buffer_allocation_size = get_reader_buffer_allocation_size();
  char* string_buffer = malloc(string_buffer_allocation_size);
  
  string_buffer[0] = '\0';

  while (true) {
    c = (char)read_byte_with_buffer(file);

    if (c == -1)
      throw_kl_exception("String not closed");
    else if (is_double_quotation_character(c)) {
      if (is_string_opened) {
        size_t string_length = strlen(string_buffer);
        char* string = malloc(string_length + 1);

        strncpy(string, string_buffer, string_length);
        string[string_length] = '\0';
        string_object = create_kl_string_with_intern(string);

        break;
      } else
        is_string_opened = true;
    } else
      string_buffer = append_character_to_string(string_buffer,
                                                 &string_buffer_allocation_size,
                                                 c);
  }

  return string_object;
}

static KLObject* read_string_symbol_and_boolean (FILE* file)
{
  char c;
  KLObject* symbol_or_boolean_object = NULL;
  size_t symbol_name_buffer_allocation_size = get_reader_buffer_allocation_size();
  char* symbol_name_buffer = malloc(symbol_name_buffer_allocation_size);

  symbol_name_buffer[0] = '\0';

  while (true) {
    c = (char)read_byte_with_buffer(file);

    if (is_symbol_character(c))
      symbol_name_buffer =
        append_character_to_string(symbol_name_buffer,
                                   &symbol_name_buffer_allocation_size,
                                   c);
    else {
      size_t symbol_name_length = strlen(symbol_name_buffer);
      char* symbol_name = malloc(symbol_name_length + 1);

      strncpy(symbol_name, symbol_name_buffer, symbol_name_length);
      symbol_name[symbol_name_length] = '\0';

      KLObject* string_object = create_kl_string_with_intern(symbol_name);

      if (is_kl_string_equal(string_object, get_true_string_object()))
        symbol_or_boolean_object = get_true_boolean_object();
      else if (is_kl_string_equal(string_object, get_false_string_object()))
        symbol_or_boolean_object = get_false_boolean_object();
      else {
        KLObject* symbol_object = lookup_symbol_table(string_object);

        if (is_null(symbol_object)) {
          symbol_or_boolean_object = create_kl_symbol(string_object);
          extend_symbol_table(string_object, symbol_or_boolean_object);
        } else
          symbol_or_boolean_object = symbol_object;
      }

      unread_byte_with_buffer(c);
      
      break;
    }
  }

  return symbol_or_boolean_object;
}

static KLObject* read_string_number (FILE* file)
{
  char c;
  KLObject* number_object = NULL;
  bool is_numeric_character_found = false;
  bool is_dot_character_found = false;
  size_t plus_character_count = 0;
  size_t minus_character_count = 0;
  size_t number_string_buffer_allocation_size =
    get_reader_buffer_allocation_size();
  char* number_string_buffer = malloc(number_string_buffer_allocation_size);

  number_string_buffer[0] = '\0';

  while (true) {
    c = (char)read_byte_with_buffer(file);

    if (is_plus_character(c) && !is_numeric_character_found)
      ++plus_character_count;
    else if (is_minus_character(c) && !is_numeric_character_found)
      ++minus_character_count;
    else if (is_numeric_character(c))
      is_numeric_character_found = true;
    else if (is_dot_character(c) && !is_dot_character_found) {
      is_dot_character_found = true;

      char next_c = (char)read_byte_with_buffer(file);

      unread_byte_with_buffer(next_c);

      if (!is_numeric_character(next_c)) {
        unread_byte_with_buffer(c);

        continue;
      }
    } else {
      char* number_string;
      size_t number_string_length = strlen(number_string_buffer);

      if (minus_character_count == 0) {
        size_t signless_number_string_length =
          number_string_length - plus_character_count;

        number_string = malloc(signless_number_string_length + 1);

        for (size_t i = 0; i < signless_number_string_length; ++i)
          number_string[i] = *(number_string_buffer + plus_character_count + i);
        
        number_string[signless_number_string_length] = '\0';
      } else {
        size_t sign_count = plus_character_count + minus_character_count;
        size_t single_signed_number_string_length =
          number_string_length - sign_count + 1;

        number_string = malloc(single_signed_number_string_length + 1);

        for (size_t i = 1; i < single_signed_number_string_length; ++i)
          number_string[i] = *(number_string_buffer + sign_count + i - 1);

        number_string[0] = (minus_character_count % 2 == 0) ? '+' : '-';
        number_string[single_signed_number_string_length] = '\0';
      }

      if (is_dot_character_found)
        number_object = create_kl_number_d(atof(number_string));
      else
        number_object = create_kl_number_l(atol(number_string));
      
      unread_byte_with_buffer(c);

      break;
    }

    number_string_buffer =
      append_character_to_string(number_string_buffer,
                                 &number_string_buffer_allocation_size,
                                 c);
  }

  return number_object;
}

static KLObject* read_string_symbol_and_number_and_boolean (FILE* file)
{
  char c;
  KLObject* object = NULL;
  size_t lookahead_buffer_allocation_size = get_reader_buffer_allocation_size();
  char* lookahead_buffer = malloc(lookahead_buffer_allocation_size);

  lookahead_buffer[0] = '\0';

  while (true) {
    c = (char)read_byte_with_buffer(file);

    if (is_plus_character(c)) {
      lookahead_buffer =
        append_character_to_string(lookahead_buffer,
                                   &lookahead_buffer_allocation_size,
                                   c);

      continue;
    } else if (is_minus_character(c)) {
      lookahead_buffer =
        append_character_to_string(lookahead_buffer,
                                   &lookahead_buffer_allocation_size,
                                   c);

      continue;
    } else if (is_dot_character(c)) {
      lookahead_buffer =
        append_character_to_string(lookahead_buffer,
                                   &lookahead_buffer_allocation_size,
                                   c);

      char next_c = (char)read_byte_with_buffer(file);

      lookahead_buffer =
        append_character_to_string(lookahead_buffer,
                                   &lookahead_buffer_allocation_size,
                                   next_c);
      unread_bytes_with_buffer(lookahead_buffer);
      object = ((is_numeric_character(next_c)) ?
                read_string_number(file) : read_string_symbol_and_boolean(file));

      break;
    } else if (is_numeric_character(c)) {
      lookahead_buffer =
        append_character_to_string(lookahead_buffer,
                                   &lookahead_buffer_allocation_size,
                                   c);
      unread_bytes_with_buffer(lookahead_buffer);
      object = read_string_number(file);

      break;
    } else {
      lookahead_buffer =
        append_character_to_string(lookahead_buffer,
                                   &lookahead_buffer_allocation_size,
                                   c);
      unread_bytes_with_buffer(lookahead_buffer);
      object = read_string_symbol_and_boolean(file);

      break;
    }
}

  return object;
}

static KLObject* read_string_helper (FILE* file, int list_level)
{
  char c;
  KLObject* object = NULL;
  KLObject* head_list_object = NULL;
  KLObject* tail_list_object = NULL;

  while ((c = (char)read_byte_with_buffer(file)) != -1) {
    if (is_whitespace_character(c)) {
      // Do nothing
    } else if (is_left_parenthesis_character(c)) {
      object = read_string_helper(file, list_level + 1);

      if (list_level == 0)
        return object;
      
      append_read_kl_object(object, &head_list_object, &tail_list_object);
    } else if (is_right_parenthesis_character(c)) {
      if (is_null(head_list_object)) {
        head_list_object = EL;
        tail_list_object = head_list_object;
      } else
        set_tail_kl_list(tail_list_object, EL);

      return head_list_object;
    } else if (is_double_quotation_character(c)) {
      unread_byte_with_buffer(c);
      object = read_string_string(file);

      if (list_level == 0)
        return object;

      append_read_kl_object(object, &head_list_object, &tail_list_object);

      continue;
    } else if (is_numeric_character(c)) {
      unread_byte_with_buffer(c);
      object = read_string_number(file);

      if (list_level == 0)
        return object;

      append_read_kl_object(object, &head_list_object, &tail_list_object);

      continue;
    } else if (is_symbol_character(c)) {
      unread_byte_with_buffer(c);
      object = read_string_symbol_and_number_and_boolean(file);

      if (list_level == 0)
        return object;

      append_read_kl_object(object, &head_list_object, &tail_list_object);

      continue;
    } else
      throw_kl_exception("No parsing rules found");
  }

  return NULL;
}

KLObject* read_string (KLObject* stream_object)
{
  return read_string_helper(get_kl_stream_file(stream_object), 0);
}
