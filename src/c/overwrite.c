#include "overwrite.h"

KLObject* exit_symbol_object;
KLObject* hash_symbol_object;
KLObject* is_symbol_symbol_object;
KLObject* is_integer_symbol_object;
KLObject* is_boolean_symbol_object;
KLObject* is_variable_symbol_object;
KLObject* not_symbol_object;
KLObject* value_slash_or_symbol_object;
KLObject* get_absvector_element_slash_or_symbol_object;
KLObject* map_symbol_object;
KLObject* reverse_symbol_object;
KLObject* shen_is_numbyte_symbol_object;
KLObject* shen_byte_to_digit_symbol_object;
KLObject* read_file_as_charlist_symbol_object;
KLObject* shen_pvar_symbol_object;
KLObject* shen_is_pvar_symbol_object;

extern KLObject* get_exit_symbol_object (void);
extern KLObject* get_hash_symbol_object (void);
extern KLObject* get_is_symbol_symbol_object (void);
extern KLObject* get_is_integer_symbol_object (void);
extern KLObject* get_is_boolean_symbol_object (void);
extern KLObject* get_is_variable_symbol_object (void);
extern KLObject* get_not_symbol_object (void);
extern KLObject* get_value_slash_or_symbol_object (void);
extern KLObject* get_get_absvector_element_slash_or_symbol_object (void);
extern KLObject* get_map_symbol_object (void);
extern KLObject* get_reverse_symbol_object (void);
extern KLObject* get_shen_is_numbyte_symbol_object (void);
extern KLObject* get_shen_byte_to_digit_symbol_object (void);
extern KLObject* get_read_file_as_charlist_symbol_object (void);
extern KLObject* get_shen_pvar_symbol_object (void);
extern KLObject* get_shen_is_pvar_symbol_object (void);

static inline void initialize_exit_symbol_object (void)
{
  exit_symbol_object = create_kl_symbol("exit");
}

static inline void register_exit_symbol_object (void)
{
  initialize_exit_symbol_object();
  extend_symbol_name_table("exit", get_exit_symbol_object());
}

static inline KLObject* primitive_function_exit (KLObject* function_object,
                                                 Vector* arguments,
                                                 Environment* function_environment,
                                                 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  if (is_kl_number_l(objects[0]))
    exit(get_kl_number_number_l(objects[0]));

  throw_kl_exception("Argument of exit function should be a number");

  return NULL;
}

static inline void register_primitive_kl_function_exit (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_exit);

  set_kl_symbol_function(exit_symbol_object, function_object);
}

static inline void initialize_hash_symbol_object (void)
{
  hash_symbol_object = create_kl_symbol("hash");
}

static inline void register_hash_symbol_object (void)
{
  initialize_hash_symbol_object();
  extend_symbol_name_table("hash", get_hash_symbol_object());
}

static inline KLObject* primitive_function_hash (KLObject* function_object,
                                                 Vector* arguments,
                                                 Environment* function_environment,
                                                 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return kl_object_bounded_hash(objects[0], objects[1]);
}

static inline void register_primitive_kl_function_hash (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_hash);

  set_kl_symbol_function(get_hash_symbol_object(), function_object);
}

static inline void initialize_is_symbol_symbol_object (void)
{
  is_symbol_symbol_object = create_kl_symbol("symbol?");
}

static inline void register_is_symbol_symbol_object (void)
{
  initialize_is_symbol_symbol_object();
  extend_symbol_name_table("symbol?", get_is_symbol_symbol_object());
}

static inline KLObject* primitive_function_is_symbol
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  if (is_kl_symbol(objects[0]))
    return get_true_boolean_object();

  return get_false_boolean_object();
}

static inline void register_primitive_kl_function_is_symbol (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_is_symbol);

  set_kl_symbol_function(get_is_symbol_symbol_object(), function_object);
}

static inline void initialize_is_boolean_symbol_object (void)
{
  is_boolean_symbol_object = create_kl_symbol("boolean?");
}

static inline void register_is_boolean_symbol_object (void)
{
  initialize_is_boolean_symbol_object();
  extend_symbol_name_table("boolean?", get_is_boolean_symbol_object());
}

static inline KLObject* primitive_function_is_boolean
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  if (is_kl_boolean(objects[0]))
    return get_true_boolean_object();

  return get_false_boolean_object();
}

static inline void register_primitive_kl_function_is_boolean (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_is_boolean);

  set_kl_symbol_function(get_is_boolean_symbol_object(), function_object);
}

static inline void initialize_is_integer_symbol_object (void)
{
  is_integer_symbol_object = create_kl_symbol("integer?");
}

static inline void register_is_integer_symbol_object (void)
{
  initialize_is_integer_symbol_object();
  extend_symbol_name_table("integer?", get_is_integer_symbol_object());
}

static inline KLObject* primitive_function_is_integer
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  if (is_kl_number_l(objects[0]))
    return get_true_boolean_object();

  return get_false_boolean_object();
}

static inline void register_primitive_kl_function_is_integer (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_is_integer);

  set_kl_symbol_function(get_is_integer_symbol_object(), function_object);
}

static inline void initialize_is_variable_symbol_object (void)
{
  is_variable_symbol_object = create_kl_symbol("variable?");
}

static inline void register_is_variable_symbol_object (void)
{
  initialize_is_variable_symbol_object();
  extend_symbol_name_table("variable?", get_is_variable_symbol_object());
}

static inline KLObject* primitive_function_is_variable
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  if (is_kl_symbol(objects[0])) {
    char* symbol_name = get_kl_symbol_name(objects[0]);

    if (is_uppercase_alphabet_character(symbol_name[0]))
      return get_true_boolean_object();

    return get_false_boolean_object();
  }

  return get_false_boolean_object();
}

static inline void register_primitive_kl_function_is_variable (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_is_variable);

  set_kl_symbol_function(get_is_variable_symbol_object(), function_object);
}

static inline void initialize_not_symbol_object (void)
{
  not_symbol_object = create_kl_symbol("not");
}

static inline void register_not_symbol_object (void)
{
  initialize_not_symbol_object();
  extend_symbol_name_table("not", get_not_symbol_object());
}

static inline KLObject* primitive_function_not (KLObject* function_object,
                                                Vector* arguments,
                                                Environment* function_environment,
                                                Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  if (get_boolean(objects[0]))
    return get_false_boolean_object();

  return get_true_boolean_object();
}

static inline void register_primitive_kl_function_not (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_not);

  set_kl_symbol_function(get_not_symbol_object(), function_object);
}

static inline void initialize_value_slash_or_symbol_object (void)
{
  value_slash_or_symbol_object = create_kl_symbol("value/or");
}

static inline void register_value_slash_or_symbol_object (void)
{
  initialize_value_slash_or_symbol_object();
  extend_symbol_name_table("value/or", get_value_slash_or_symbol_object());
}

static inline KLObject* primitive_function_value_slash_or
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  KLObject* symbol_object = objects[0];
  KLObject* clojure_function_object = objects[1];

  if (!is_kl_symbol(symbol_object))
    return eval_simple_closure_function_application(clojure_function_object);

  KLObject* variable_value_object = get_kl_symbol_variable_value(symbol_object);

  if (is_null(variable_value_object))
    return eval_simple_closure_function_application(clojure_function_object);

  return variable_value_object;
}

static inline void register_primitive_kl_function_value_slash_or (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_value_slash_or);

  set_kl_symbol_function(get_value_slash_or_symbol_object(), function_object);
}

static inline void initialize_get_absvector_element_slash_or_symbol_object (void)
{
  get_absvector_element_slash_or_symbol_object = create_kl_symbol("<-address/or");
}

static inline void register_get_absvector_element_slash_or_symbol_object (void)
{
  initialize_get_absvector_element_slash_or_symbol_object();
  extend_symbol_name_table("<-address/or",
                           get_get_absvector_element_slash_or_symbol_object());
}

static inline KLObject* primitive_function_get_absvector_element_slash_or
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);
  KLObject* vector_object = objects[0];
  KLObject* number_object = objects[1];

  if (!is_kl_vector(vector_object))
    eval_simple_closure_function_application(objects[2]);

  if (!is_kl_number_l(number_object))
    eval_simple_closure_function_application(objects[2]);

  long index = get_kl_number_number_l(number_object);
  Vector* vector = get_vector(vector_object);
  size_t size = get_vector_size(vector);

  if (index >= (long)size || index < 0)
    eval_simple_closure_function_application(objects[2]);

  KLObject** vector_objects = get_vector_objects(vector);

  return vector_objects[index];
}

static inline void register_primitive_kl_function_get_absvector_element_slash_or
(void)
{
  KLObject* function_object =
    create_primitive_kl_function(3, &primitive_function_get_absvector_element_slash_or);

  set_kl_symbol_function(get_get_absvector_element_slash_or_symbol_object(),
                         function_object);
}

static inline void initialize_map_symbol_object (void)
{
  map_symbol_object = create_kl_symbol("map");
}

static inline void register_map_symbol_object (void)
{
  initialize_map_symbol_object();
  extend_symbol_name_table("map", get_map_symbol_object());
}

static inline KLObject* primitive_function_map
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);
  KLObject* symbol_or_function_object = objects[0];
  KLObject* argument_list_object = objects[1];
  KLObject* head_list_object = get_empty_kl_list();
  KLObject* tail_list_object = head_list_object;

  while (!is_empty_kl_list(argument_list_object)) {
    if (!is_non_empty_kl_list(argument_list_object))
      throw_kl_exception("Wrong arguments for map function");

    KLObject* quoted_argument_object
      = create_kl_list(get_quote_symbol_object(),
                       create_kl_list(get_head_kl_list(argument_list_object),
                                      get_empty_kl_list()));
    KLObject* function_application_list_object =
      create_kl_list(symbol_or_function_object,
                     create_kl_list(quoted_argument_object, get_empty_kl_list()));
    KLObject* list_object =
      create_kl_list(eval_kl_object(function_application_list_object,
                                    function_environment,
                                    variable_environment),
                     get_empty_kl_list());

    if (is_empty_kl_list(head_list_object))
      head_list_object = list_object;
    else
      set_tail_kl_list(tail_list_object, list_object);

    tail_list_object = list_object;
    argument_list_object = get_tail_kl_list(argument_list_object);
  }

  return head_list_object;
}

static inline void register_primitive_kl_function_map (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_map);

  set_kl_symbol_function(get_map_symbol_object(), function_object);
}

static inline void initialize_reverse_symbol_object (void)
{
  reverse_symbol_object = create_kl_symbol("reverse");
}

static inline void register_reverse_symbol_object (void)
{
  initialize_reverse_symbol_object();
  extend_symbol_name_table("reverse", get_reverse_symbol_object());
}

static inline KLObject* primitive_function_reverse
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);
  KLObject* argument_list_object = objects[0];

  if (!is_kl_list(argument_list_object))
    throw_kl_exception("Wrong argument for reverse function");

  KLObject* head_list_object = get_empty_kl_list();

  while (is_non_empty_kl_list(argument_list_object)) {
    head_list_object = create_kl_list(get_head_kl_list(argument_list_object),
                                      head_list_object);
    argument_list_object = get_tail_kl_list(argument_list_object);
  }

  return head_list_object;
}

static inline void register_primitive_kl_function_reverse (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_reverse);

  set_kl_symbol_function(get_reverse_symbol_object(), function_object);
}


static inline void initialize_shen_is_numbyte_symbol_object (void)
{
  shen_is_numbyte_symbol_object = create_kl_symbol("shen.numbyte?");
}

static inline void register_shen_is_numbyte_symbol_object (void)
{
  initialize_shen_is_numbyte_symbol_object();
  extend_symbol_name_table("shen.numbyte?", get_shen_is_numbyte_symbol_object());
}

static inline KLObject* primitive_function_shen_is_numbyte
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);
  long x = get_kl_number_number_l(objects[0]);

  if ((x >= 48 && x <= 57))
    return get_true_boolean_object();

  return get_false_boolean_object();
}

static inline void register_primitive_kl_function_shen_is_numbyte (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_shen_is_numbyte);

  set_kl_symbol_function(get_shen_is_numbyte_symbol_object(), function_object);
}

static inline void initialize_shen_byte_to_digit_symbol_object (void)
{
  shen_byte_to_digit_symbol_object = create_kl_symbol("shen.byte->digit");
}

static inline void register_shen_byte_to_digit_symbol_object (void)
{
  initialize_shen_byte_to_digit_symbol_object();
  extend_symbol_name_table("shen.byte->digit",
                           get_shen_byte_to_digit_symbol_object());
}

static inline KLObject* primitive_function_shen_byte_to_digit
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  long x = get_kl_number_number_l(objects[0]);

  switch (x) {
  case 48: return create_kl_number_l(0);
  case 49: return create_kl_number_l(1);
  case 50: return create_kl_number_l(2);
  case 51: return create_kl_number_l(3);
  case 52: return create_kl_number_l(4);
  case 53: return create_kl_number_l(5);
  case 54: return create_kl_number_l(6);
  case 55: return create_kl_number_l(7);
  case 56: return create_kl_number_l(8);
  case 57: return create_kl_number_l(9);
  default: throw_kl_exception("Out of range error in shen.byte->digit");
  }

  return create_kl_number_l(0);
}

static inline void register_primitive_kl_function_shen_byte_to_digit (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_shen_byte_to_digit);

  set_kl_symbol_function(get_shen_byte_to_digit_symbol_object(), function_object);
}

static inline void initialize_read_file_as_charlist_symbol_object (void)
{
  read_file_as_charlist_symbol_object = create_kl_symbol("read-file-as-charlist");
}

static inline void register_read_file_as_charlist_symbol_object (void)
{
  initialize_read_file_as_charlist_symbol_object();
  extend_symbol_name_table("read-file-as-charlist",
                           get_read_file_as_charlist_symbol_object());
}

static inline KLObject* primitive_function_read_file_as_charlist
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);
  KLObject* string_object = objects[0];

  if (!is_kl_string(string_object))
    throw_kl_exception("The argument to read-file-as-charlist should be a string");

  char* file_path = get_string(string_object);
  KLObject* home_directory_string_object =
    get_kl_symbol_variable_value(get_earmuff_home_directory_symbol_object());
  char* home_directory_string = get_string(home_directory_string_object);

  if (strcmp(home_directory_string, "") != 0)
    file_path = concatenate_string(home_directory_string, file_path);

  char* string = read_file_by_file_path(file_path);
  size_t string_length = strlen(string);
  KLObject* head_list_object = NULL;
  KLObject* tail_list_object = head_list_object;

  for (long i = 0; i < string_length; ++i) {
    KLObject* list_object = create_kl_list(create_kl_number_l(string[i]),
                                           get_empty_kl_list());

    if (is_null(head_list_object))
      head_list_object = list_object;
    else
      set_tail_kl_list(tail_list_object, list_object);

    tail_list_object = list_object;
  }

  return head_list_object;
}

static inline void register_primitive_kl_function_read_file_as_charlist (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_read_file_as_charlist);

  set_kl_symbol_function(get_read_file_as_charlist_symbol_object(),
                         function_object);
}


static inline void initialize_shen_pvar_symbol_object (void)
{
  shen_pvar_symbol_object = create_kl_symbol("shen.pvar");
}

static inline void register_shen_pvar_symbol_object (void)
{
  initialize_shen_pvar_symbol_object();
  extend_symbol_name_table("shen.pvar", get_shen_pvar_symbol_object());
}

static inline void initialize_shen_is_pvar_symbol_object (void)
{
  shen_is_pvar_symbol_object = create_kl_symbol("shen.pvar?");
}

static inline void register_shen_is_pvar_symbol_object (void)
{
  initialize_shen_is_pvar_symbol_object();
  extend_symbol_name_table("shen.pvar?", get_shen_is_pvar_symbol_object());
}

static inline KLObject* primitive_function_shen_is_pvar
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  if (is_kl_vector(objects[0])) {
    Vector* vector = get_vector(objects[0]);
    KLObject* object = get_vector_element(vector, 0);

    if (object == get_shen_pvar_symbol_object())
      return get_true_boolean_object();

    return get_false_boolean_object();
  }

  return get_false_boolean_object();
}

static inline void register_primitive_kl_function_shen_is_pvar (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_shen_is_pvar);

  set_kl_symbol_function(get_shen_is_pvar_symbol_object(), function_object);
}

void register_overwrite_symbol_objects (void)
{
  register_exit_symbol_object();
  register_hash_symbol_object();
  register_is_symbol_symbol_object();
  register_is_boolean_symbol_object();
  register_is_integer_symbol_object();
  register_is_variable_symbol_object();
  register_not_symbol_object();
  register_value_slash_or_symbol_object();
  register_get_absvector_element_slash_or_symbol_object();
  register_map_symbol_object();
  register_reverse_symbol_object();
  register_shen_is_numbyte_symbol_object();
  register_read_file_as_charlist_symbol_object();
  register_shen_byte_to_digit_symbol_object();
  register_shen_pvar_symbol_object();
  register_shen_is_pvar_symbol_object();
}

void register_overwrite_toplevel_primitive_kl_functions (void)
{
  register_primitive_kl_function_exit();
}

void register_overwrite_sys_primitive_kl_functions (void)
{
  register_primitive_kl_function_hash();
  register_primitive_kl_function_is_symbol();
  register_primitive_kl_function_is_integer();
  register_primitive_kl_function_is_boolean();
  register_primitive_kl_function_is_variable();
  register_primitive_kl_function_not();
  register_primitive_kl_function_value_slash_or();
  register_primitive_kl_function_get_absvector_element_slash_or();
  register_primitive_kl_function_map();
  register_primitive_kl_function_reverse();
}

void register_overwrite_reader_primitive_kl_functions (void)
{
  register_primitive_kl_function_shen_is_numbyte();
  register_primitive_kl_function_shen_byte_to_digit();
  register_primitive_kl_function_read_file_as_charlist();
}

void register_overwrite_prolog_primitive_kl_functions (void)
{
  register_primitive_kl_function_shen_is_pvar();
}
