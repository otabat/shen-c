#include "primitive.h"

KLObject* if_symbol_object;
KLObject* and_symbol_object;
KLObject* or_symbol_object;
KLObject* cond_symbol_object;
KLObject* intern_symbol_object;
KLObject* pos_symbol_object;
KLObject* tlstr_symbol_object;
KLObject* cn_symbol_object;
KLObject* str_symbol_object;
KLObject* is_string_symbol_object;
KLObject* n_to_string_symbol_object;
KLObject* string_to_n_symbol_object;
KLObject* set_symbol_object;
KLObject* value_symbol_object;
KLObject* simple_error_symbol_object;
KLObject* trap_error_symbol_object;
KLObject* error_to_string_symbol_object;
KLObject* cons_symbol_object;
KLObject* hd_symbol_object;
KLObject* tl_symbol_object;
KLObject* is_cons_symbol_object;
KLObject* defun_symbol_object;
KLObject* lambda_symbol_object;
KLObject* let_symbol_object;
KLObject* is_equal_symbol_object;
KLObject* eval_kl_symbol_object;
KLObject* freeze_symbol_object;
KLObject* type_symbol_object;
KLObject* absvector_symbol_object;
KLObject* set_absvector_element_symbol_object;
KLObject* get_absvector_element_symbol_object;
KLObject* is_absvector_symbol_object;
KLObject* write_byte_symbol_object;
KLObject* read_byte_symbol_object;
KLObject* open_symbol_object;
KLObject* close_symbol_object;
KLObject* get_time_symbol_object;
KLObject* add_symbol_object;
KLObject* subtract_symbol_object;
KLObject* multiply_symbol_object;
KLObject* divide_symbol_object;
KLObject* is_greater_symbol_object;
KLObject* is_less_symbol_object;
KLObject* is_greater_or_equal_symbol_object;
KLObject* is_less_or_equal_symbol_object;
KLObject* is_number_symbol_object;

extern KLObject* get_if_symbol_object (void);
extern KLObject* get_and_symbol_object (void);
extern KLObject* get_or_symbol_object (void);
extern KLObject* get_cond_symbol_object (void);
extern KLObject* get_intern_symbol_object (void);
extern KLObject* get_pos_symbol_object (void);
extern KLObject* get_tlstr_symbol_object (void);
extern KLObject* get_cn_symbol_object (void);
extern KLObject* get_str_symbol_object (void);
extern KLObject* get_is_string_symbol_object (void);
extern KLObject* get_n_to_string_symbol_object (void);
extern KLObject* get_string_to_n_symbol_object (void);
extern KLObject* get_set_symbol_object (void);
extern KLObject* get_value_symbol_object (void);
extern KLObject* get_simple_error_symbol_object (void);
extern KLObject* get_trap_error_symbol_object (void);
extern KLObject* get_error_to_string_symbol_object (void);
extern KLObject* get_cons_symbol_object (void);
extern KLObject* get_hd_symbol_object (void);
extern KLObject* get_tl_symbol_object (void);
extern KLObject* get_is_cons_symbol_object (void);
extern KLObject* get_defun_symbol_object (void);
extern KLObject* get_lambda_symbol_object (void);
extern KLObject* get_let_symbol_object (void);
extern KLObject* get_is_equal_symbol_object (void);
extern KLObject* get_eval_kl_symbol_object (void);
extern KLObject* get_freeze_symbol_object (void);
extern KLObject* get_type_symbol_object (void);
extern KLObject* get_absvector_symbol_object (void);
extern KLObject* get_set_absvector_element_symbol_object (void);
extern KLObject* get_get_absvector_element_symbol_object (void);
extern KLObject* get_is_absvector_symbol_object (void);
extern KLObject* get_write_byte_symbol_object (void);
extern KLObject* get_read_byte_symbol_object (void);
extern KLObject* get_open_symbol_object (void);
extern KLObject* get_close_symbol_object (void);
extern KLObject* get_get_time_symbol_object (void);
extern KLObject* get_add_symbol_object (void);
extern KLObject* get_subtract_symbol_object (void);
extern KLObject* get_multiply_symbol_object (void);
extern KLObject* get_divide_symbol_object (void);
extern KLObject* get_is_greater_symbol_object (void);
extern KLObject* get_is_less_symbol_object (void);
extern KLObject* get_is_greater_or_equal_symbol_object (void);
extern KLObject* get_is_less_or_equal_symbol_object (void);
extern KLObject* get_is_number_symbol_object (void);

extern KLObject** get_kl_function_arguments_with_count_check
(KLObject* function_object, Vector* arguments);

static inline void initialize_if_symbol_object (void)
{
  if_symbol_object = create_kl_symbol("if");
}

static inline void register_primitive_kl_function_if (void)
{
  initialize_if_symbol_object();
  extend_symbol_name_table("if", get_if_symbol_object());
}

static inline void initialize_and_symbol_object (void)
{
  and_symbol_object = create_kl_symbol("and");
}

static inline void register_primitive_kl_function_and (void)
{
  initialize_and_symbol_object();
  extend_symbol_name_table("and", get_and_symbol_object());
}

static inline void initialize_or_symbol_object (void)
{
  or_symbol_object = create_kl_symbol("or");
}

static inline void register_primitive_kl_function_or (void)
{
  initialize_or_symbol_object();
  extend_symbol_name_table("or", get_or_symbol_object());
}

static inline void initialize_cond_symbol_object (void)
{
  cond_symbol_object = create_kl_symbol("cond");
}

static inline void register_primitive_kl_function_cond (void)
{
  initialize_cond_symbol_object();
  extend_symbol_name_table("cond", get_cond_symbol_object());
}

static inline KLObject* primitive_function_intern
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);
  KLObject* string_object = objects[0];

  if (!is_kl_string(string_object))
    throw_kl_exception("Should be a string object");

  char* string = get_string(string_object);

  if (strcmp(string, "true") == 0)
    return get_true_boolean_object();
  else if (strcmp(string, "false") == 0)
    return get_false_boolean_object();

  KLObject* symbol_object = lookup_symbol_name_table(string);

  if (is_null(symbol_object)) {
    symbol_object = create_kl_symbol(string);
    extend_symbol_name_table(string, symbol_object);
  }

  return symbol_object;
}

static inline void initialize_intern_symbol_object (KLObject* function_object)
{
  intern_symbol_object = create_kl_symbol("intern");
  set_kl_symbol_function(intern_symbol_object, function_object);
}

static inline void register_primitive_kl_function_intern (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_intern);

  initialize_intern_symbol_object(function_object);
  extend_symbol_name_table("intern", get_intern_symbol_object());
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

static inline void initialize_pos_symbol_object (KLObject* function_object)
{
  pos_symbol_object = create_kl_symbol("pos");
  set_kl_symbol_function(pos_symbol_object, function_object);
}

static inline void register_primitive_kl_function_pos (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_pos);

  initialize_pos_symbol_object(function_object);
  extend_symbol_name_table("pos", get_pos_symbol_object());
}

static inline KLObject* primitive_function_tlstr
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return get_tail_kl_string(objects[0]);
}

static inline void initialize_tlstr_symbol_object (KLObject* function_object)
{
  tlstr_symbol_object = create_kl_symbol("tlstr");
  set_kl_symbol_function(tlstr_symbol_object, function_object);
}

static inline void register_primitive_kl_function_tlstr (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_tlstr);

  initialize_tlstr_symbol_object(function_object);
  extend_symbol_name_table("tlstr", get_tlstr_symbol_object());
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

static inline void initialize_cn_symbol_object (KLObject* function_object)
{
  cn_symbol_object = create_kl_symbol("cn");
  set_kl_symbol_function(cn_symbol_object, function_object);
}

static inline void register_primitive_kl_function_cn (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_cn);

  initialize_cn_symbol_object(function_object);
  extend_symbol_name_table("cn", get_cn_symbol_object());
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

  return create_kl_string(string);
}

static inline void initialize_str_symbol_object (KLObject* function_object)
{
  str_symbol_object = create_kl_symbol("str");
  set_kl_symbol_function(str_symbol_object, function_object);
}

static inline void register_primitive_kl_function_str (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_str);

  initialize_str_symbol_object(function_object);
  extend_symbol_name_table("str", get_str_symbol_object());
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

static inline void initialize_is_string_symbol_object (KLObject* function_object)
{
  is_string_symbol_object = create_kl_symbol("string?");
  set_kl_symbol_function(is_string_symbol_object, function_object);
}

static inline void register_primitive_kl_function_is_string (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_is_string);

  initialize_is_string_symbol_object(function_object);
  extend_symbol_name_table("string?", get_is_string_symbol_object());
}

static inline KLObject* primitive_function_n_to_string
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return kl_number_code_point_to_kl_string(objects[0]);
}

static inline void initialize_n_to_string_symbol_object
(KLObject* function_object)
{
  n_to_string_symbol_object = create_kl_symbol("n->string");
  set_kl_symbol_function(n_to_string_symbol_object, function_object);
}

static inline void register_primitive_kl_function_n_to_string (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_n_to_string);

  initialize_n_to_string_symbol_object(function_object);
  extend_symbol_name_table("n->string", get_n_to_string_symbol_object());
}

static inline KLObject* primitive_function_string_to_n
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return kl_string_to_kl_number_code_point(objects[0]);
}

static inline void initialize_string_to_n_symbol_object
(KLObject* function_object)
{
  string_to_n_symbol_object = create_kl_symbol("string->n");
  set_kl_symbol_function(string_to_n_symbol_object, function_object);
}

static inline void register_primitive_kl_function_string_to_n (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_string_to_n);

  initialize_string_to_n_symbol_object(function_object);
  extend_symbol_name_table("string->n", get_string_to_n_symbol_object());
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

static inline void initialize_set_symbol_object (KLObject* function_object)
{
  set_symbol_object = create_kl_symbol("set");
  set_kl_symbol_function(set_symbol_object, function_object);
}

static inline void register_primitive_kl_function_set (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_set);

  initialize_set_symbol_object(function_object);
  extend_symbol_name_table("set", get_set_symbol_object());
}

static inline KLObject* primitive_function_value
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return get_variable_value(objects[0], get_global_variable_environment());
}

static inline void initialize_value_symbol_object (KLObject* function_object)
{
  value_symbol_object = create_kl_symbol("value");
  set_kl_symbol_function(value_symbol_object, function_object);
}

static inline void register_primitive_kl_function_value (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_value);

  initialize_value_symbol_object(function_object);
  extend_symbol_name_table("value", get_value_symbol_object());
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

static inline void initialize_simple_error_symbol_object
(KLObject* function_object)
{
  simple_error_symbol_object = create_kl_symbol("simple-error");
  set_kl_symbol_function(simple_error_symbol_object, function_object);
}

static inline void register_primitive_kl_function_simple_error (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_simple_error);

  initialize_simple_error_symbol_object(function_object);
  extend_symbol_name_table("simple-error", get_simple_error_symbol_object());
}

static inline void initialize_trap_error_symbol_object (void)
{
  trap_error_symbol_object = create_kl_symbol("trap-error");
}

static inline void register_primitive_kl_function_trap_error (void)
{
  initialize_trap_error_symbol_object();
  extend_symbol_name_table("trap-error", get_trap_error_symbol_object());
}

static inline KLObject* primitive_function_error_to_string
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  if (!is_kl_exception(objects[0]))
    throw_kl_exception("Parameter is not an exception object");

  return create_kl_string(get_exception_error_message(get_exception(objects[0])));
}

static inline void initialize_error_to_string_symbol_object
(KLObject* function_object)
{
  error_to_string_symbol_object = create_kl_symbol("error-to-string");
  set_kl_symbol_function(error_to_string_symbol_object, function_object);
}

static inline void register_primitive_kl_function_error_to_string (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_error_to_string);

  initialize_error_to_string_symbol_object(function_object);
  extend_symbol_name_table("error-to-string",
                           get_error_to_string_symbol_object());
}

static inline KLObject* primitive_function_cons (KLObject* function_object,
                                                 Vector* arguments,
                                                 Environment* function_environment,
                                                 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return create_kl_list(objects[0], objects[1]);
}

static inline void initialize_cons_symbol_object (KLObject* function_object)
{
  cons_symbol_object = create_kl_symbol("cons");
  set_kl_symbol_function(cons_symbol_object, function_object);
}

static inline void register_primitive_kl_function_cons (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_cons);

  initialize_cons_symbol_object(function_object);
  extend_symbol_name_table("cons", get_cons_symbol_object());
}

static inline KLObject* primitive_function_hd (KLObject* function_object,
                                               Vector* arguments,
                                               Environment* function_environment,
                                               Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return get_head_kl_list(objects[0]);
}

static inline void initialize_hd_symbol_object (KLObject* function_object)
{
  hd_symbol_object = create_kl_symbol("hd");
  set_kl_symbol_function(hd_symbol_object, function_object);
}

static inline void register_primitive_kl_function_hd (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_hd);

  initialize_hd_symbol_object(function_object);
  extend_symbol_name_table("hd", get_hd_symbol_object());
}

static inline KLObject* primitive_function_tl (KLObject* function_object,
                                               Vector* arguments,
                                               Environment* function_environment,
                                               Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return get_tail_kl_list(objects[0]);
}

static inline void initialize_tl_symbol_object (KLObject* function_object)
{
  tl_symbol_object = create_kl_symbol("tl");
  set_kl_symbol_function(tl_symbol_object, function_object);
}

static inline void register_primitive_kl_function_tl (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_tl);

  initialize_tl_symbol_object(function_object);
  extend_symbol_name_table("tl", get_tl_symbol_object());
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

static inline void initialize_is_cons_symbol_object (KLObject* function_object)
{
  is_cons_symbol_object = create_kl_symbol("cons?");
  set_kl_symbol_function(is_cons_symbol_object, function_object);
}

static inline void register_primitive_kl_function_is_cons (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_is_cons);

  initialize_is_cons_symbol_object(function_object);
  extend_symbol_name_table("cons?", get_is_cons_symbol_object());
}

static inline void initialize_defun_symbol_object (void)
{
  defun_symbol_object = create_kl_symbol("defun");
}

static inline void register_primitive_kl_function_defun (void)
{
  initialize_defun_symbol_object();
  extend_symbol_name_table("defun", get_defun_symbol_object());
}

static inline void initialize_lambda_symbol_object (void)
{
  lambda_symbol_object = create_kl_symbol("lambda");
}

static inline void register_primitive_kl_function_lambda (void)
{
  initialize_lambda_symbol_object();
  extend_symbol_name_table("lambda", get_lambda_symbol_object());
}

static inline void initialize_let_symbol_object (void)
{
  let_symbol_object = create_kl_symbol("let");
}

static inline void register_primitive_kl_function_let (void)
{
  initialize_let_symbol_object();
  extend_symbol_name_table("let", get_let_symbol_object());
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

static inline void initialize_is_equal_symbol_object (KLObject* function_object)
{
  is_equal_symbol_object = create_kl_symbol("=");
  set_kl_symbol_function(is_equal_symbol_object, function_object);
}

static inline void register_primitive_kl_function_is_equal (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_is_equal);

  initialize_is_equal_symbol_object(function_object);
  extend_symbol_name_table("=", get_is_equal_symbol_object());
}

static inline void initialize_eval_kl_symbol_object (void)
{
  eval_kl_symbol_object = create_kl_symbol("eval-kl");
}

static inline void register_primitive_kl_function_eval_kl (void)
{
  initialize_eval_kl_symbol_object();
  extend_symbol_name_table("eval-kl", get_eval_kl_symbol_object());
}

static inline void initialize_freeze_symbol_object (void)
{
  freeze_symbol_object = create_kl_symbol("freeze");
}

static inline void register_primitive_kl_function_freeze (void)
{
  initialize_freeze_symbol_object();
  extend_symbol_name_table("freeze", get_freeze_symbol_object());
}

static inline KLObject* primitive_function_type
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return objects[0];
}

static inline void initialize_type_symbol_object (KLObject* function_object)
{
  type_symbol_object = create_kl_symbol("type");
  set_kl_symbol_function(type_symbol_object, function_object);
}

static inline void register_primitive_kl_function_type (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_type);

  initialize_type_symbol_object(function_object);
  extend_symbol_name_table("type", get_type_symbol_object());
}

static inline KLObject* primitive_function_absvector
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return create_kl_vector((size_t)get_kl_number_number_l(objects[0]));
}

static inline void initialize_absvector_symbol_object (KLObject* function_object)
{
  absvector_symbol_object = create_kl_symbol("absvector");
  set_kl_symbol_function(absvector_symbol_object, function_object);
}

static inline void register_primitive_kl_function_absvector (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_absvector);

  initialize_absvector_symbol_object(function_object);
  extend_symbol_name_table("absvector", get_absvector_symbol_object());
}

static inline KLObject* primitive_function_set_absvector_element
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return set_kl_vector_element(objects[0], objects[1], objects[2]);
}

static inline void initialize_set_absvector_element_symbol_object
(KLObject* function_object)
{
  set_absvector_element_symbol_object = create_kl_symbol("address->");
  set_kl_symbol_function(set_absvector_element_symbol_object, function_object);
}

static inline void register_primitive_kl_function_set_absvector_element (void)
{
  KLObject* function_object =
    create_primitive_kl_function(3, &primitive_function_set_absvector_element);

  initialize_set_absvector_element_symbol_object(function_object);
  extend_symbol_name_table("address->", get_set_absvector_element_symbol_object());
}

static inline KLObject* primitive_function_get_absvector_element
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return get_kl_vector_element(objects[0], objects[1]);
}

static inline void initialize_get_absvector_element_symbol_object
(KLObject* function_object)
{
  get_absvector_element_symbol_object = create_kl_symbol("<-address");
  set_kl_symbol_function(get_absvector_element_symbol_object, function_object);
}

static inline void register_primitive_kl_function_get_absvector_element (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_get_absvector_element);

  initialize_get_absvector_element_symbol_object(function_object);
  extend_symbol_name_table("<-address",
                           get_get_absvector_element_symbol_object());
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

static inline void initialize_is_absvector_symbol_object
(KLObject* function_object)
{
  is_absvector_symbol_object = create_kl_symbol("absvector?");
  set_kl_symbol_function(is_absvector_symbol_object, function_object);
}

static inline void register_primitive_kl_function_is_absvector (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_is_absvector);

  initialize_is_absvector_symbol_object(function_object);
  extend_symbol_name_table("absvector?", get_is_absvector_symbol_object());
}

static inline KLObject* primitive_function_write_byte
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return write_kl_stream_byte(objects[1], objects[0]);
}

static inline void initialize_write_byte_symbol_object (KLObject* function_object)
{
  write_byte_symbol_object = create_kl_symbol("write-byte");
  set_kl_symbol_function(write_byte_symbol_object, function_object);
}

static inline void register_primitive_kl_function_write_byte (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_write_byte);

  initialize_write_byte_symbol_object(function_object);
  extend_symbol_name_table("write-byte", get_write_byte_symbol_object());
}

static inline KLObject* primitive_function_read_byte
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return read_kl_stream_byte(objects[0]);
}

static inline void initialize_read_byte_symbol_object (KLObject* function_object)
{
  read_byte_symbol_object = create_kl_symbol("read-byte");
  set_kl_symbol_function(read_byte_symbol_object, function_object);
}

static inline void register_primitive_kl_function_read_byte (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_read_byte);

  initialize_read_byte_symbol_object(function_object);
  extend_symbol_name_table("read-byte", get_read_byte_symbol_object());
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

  if (strcmp(home_directory_string, "") == 0)
    return create_kl_stream(get_string(objects[0]), objects[1]);

  char* file_path = concatenate_string(home_directory_string,
                                       get_string(objects[0]));

  return create_kl_stream(file_path, objects[1]);
}

static inline void initialize_open_symbol_object (KLObject* function_object)
{
  open_symbol_object = create_kl_symbol("open");
  set_kl_symbol_function(open_symbol_object, function_object);
}

static inline void register_primitive_kl_function_open (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_open);

  initialize_open_symbol_object(function_object);
  extend_symbol_name_table("open", get_open_symbol_object());
}

static inline KLObject* primitive_function_close
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return close_kl_stream(objects[0]);
}

static inline void initialize_close_symbol_object (KLObject* function_object)
{
  close_symbol_object = create_kl_symbol("close");
  set_kl_symbol_function(close_symbol_object, function_object);
}

static inline void register_primitive_kl_function_close (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_close);

  initialize_close_symbol_object(function_object);
  extend_symbol_name_table("close", get_close_symbol_object());
}

static inline KLObject* primitive_function_get_time
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return get_kl_number_time(objects[0]);
}

static inline void initialize_get_time_symbol_object (KLObject* function_object)
{
  get_time_symbol_object = create_kl_symbol("get-time");
  set_kl_symbol_function(get_time_symbol_object, function_object);
}

static inline void register_primitive_kl_function_get_time (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_get_time);

  initialize_get_time_symbol_object(function_object);
  extend_symbol_name_table("get-time", get_get_time_symbol_object());
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

static inline void initialize_add_symbol_object (KLObject* function_object)
{
  add_symbol_object = create_kl_symbol("+");
  set_kl_symbol_function(add_symbol_object, function_object);
}

static inline void register_primitive_kl_function_add (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_add);

  initialize_add_symbol_object(function_object);
  extend_symbol_name_table("+", get_add_symbol_object());
}

static inline KLObject* primitive_function_subtract
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return subtract_kl_number(objects[0], objects[1]);
}

static inline void initialize_subtract_symbol_object (KLObject* function_object)
{
  subtract_symbol_object = create_kl_symbol("-");
  set_kl_symbol_function(subtract_symbol_object, function_object);
}

static inline void register_primitive_kl_function_subtract (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_subtract);

  initialize_subtract_symbol_object(function_object);
  extend_symbol_name_table("-", get_subtract_symbol_object());
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

static inline void initialize_multiply_symbol_object (KLObject* function_object)
{
  multiply_symbol_object = create_kl_symbol("*");
  set_kl_symbol_function(multiply_symbol_object, function_object);
}

static inline void register_primitive_kl_function_multiply (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_multiply);

  initialize_multiply_symbol_object(function_object);
  extend_symbol_name_table("*", get_multiply_symbol_object());
}

static inline KLObject* primitive_function_divide
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return divide_kl_number(objects[0], objects[1]);
}

static inline void initialize_divide_symbol_object (KLObject* function_object)
{
  divide_symbol_object = create_kl_symbol("/");
  set_kl_symbol_function(divide_symbol_object, function_object);
}

static inline void register_primitive_kl_function_divide (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_divide);

  initialize_divide_symbol_object(function_object);
  extend_symbol_name_table("/", get_divide_symbol_object());
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

static inline void initialize_is_greater_symbol_object (KLObject* function_object)
{
  is_greater_symbol_object = create_kl_symbol(">");
  set_kl_symbol_function(is_greater_symbol_object, function_object);
}

static inline void register_primitive_kl_function_is_greater (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_is_greater);

  initialize_is_greater_symbol_object(function_object);
  extend_symbol_name_table(">", get_is_greater_symbol_object());
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

static inline void initialize_is_less_symbol_object (KLObject* function_object)
{
  is_less_symbol_object = create_kl_symbol("<");
  set_kl_symbol_function(is_less_symbol_object, function_object);
}

static inline void register_primitive_kl_function_is_less (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_is_less);

  initialize_is_less_symbol_object(function_object);
  extend_symbol_name_table("<", get_is_less_symbol_object());
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

static inline void initialize_is_greater_or_equal_symbol_object
(KLObject* function_object)
{
  is_greater_or_equal_symbol_object = create_kl_symbol(">=");
  set_kl_symbol_function(is_greater_or_equal_symbol_object, function_object);
}

static inline void register_primitive_kl_function_is_greater_or_equal (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_is_greater_or_equal);

  initialize_is_greater_or_equal_symbol_object(function_object);
  extend_symbol_name_table(">=", get_is_greater_or_equal_symbol_object());
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

static inline void initialize_is_less_or_equal_symbol_object
(KLObject* function_object)
{
  is_less_or_equal_symbol_object = create_kl_symbol("<=");
  set_kl_symbol_function(is_less_or_equal_symbol_object, function_object);
}

static inline void register_primitive_kl_function_is_less_or_equal (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_is_less_or_equal);

  initialize_is_less_or_equal_symbol_object(function_object);
  extend_symbol_name_table("<=", get_is_less_or_equal_symbol_object());
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

static inline void initialize_is_number_symbol_object (KLObject* function_object)
{
  is_number_symbol_object = create_kl_symbol("number?");
  set_kl_symbol_function(is_number_symbol_object, function_object);
}

static inline void register_primitive_kl_function_is_number (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_is_number);

  initialize_is_number_symbol_object(function_object);
  extend_symbol_name_table("number?", get_is_number_symbol_object());
}

void register_primitive_kl_functions (void)
{
  register_primitive_kl_function_if();
  register_primitive_kl_function_and();
  register_primitive_kl_function_or();
  register_primitive_kl_function_cond();
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
  register_primitive_kl_function_trap_error();
  register_primitive_kl_function_error_to_string();
  register_primitive_kl_function_cons();
  register_primitive_kl_function_hd();
  register_primitive_kl_function_tl();
  register_primitive_kl_function_is_cons();
  register_primitive_kl_function_defun();
  register_primitive_kl_function_lambda();
  register_primitive_kl_function_let();
  register_primitive_kl_function_is_equal();
  register_primitive_kl_function_eval_kl();
  register_primitive_kl_function_freeze();
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
