#include "primitive.h"

extern KLObject** get_kl_function_arguments_with_count_check
(KLObject* function_object, Vector* arguments);

static inline KLObject* primitive_function_intern
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);
  KLObject* string_object = objects[0];

  if (!is_kl_string(string_object))
    throw_kl_exception("Should be a string object");

  if (is_kl_string_equal(string_object, true_string_object))
    return get_true_boolean_object();
  else if (is_kl_string_equal(string_object, false_string_object))
    return get_false_boolean_object();

  char* string = get_string(string_object);
  KLObject* symbol_object = lookup_symbol_name_table(string);

  if (is_null(symbol_object)) {
    symbol_object = create_kl_symbol(string);
    extend_symbol_name_table(string, symbol_object);
  }

  return symbol_object;
}

static inline void register_primitive_kl_function_intern (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_intern);

  set_kl_symbol_function(get_intern_symbol_object(), function_object);
}

static inline KLObject* primitive_function_pos (KLObject* function_object,
                                                Vector* arguments,
                                                Environment* function_environment,
                                                Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return get_position_kl_string(objects[0], objects[1]);
}

static inline void register_primitive_kl_function_pos (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_pos);

  set_kl_symbol_function(get_pos_symbol_object(), function_object);
}

static inline KLObject* primitive_function_tlstr
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return get_tail_kl_string(objects[0]);
}

static inline void register_primitive_kl_function_tlstr (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_tlstr);

  set_kl_symbol_function(get_tlstr_symbol_object(), function_object);
}

static inline KLObject* primitive_function_cn (KLObject* function_object,
                                               Vector* arguments,
                                               Environment* function_environment,
                                               Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return concatenate_kl_string(objects[0], objects[1]);
}

static inline void register_primitive_kl_function_cn (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_cn);

  set_kl_symbol_function(get_cn_symbol_object(), function_object);
}

static inline KLObject* primitive_function_str (KLObject* function_object,
                                                Vector* arguments,
                                                Environment* function_environment,
                                                Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);
  char* string = NULL;

  if (is_kl_symbol(objects[0]))
    string = get_kl_symbol_name(objects[0]);
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

  return create_kl_string_with_intern(string);
}

static inline void register_primitive_kl_function_str (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_str);

  set_kl_symbol_function(get_str_symbol_object(), function_object);
}

static inline KLObject* primitive_function_is_string
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  if (is_kl_string(objects[0]))
    return get_true_boolean_object();

  return get_false_boolean_object();
}

static inline void register_primitive_kl_function_is_string (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_is_string);

  set_kl_symbol_function(get_is_string_symbol_object(), function_object);
}

static inline KLObject* primitive_function_n_to_string
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return kl_number_code_point_to_kl_string(objects[0]);
}

static inline void register_primitive_kl_function_n_to_string (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_n_to_string);

  set_kl_symbol_function(get_n_to_string_symbol_object(), function_object);
}

static inline KLObject* primitive_function_string_to_n
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return kl_string_to_kl_number_code_point(objects[0]);
}

static inline void register_primitive_kl_function_string_to_n (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_string_to_n);

  set_kl_symbol_function(get_string_to_n_symbol_object(), function_object);
}

static inline KLObject* primitive_function_set (KLObject* function_object,
                                                Vector* arguments,
                                                Environment* function_environment,
                                                Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return set_variable_value(objects[0], objects[1],
                            get_global_variable_environment());
}

static inline void register_primitive_kl_function_set (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_set);

  set_kl_symbol_function(get_set_symbol_object(), function_object);
}

static inline KLObject* primitive_function_value
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return get_variable_value(objects[0], get_global_variable_environment());
}

static inline void register_primitive_kl_function_value (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_value);

  set_kl_symbol_function(get_value_symbol_object(), function_object);
}

static inline KLObject* primitive_function_simple_error
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);
  KLObject* string_object = objects[0];

  if (!is_kl_string(string_object))
    throw_kl_exception("Parameter should be a string");

  throw_kl_exception(get_string(string_object));

  return NULL;
}

static inline void register_primitive_kl_function_simple_error (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_simple_error);

  set_kl_symbol_function(get_simple_error_symbol_object(), function_object);
}

static inline KLObject* primitive_function_error_to_string
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  if (!is_kl_exception(objects[0]))
    throw_kl_exception("Parameter is not an exception object");

  char* error_message = get_exception_error_message(get_exception(objects[0]));

  return create_kl_string_with_intern(error_message);
}

static inline void register_primitive_kl_function_error_to_string (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_error_to_string);

  set_kl_symbol_function(get_error_to_string_symbol_object(), function_object);
}

static inline KLObject* primitive_function_cons (KLObject* function_object,
                                                 Vector* arguments,
                                                 Environment* function_environment,
                                                 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return CONS(objects[0], objects[1]);
}

static inline void register_primitive_kl_function_cons (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_cons);

  set_kl_symbol_function(get_cons_symbol_object(), function_object);
}

static inline KLObject* primitive_function_hd (KLObject* function_object,
                                               Vector* arguments,
                                               Environment* function_environment,
                                               Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return CAR(objects[0]);
}

static inline void register_primitive_kl_function_hd (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_hd);

  set_kl_symbol_function(get_hd_symbol_object(), function_object);
}

static inline KLObject* primitive_function_tl (KLObject* function_object,
                                               Vector* arguments,
                                               Environment* function_environment,
                                               Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return CDR(objects[0]);
}

static inline void register_primitive_kl_function_tl (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_tl);

  set_kl_symbol_function(get_tl_symbol_object(), function_object);
}

static inline KLObject* primitive_function_is_cons
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  if (is_non_empty_kl_list(objects[0]))
    return get_true_boolean_object();

  return get_false_boolean_object();
}

static inline void register_primitive_kl_function_is_cons (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_is_cons);

  set_kl_symbol_function(get_is_cons_symbol_object(), function_object);
}

static inline KLObject* primitive_function_is_equal
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  if (is_kl_object_equal(objects[0], objects[1]))
    return get_true_boolean_object();

  return get_false_boolean_object();
}

static inline void register_primitive_kl_function_is_equal (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_is_equal);

  set_kl_symbol_function(get_is_equal_symbol_object(), function_object);
}

static inline KLObject* primitive_function_type
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return objects[0];
}

static inline void register_primitive_kl_function_type (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_type);

  set_kl_symbol_function(get_type_symbol_object(), function_object);
}

static inline KLObject* primitive_function_absvector
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return create_kl_vector(get_kl_number_number_l(objects[0]));
}

static inline void register_primitive_kl_function_absvector (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_absvector);

  set_kl_symbol_function(get_absvector_symbol_object(), function_object);
}

static inline KLObject* primitive_function_set_absvector_element
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);
  KLObject* vector_object = objects[0];
  KLObject* index_object = objects[1];

  if (!is_kl_vector(vector_object))
    throw_kl_exception("Failed to set an element to a non-vector object");

  if (!is_kl_number_l(index_object))
    throw_kl_exception("Vector index should be a number object");

  Vector* vector = get_vector(vector_object);
  long index = get_kl_number_number_l(index_object);
  long size = get_vector_size(vector);

  if (index >= size || index < 0)
    throw_kl_exception("Vector index is out of bound");

  set_vector_element(vector, index, objects[2]);

  return vector_object;
}

static inline void register_primitive_kl_function_set_absvector_element (void)
{
  KLObject* function_object =
    create_primitive_kl_function(3, &primitive_function_set_absvector_element);

  set_kl_symbol_function(get_set_absvector_element_symbol_object(), function_object);
}

static inline KLObject* primitive_function_get_absvector_element
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);
  KLObject* vector_object = objects[0];
  KLObject* index_object = objects[1];

  if (!is_kl_vector(vector_object))
    throw_kl_exception("Failed to get an element from a non-vector object");

  if (!is_kl_number_l(index_object))
    throw_kl_exception("Vector index should be a number object");

  Vector* vector = get_vector(vector_object);
  long index = get_kl_number_number_l(index_object);
  long size = get_vector_size(vector);

  if (index >= size || index < 0)
    throw_kl_exception("Vector index is out of bound");

  return get_vector_element(vector, index);
}

static inline void register_primitive_kl_function_get_absvector_element (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_get_absvector_element);

  set_kl_symbol_function(get_get_absvector_element_symbol_object(),
                         function_object);
}

static inline KLObject* primitive_function_is_absvector
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  if (is_kl_vector(objects[0]))
    return get_true_boolean_object();

  return get_false_boolean_object();
}

static inline void register_primitive_kl_function_is_absvector (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_is_absvector);

  set_kl_symbol_function(get_is_absvector_symbol_object(), function_object);
}

static inline KLObject* primitive_function_write_byte
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return write_kl_stream_byte(objects[1], objects[0]);
}

static inline void register_primitive_kl_function_write_byte (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_write_byte);

  set_kl_symbol_function(get_write_byte_symbol_object(), function_object);
}

static inline KLObject* primitive_function_read_byte
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return read_kl_stream_byte(objects[0]);
}

static inline void register_primitive_kl_function_read_byte (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_read_byte);

  set_kl_symbol_function(get_read_byte_symbol_object(), function_object);
}

static inline KLObject* primitive_function_open
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  if (!is_kl_string(objects[0]))
    throw_kl_exception("File path should be a string");

  if (!is_kl_symbol(objects[1]))
    throw_kl_exception("Stream direction should be a symbol");

  KLObject* home_directory_string_object =
    get_kl_symbol_variable_value(get_earmuff_home_directory_symbol_object());
  char* home_directory_string = get_string(home_directory_string_object);

  if (is_kl_string_equal(home_directory_string_object, empty_string_object))
    #ifdef SHEN_C_MOBILE
    return create_kl_stream_from_home_path(get_string(objects[0]), objects[1]);
    #else
    return create_kl_stream(get_string(objects[0]), objects[1]);
    #endif

  char* file_path = concatenate_string(home_directory_string,
                                       get_string(objects[0]));

  #ifdef SHEN_C_MOBILE
  return create_kl_stream_from_home_path(file_path, objects[1]);
  #else
  return create_kl_stream(file_path, objects[1]);
  #endif
}

static inline void register_primitive_kl_function_open (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_open);

  set_kl_symbol_function(get_open_symbol_object(), function_object);
}

static inline KLObject* primitive_function_close
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return close_kl_stream(objects[0]);
}

static inline void register_primitive_kl_function_close (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_close);

  set_kl_symbol_function(get_close_symbol_object(), function_object);
}

static inline KLObject* primitive_function_get_time
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return get_kl_number_time(objects[0]);
}

static inline void register_primitive_kl_function_get_time (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_get_time);

  set_kl_symbol_function(get_get_time_symbol_object(), function_object);
}

static inline KLObject* primitive_function_add (KLObject* function_object,
                                                Vector* arguments,
                                                Environment* function_environment,
                                                Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);
  
  return add_kl_number(objects[0], objects[1]);
}

static inline void register_primitive_kl_function_add (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_add);

  set_kl_symbol_function(get_add_symbol_object(), function_object);
}

static inline KLObject* primitive_function_subtract
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return subtract_kl_number(objects[0], objects[1]);
}

static inline void register_primitive_kl_function_subtract (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_subtract);

  set_kl_symbol_function(get_subtract_symbol_object(), function_object);
}

static inline KLObject* primitive_function_multiply (KLObject* function_object,
                                                     Vector* arguments,
                                                     Environment* function_environment,
                                                     Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return multiply_kl_number(objects[0], objects[1]);
}

static inline void register_primitive_kl_function_multiply (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_multiply);

  set_kl_symbol_function(get_multiply_symbol_object(), function_object);
}

static inline KLObject* primitive_function_divide
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return divide_kl_number(objects[0], objects[1]);
}

static inline void register_primitive_kl_function_divide (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_divide);

  set_kl_symbol_function(get_divide_symbol_object(), function_object);
}

static inline KLObject* primitive_function_is_greater
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  if (is_kl_number_greater(objects[0], objects[1]))
    return get_true_boolean_object();

  return get_false_boolean_object();
}

static inline void register_primitive_kl_function_is_greater (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_is_greater);

  set_kl_symbol_function(get_is_greater_symbol_object(), function_object);
}

static inline KLObject* primitive_function_is_less
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  if (is_kl_number_less(objects[0], objects[1]))
    return get_true_boolean_object();

  return get_false_boolean_object();
}

static inline void register_primitive_kl_function_is_less (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_is_less);

  set_kl_symbol_function(get_is_less_symbol_object(), function_object);
}

static inline KLObject* primitive_function_is_greater_or_equal
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  if (is_kl_number_greater_or_equal(objects[0], objects[1]))
    return get_true_boolean_object();

  return get_false_boolean_object();
}

static inline void register_primitive_kl_function_is_greater_or_equal (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_is_greater_or_equal);

  set_kl_symbol_function(get_is_greater_or_equal_symbol_object(), function_object);
}

static inline KLObject* primitive_function_is_less_or_equal
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  if (is_kl_number_less_or_equal(objects[0], objects[1]))
    return get_true_boolean_object();

  return get_false_boolean_object();
}

static inline void register_primitive_kl_function_is_less_or_equal (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_is_less_or_equal);

  set_kl_symbol_function(get_is_less_or_equal_symbol_object(), function_object);
}

static inline KLObject* primitive_function_is_number
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  if (is_kl_number(objects[0]))
    return get_true_boolean_object();

  return get_false_boolean_object();
}

static inline void register_primitive_kl_function_is_number (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_is_number);

  set_kl_symbol_function(get_is_number_symbol_object(), function_object);
}

void register_primitive_kl_functions (void)
{
  register_primitive_kl_function_intern();
  register_primitive_kl_function_pos();
  register_primitive_kl_function_tlstr();
  register_primitive_kl_function_cn();
  register_primitive_kl_function_str();
  register_primitive_kl_function_is_string();
  register_primitive_kl_function_n_to_string();
  register_primitive_kl_function_string_to_n();
  register_primitive_kl_function_set();
  register_primitive_kl_function_value();
  register_primitive_kl_function_simple_error();
  register_primitive_kl_function_error_to_string();
  register_primitive_kl_function_cons();
  register_primitive_kl_function_hd();
  register_primitive_kl_function_tl();
  register_primitive_kl_function_is_cons();
  register_primitive_kl_function_is_equal();
  register_primitive_kl_function_type();
  register_primitive_kl_function_absvector();
  register_primitive_kl_function_set_absvector_element();
  register_primitive_kl_function_get_absvector_element();
  register_primitive_kl_function_is_absvector();
  register_primitive_kl_function_write_byte();
  register_primitive_kl_function_read_byte();
  register_primitive_kl_function_open();
  register_primitive_kl_function_close();
  register_primitive_kl_function_get_time();
  register_primitive_kl_function_add();
  register_primitive_kl_function_subtract();
  register_primitive_kl_function_multiply();
  register_primitive_kl_function_divide();
  register_primitive_kl_function_is_greater();
  register_primitive_kl_function_is_less();
  register_primitive_kl_function_is_greater_or_equal();
  register_primitive_kl_function_is_less_or_equal();
  register_primitive_kl_function_is_number();
}
