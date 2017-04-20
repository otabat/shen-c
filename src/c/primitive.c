#include "primitive.h"

extern KLObject** get_kl_function_arguments_with_count_check
(KLObject* function_object, Vector* arguments);
extern void register_primitive_kl_function
(char* symbol, KLObject* (*create_primitive_kl_function) (void));

static inline KLObject* primitive_function_intern (KLObject* function_object,
                                                   Vector* arguments)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return kl_string_to_kl_symbol_or_kl_boolean(objects[0]);
}

static inline KLObject* create_primitive_kl_function_intern (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_intern);

  return function_object;
}

static inline KLObject* primitive_function_pos (KLObject* function_object,
                                                Vector* arguments)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return get_position_kl_string(objects[0], objects[1]);
}

static inline KLObject* create_primitive_kl_function_pos (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_pos);

  return function_object;
}

static inline KLObject* primitive_function_tlstr (KLObject* function_object,
                                                  Vector* arguments)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return get_tail_kl_string(objects[0]);
}

static inline KLObject* create_primitive_kl_function_tlstr (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_tlstr);

  return function_object;
}

static inline KLObject* primitive_function_cn (KLObject* function_object,
                                               Vector* arguments)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return concatenate_kl_string(objects[0], objects[1]);
}

static inline KLObject* create_primitive_kl_function_cn (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_cn);

  return function_object;
}

static inline KLObject* primitive_function_str (KLObject* function_object,
                                                Vector* arguments)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);
  char* string = NULL;

  if (is_kl_symbol(objects[0]))
    string = get_symbol(objects[0]);
  else if (is_kl_string(objects[0]))
    string = get_double_quoted_string(objects[0]);
  else if (is_kl_number(objects[0]))
    string = kl_number_to_string(objects[0]);
  else if (is_kl_boolean(objects[0]))
    string = kl_boolean_to_string(objects[0]);
  else if (is_kl_function(objects[0]))
    string = kl_function_to_string(objects[0]);
  else if (is_kl_stream(objects[0]))
    string = kl_stream_to_string(objects[0]);
  else
    throw_kl_exception("Parameter is not an atom, closure, or stream");

  return create_kl_string(string);
}

static inline KLObject* create_primitive_kl_function_str (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_str);

  return function_object;
}

static inline KLObject* primitive_function_is_string (KLObject* function_object,
                                                      Vector* arguments)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return create_kl_boolean(is_kl_string(objects[0]));
}

static inline KLObject* create_primitive_kl_function_is_string (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_is_string);

  return function_object;
}

static inline KLObject* primitive_function_n_to_string (KLObject* function_object,
                                                        Vector* arguments)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return kl_number_code_point_to_kl_string(objects[0]);
}

static inline KLObject* create_primitive_kl_function_n_to_string (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_n_to_string);

  return function_object;
}

static inline KLObject* primitive_function_string_to_n (KLObject* function_object,
                                                        Vector* arguments)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return kl_string_to_kl_number_code_point(objects[0]);
}

static inline KLObject* create_primitive_kl_function_string_to_n (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_string_to_n);

  return function_object;
}

static inline KLObject* primitive_function_set (KLObject* function_object,
                                                Vector* arguments)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return set_variable_value(objects[0], objects[1],
                            get_global_variable_environment());
}

static inline KLObject* create_primitive_kl_function_set (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_set);

  return function_object;
}

static inline KLObject* primitive_function_value (KLObject* function_object,
                                                  Vector* arguments)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return get_variable_value(objects[0], get_global_variable_environment());
}

static inline KLObject* create_primitive_kl_function_value (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_value);

  return function_object;
}

static inline KLObject* primitive_function_simple_error (KLObject* function_object,
                                                         Vector* arguments)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);
  KLObject* string_object = objects[0];

  if (!is_kl_string(string_object))
    throw_kl_exception("Parameter should be a string");

  throw_kl_exception(get_string(string_object));

  return NULL;
}

static inline KLObject* create_primitive_kl_function_simple_error (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_simple_error);

  return function_object;
}

static inline KLObject* primitive_function_error_to_string
(KLObject* function_object, Vector* arguments)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  if (!is_kl_exception(objects[0]))
    throw_kl_exception("Parameter is not an exception object");

  return create_kl_string(get_exception_error_message(get_exception(objects[0])));
}

static inline KLObject* create_primitive_kl_function_error_to_string (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_error_to_string);

  return function_object;
}

static inline KLObject* primitive_function_cons (KLObject* function_object,
                                                 Vector* arguments)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return create_kl_list(objects[0], objects[1]);
}

static inline KLObject* create_primitive_kl_function_cons (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_cons);

  return function_object;
}

static inline KLObject* primitive_function_hd (KLObject* function_object,
                                               Vector* arguments)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return get_head_kl_list(objects[0]);
}

static inline KLObject* create_primitive_kl_function_hd (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_hd);

  return function_object;
}

static inline KLObject* primitive_function_tl (KLObject* function_object,
                                               Vector* arguments)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return get_tail_kl_list(objects[0]);
}

static inline KLObject* create_primitive_kl_function_tl (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_tl);

  return function_object;
}

static inline KLObject* primitive_function_is_cons (KLObject* function_object,
                                                    Vector* arguments)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return create_kl_boolean(is_non_empty_kl_list(objects[0]));
}

static inline KLObject* create_primitive_kl_function_is_cons (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_is_cons);

  return function_object;
}

static inline KLObject* primitive_function_is_equal (KLObject* function_object,
                                                     Vector* arguments)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return create_kl_boolean(is_kl_object_equal(objects[0], objects[1]));
}

static inline KLObject* create_primitive_kl_function_is_equal (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_is_equal);

  return function_object;
}

static inline KLObject* primitive_function_type (KLObject* function_object,
                                                 Vector* arguments)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return objects[0];
}

static inline KLObject* create_primitive_kl_function_type (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_type);

  return function_object;
}

static inline KLObject* primitive_function_absvector (KLObject* function_object,
                                                      Vector* arguments)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return create_kl_vector((size_t)get_kl_number_number_l(objects[0]));
}

static inline KLObject* create_primitive_kl_function_absvector (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_absvector);

  return function_object;
}

static inline KLObject* primitive_function_set_absvector_element
(KLObject* function_object, Vector* arguments)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return set_kl_vector_element(objects[0], objects[1], objects[2]);
}

static inline KLObject* create_primitive_kl_function_set_absvector_element (void)
{
  KLObject* function_object =
    create_primitive_kl_function(3, &primitive_function_set_absvector_element);

  return function_object;
}

static inline KLObject* primitive_function_get_absvector_element
(KLObject* function_object, Vector* arguments)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return get_kl_vector_element(objects[0], objects[1]);
}

static inline KLObject* create_primitive_kl_function_get_absvector_element (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_get_absvector_element);

  return function_object;
}

static inline KLObject* primitive_function_is_absvector (KLObject* function_object,
                                                         Vector* arguments)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return create_kl_boolean(is_kl_vector(objects[0]));
}

static inline KLObject* create_primitive_kl_function_is_absvector (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_is_absvector);

  return function_object;
}

static inline KLObject* primitive_function_write_byte (KLObject* function_object,
                                                       Vector* arguments)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return write_kl_stream_byte(objects[1], objects[0]);
}

static inline KLObject* create_primitive_kl_function_write_byte (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_write_byte);

  return function_object;
}

static inline KLObject* primitive_function_read_byte (KLObject* function_object,
                                                      Vector* arguments)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return read_kl_stream_byte(objects[0]);
}

static inline KLObject* create_primitive_kl_function_read_byte (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_read_byte);

  return function_object;
}

static inline KLObject* primitive_function_open (KLObject* function_object,
                                                 Vector* arguments)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  if (!is_kl_string(objects[0]))
    throw_kl_exception("File path should be a string");

  if (!is_kl_symbol(objects[1]))
    throw_kl_exception("Stream direction should be a symbol");

  KLObject* home_directory_string_object =
    get_variable_value(create_kl_symbol("*home-directory*"),
                       get_global_variable_environment());
  char* home_directory_string = get_string(home_directory_string_object);

  if (strcmp(home_directory_string, "") == 0)
    return create_kl_stream(get_string(objects[0]), get_symbol(objects[1]));

  char* file_path = concatenate_string(home_directory_string,
                                       get_string(objects[0]));

  return create_kl_stream(file_path, get_symbol(objects[1]));
}

static inline KLObject* create_primitive_kl_function_open (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_open);

  return function_object;
}

static inline KLObject* primitive_function_close (KLObject* function_object,
                                                  Vector* arguments)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return close_kl_stream(objects[0]);
}

static inline KLObject* create_primitive_kl_function_close (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_close);

  return function_object;
}

static inline KLObject* primitive_function_get_time (KLObject* function_object,
                                                     Vector* arguments)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return get_kl_number_time(objects[0]);
}

static inline KLObject* create_primitive_kl_function_get_time (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_get_time);

  return function_object;
}

static inline KLObject* primitive_function_add (KLObject* function_object,
                                                Vector* arguments)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);
  
  return add_kl_number(objects[0], objects[1]);
}

static inline KLObject* create_primitive_kl_function_add (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_add);

  return function_object;
}

static inline KLObject* primitive_function_subtract (KLObject* function_object,
                                                     Vector* arguments)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return subtract_kl_number(objects[0], objects[1]);
}

static inline KLObject* create_primitive_kl_function_subtract (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_subtract);

  return function_object;
}

static inline KLObject* primitive_function_multiply (KLObject* function_object,
                                                     Vector* arguments)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return multiply_kl_number(objects[0], objects[1]);
}

static inline KLObject* create_primitive_kl_function_multiply (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_multiply);

  return function_object;
}

static inline KLObject* primitive_function_divide (KLObject* function_object,
                                                   Vector* arguments)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return divide_kl_number(objects[0], objects[1]);
}

static inline KLObject* create_primitive_kl_function_divide (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_divide);

  return function_object;
}

static inline KLObject* primitive_function_is_greater (KLObject* function_object,
                                                       Vector* arguments)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return create_kl_boolean(is_kl_number_greater(objects[0], objects[1]));
}

static inline KLObject* create_primitive_kl_function_is_greater (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_is_greater);

  return function_object;
}

static inline KLObject* primitive_function_is_less (KLObject* function_object,
                                                    Vector* arguments)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return create_kl_boolean(is_kl_number_less(objects[0], objects[1]));
}

static inline KLObject* create_primitive_kl_function_is_less (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_is_less);

  return function_object;
}

static inline KLObject* primitive_function_is_greater_or_equal
(KLObject* function_object, Vector* arguments)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return create_kl_boolean(is_kl_number_greater_or_equal(objects[0], objects[1]));
}

static inline KLObject* create_primitive_kl_function_is_greater_or_equal (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_is_greater_or_equal);

  return function_object;
}

static inline KLObject* primitive_function_is_less_or_equal
(KLObject* function_object, Vector* arguments)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return create_kl_boolean(is_kl_number_less_or_equal(objects[0], objects[1]));
}

static inline KLObject* create_primitive_kl_function_is_less_or_equal (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_is_less_or_equal);

  return function_object;
}

static inline KLObject* primitive_function_is_number (KLObject* function_object,
                                                      Vector* arguments)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return create_kl_boolean(is_kl_number(objects[0]));
}

static inline KLObject* create_primitive_kl_function_is_number (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_is_number);

  return function_object;
}

void register_primitive_kl_functions (void)
{
  register_primitive_kl_function("intern", &create_primitive_kl_function_intern);
  
  register_primitive_kl_function("pos", &create_primitive_kl_function_pos);
  register_primitive_kl_function("tlstr", &create_primitive_kl_function_tlstr);
  register_primitive_kl_function("cn", &create_primitive_kl_function_cn);
  register_primitive_kl_function("str", &create_primitive_kl_function_str);
  register_primitive_kl_function("string?",
                                 &create_primitive_kl_function_is_string);
  register_primitive_kl_function("n->string",
                                 &create_primitive_kl_function_n_to_string);
  register_primitive_kl_function("string->n",
                                 &create_primitive_kl_function_string_to_n);

  register_primitive_kl_function("set", &create_primitive_kl_function_set);
  register_primitive_kl_function("value", &create_primitive_kl_function_value);
  register_primitive_kl_function("simple-error",
                                 &create_primitive_kl_function_simple_error);
  register_primitive_kl_function("error-to-string",
                                 &create_primitive_kl_function_error_to_string);

  register_primitive_kl_function("cons", &create_primitive_kl_function_cons);
  register_primitive_kl_function("hd", &create_primitive_kl_function_hd);
  register_primitive_kl_function("tl", &create_primitive_kl_function_tl);
  register_primitive_kl_function("cons?", &create_primitive_kl_function_is_cons);

  register_primitive_kl_function("=", &create_primitive_kl_function_is_equal);
  register_primitive_kl_function("type", &create_primitive_kl_function_type);

  register_primitive_kl_function("absvector",
                                 &create_primitive_kl_function_absvector);
  register_primitive_kl_function("address->",
                                 &create_primitive_kl_function_set_absvector_element);
  register_primitive_kl_function("<-address",
                                 &create_primitive_kl_function_get_absvector_element);
  register_primitive_kl_function("absvector?",
                                 &create_primitive_kl_function_is_absvector);

  register_primitive_kl_function("write-byte",
                                 &create_primitive_kl_function_write_byte);
  register_primitive_kl_function("read-byte",
                                 &create_primitive_kl_function_read_byte);
  register_primitive_kl_function("open", &create_primitive_kl_function_open);
  register_primitive_kl_function("close", &create_primitive_kl_function_close);

  register_primitive_kl_function("get-time",
                                 &create_primitive_kl_function_get_time);

  register_primitive_kl_function("+", &create_primitive_kl_function_add);
  register_primitive_kl_function("-", &create_primitive_kl_function_subtract);
  register_primitive_kl_function("*", &create_primitive_kl_function_multiply);
  register_primitive_kl_function("/", &create_primitive_kl_function_divide);
  register_primitive_kl_function(">", &create_primitive_kl_function_is_greater);
  register_primitive_kl_function("<", &create_primitive_kl_function_is_less);
  register_primitive_kl_function(">=",
                                 &create_primitive_kl_function_is_greater_or_equal);
  register_primitive_kl_function("<=",
                                 &create_primitive_kl_function_is_less_or_equal);
  register_primitive_kl_function("number?",
                                 &create_primitive_kl_function_is_number);
}
