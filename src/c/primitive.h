#ifndef SHEN_C_PRIMITIVE_H
#define SHEN_C_PRIMITIVE_H

#include "boolean.h"
#include "exception.h"
#include "function.h"
#include "kl.h"
#include "list.h"
#include "object.h"
#include "stream.h"
#include "string.h"
#include "symbol.h"
#include "system.h"
#include "variable.h"
#include "vector.h"

extern KLObject* if_symbol_object;
extern KLObject* and_symbol_object;
extern KLObject* or_symbol_object;
extern KLObject* cond_symbol_object;
extern KLObject* intern_symbol_object;
extern KLObject* pos_symbol_object;
extern KLObject* tlstr_symbol_object;
extern KLObject* cn_symbol_object;
extern KLObject* str_symbol_object;
extern KLObject* is_string_symbol_object;
extern KLObject* n_to_string_symbol_object;
extern KLObject* string_to_n_symbol_object;
extern KLObject* set_symbol_object;
extern KLObject* value_symbol_object;
extern KLObject* simple_error_symbol_object;
extern KLObject* trap_error_symbol_object;
extern KLObject* error_to_string_symbol_object;
extern KLObject* cons_symbol_object;
extern KLObject* hd_symbol_object;
extern KLObject* tl_symbol_object;
extern KLObject* is_cons_symbol_object;
extern KLObject* defun_symbol_object;
extern KLObject* lambda_symbol_object;
extern KLObject* let_symbol_object;
extern KLObject* is_equal_symbol_object;
extern KLObject* eval_kl_symbol_object;
extern KLObject* freeze_symbol_object;
extern KLObject* type_symbol_object;
extern KLObject* absvector_symbol_object;
extern KLObject* set_absvector_element_symbol_object;
extern KLObject* get_absvector_element_symbol_object;
extern KLObject* is_absvector_symbol_object;
extern KLObject* write_byte_symbol_object;
extern KLObject* read_byte_symbol_object;
extern KLObject* open_symbol_object;
extern KLObject* close_symbol_object;
extern KLObject* get_time_symbol_object;
extern KLObject* add_symbol_object;
extern KLObject* subtract_symbol_object;
extern KLObject* multiply_symbol_object;
extern KLObject* divide_symbol_object;
extern KLObject* is_greater_symbol_object;
extern KLObject* is_less_symbol_object;
extern KLObject* is_greater_or_equal_symbol_object;
extern KLObject* is_less_or_equal_symbol_object;
extern KLObject* is_number_symbol_object;

void register_primitive_kl_functions (void);

inline KLObject* get_if_symbol_object (void) { return if_symbol_object; }
inline KLObject* get_and_symbol_object (void) { return and_symbol_object; }
inline KLObject* get_or_symbol_object (void) { return or_symbol_object; }
inline KLObject* get_cond_symbol_object (void) { return cond_symbol_object; }
inline KLObject* get_intern_symbol_object (void) { return intern_symbol_object; }
inline KLObject* get_pos_symbol_object (void) { return pos_symbol_object; }
inline KLObject* get_tlstr_symbol_object (void) { return tlstr_symbol_object; }
inline KLObject* get_cn_symbol_object (void) { return cn_symbol_object; }
inline KLObject* get_str_symbol_object (void) { return str_symbol_object; }

inline KLObject* get_is_string_symbol_object (void)
{
  return is_string_symbol_object;
}

inline KLObject* get_n_to_string_symbol_object (void)
{
  return n_to_string_symbol_object;
}

inline KLObject* get_string_to_n_symbol_object (void)
{
  return string_to_n_symbol_object;
}

inline KLObject* get_set_symbol_object (void) { return set_symbol_object; }
inline KLObject* get_value_symbol_object (void) { return value_symbol_object; }

inline KLObject* get_simple_error_symbol_object (void)
{
  return simple_error_symbol_object;
}

inline KLObject* get_trap_error_symbol_object (void)
{
  return trap_error_symbol_object;
}

inline KLObject* get_error_to_string_symbol_object (void)
{
  return error_to_string_symbol_object;
}

inline KLObject* get_cons_symbol_object (void) { return cons_symbol_object; }
inline KLObject* get_hd_symbol_object (void) { return hd_symbol_object; }
inline KLObject* get_tl_symbol_object (void) { return tl_symbol_object; }
inline KLObject* get_is_cons_symbol_object (void) { return is_cons_symbol_object; }
inline KLObject* get_defun_symbol_object (void) { return defun_symbol_object; }
inline KLObject* get_lambda_symbol_object (void) { return lambda_symbol_object; }
inline KLObject* get_let_symbol_object (void) { return let_symbol_object; }

inline KLObject* get_is_equal_symbol_object (void)
{
  return is_equal_symbol_object;
}

inline KLObject* get_eval_kl_symbol_object (void) { return eval_kl_symbol_object; }
inline KLObject* get_freeze_symbol_object (void) { return freeze_symbol_object; }
inline KLObject* get_type_symbol_object (void) { return type_symbol_object; }

inline KLObject* get_absvector_symbol_object (void)
{
  return absvector_symbol_object;
}

inline KLObject* get_set_absvector_element_symbol_object (void)
{
  return set_absvector_element_symbol_object;
}

inline KLObject* get_get_absvector_element_symbol_object (void)
{
  return get_absvector_element_symbol_object;
}

inline KLObject* get_is_absvector_symbol_object (void)
{
  return is_absvector_symbol_object;
}

inline KLObject* get_write_byte_symbol_object (void)
{
  return write_byte_symbol_object;
}

inline KLObject* get_read_byte_symbol_object (void)
{
  return read_byte_symbol_object;
}

inline KLObject* get_open_symbol_object (void) { return open_symbol_object; }
inline KLObject* get_close_symbol_object (void) { return close_symbol_object; }

inline KLObject* get_get_time_symbol_object (void)
{
  return get_time_symbol_object;
}

inline KLObject* get_add_symbol_object (void) { return add_symbol_object; }

inline KLObject* get_subtract_symbol_object (void)
{
  return subtract_symbol_object;
}

inline KLObject* get_multiply_symbol_object (void)
{
  return multiply_symbol_object;
}

inline KLObject* get_divide_symbol_object (void) { return divide_symbol_object; }

inline KLObject* get_is_greater_symbol_object (void)
{
  return is_greater_symbol_object;
}

inline KLObject* get_is_less_symbol_object (void) { return is_less_symbol_object; }

inline KLObject* get_is_greater_or_equal_symbol_object (void)
{
  return is_greater_or_equal_symbol_object;
}

inline KLObject* get_is_less_or_equal_symbol_object (void)
{
  return is_less_or_equal_symbol_object;
}

inline KLObject* get_is_number_symbol_object (void)
{
  return is_number_symbol_object;
}

inline KLObject** get_kl_function_arguments_with_count_check
(KLObject* function_object, Vector* arguments)
{
  PrimitiveFunction* primitive_function =
    get_kl_function_primitive_function(function_object);
  size_t argument_size = (is_null(arguments)) ? 0 : get_vector_size(arguments);
  size_t parameter_size =
    get_primitive_function_parameter_size(primitive_function);

  check_function_argument_size(argument_size, parameter_size);

  return (is_null(arguments))? NULL : get_vector_objects(arguments);
}

#endif
