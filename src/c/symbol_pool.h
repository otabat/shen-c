#ifndef SHEN_C_SYMBOL_POOL_H
#define SHEN_C_SYMBOL_POOL_H

#include "kl.h"
#include "symbol.h"

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

extern KLObject* in_symbol_object;
extern KLObject* out_symbol_object;

extern KLObject* unix_symbol_object;
extern KLObject* run_symbol_object;

extern KLObject* exit_symbol_object;
extern KLObject* hash_symbol_object;
extern KLObject* is_symbol_symbol_object;
extern KLObject* is_integer_symbol_object;
extern KLObject* is_boolean_symbol_object;
extern KLObject* is_variable_symbol_object;
extern KLObject* not_symbol_object;
extern KLObject* value_slash_or_symbol_object;
extern KLObject* get_absvector_element_slash_or_symbol_object;
extern KLObject* map_symbol_object;
extern KLObject* reverse_symbol_object;
extern KLObject* append_symbol_object;
extern KLObject* is_element_symbol_object;
extern KLObject* shen_is_numbyte_symbol_object;
extern KLObject* shen_byte_to_digit_symbol_object;
extern KLObject* read_file_as_charlist_symbol_object;
extern KLObject* shen_pvar_symbol_object;
extern KLObject* shen_is_pvar_symbol_object;
extern KLObject* shen_earmuff_prologvectors_symbol_object;
extern KLObject* shen_valvector_symbol_object;
extern KLObject* shen_dash_null_symbol_object;
extern KLObject* shen_lazyderef_symbol_object;
extern KLObject* shen_deref_symbol_object;
extern KLObject* shen_is_occurs_symbol_object;
extern KLObject* shen_compose_symbol_object;

extern KLObject* println_symbol_object;
extern KLObject* quit_symbol_object;
extern KLObject* loop_symbol_object;
extern KLObject* recur_symbol_object;
extern KLObject* quote_symbol_object;

void register_symbol_objects (void);

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

inline KLObject* get_in_symbol_object (void) { return in_symbol_object; }
inline KLObject* get_out_symbol_object (void) { return out_symbol_object; }

inline KLObject* get_unix_symbol_object (void) { return unix_symbol_object; }
inline KLObject* get_run_symbol_object (void) { return run_symbol_object; }

inline KLObject* get_exit_symbol_object (void) { return exit_symbol_object; }
inline KLObject* get_hash_symbol_object (void) { return hash_symbol_object; }

inline KLObject* get_is_symbol_symbol_object (void)
{
  return is_symbol_symbol_object;
}

inline KLObject* get_is_integer_symbol_object (void)
{
  return is_integer_symbol_object;
}

inline KLObject* get_is_boolean_symbol_object (void)
{
  return is_boolean_symbol_object;
}

inline KLObject* get_is_variable_symbol_object (void)
{
  return is_variable_symbol_object;
}

inline KLObject* get_not_symbol_object (void) { return not_symbol_object; }

inline KLObject* get_value_slash_or_symbol_object (void)
{
  return value_slash_or_symbol_object;
}

inline KLObject* get_get_absvector_element_slash_or_symbol_object (void)
{
  return get_absvector_element_slash_or_symbol_object;
}

inline KLObject* get_map_symbol_object (void) { return map_symbol_object; }
inline KLObject* get_reverse_symbol_object (void) { return reverse_symbol_object; }
inline KLObject* get_append_symbol_object (void) { return append_symbol_object; }

inline KLObject* get_is_element_symbol_object (void)
{
  return is_element_symbol_object;
}

inline KLObject* get_shen_is_numbyte_symbol_object (void)
{
  return shen_is_numbyte_symbol_object;
}

inline KLObject* get_shen_byte_to_digit_symbol_object (void)
{
  return shen_byte_to_digit_symbol_object;
}

inline KLObject* get_read_file_as_charlist_symbol_object (void)
{
  return read_file_as_charlist_symbol_object;
}

inline KLObject* get_shen_pvar_symbol_object (void)
{
  return shen_pvar_symbol_object;
}

inline KLObject* get_shen_is_pvar_symbol_object (void)
{
  return shen_is_pvar_symbol_object;
}

inline KLObject* get_shen_earmuff_prologvectors_symbol_object (void)
{
  return shen_earmuff_prologvectors_symbol_object;
}

inline KLObject* get_shen_valvector_symbol_object (void)
{
  return shen_valvector_symbol_object;
}

inline KLObject* get_shen_dash_null_symbol_object (void)
{
  return shen_dash_null_symbol_object;
}
inline KLObject* get_shen_lazyderef_symbol_object (void)
{
  return shen_lazyderef_symbol_object;
}

inline KLObject* get_shen_deref_symbol_object (void)
{
  return shen_deref_symbol_object;
}

inline KLObject* get_shen_is_occurs_symbol_object (void)
{
  return shen_is_occurs_symbol_object;
}

inline KLObject* get_shen_compose_symbol_object (void)
{
  return shen_compose_symbol_object;
}

inline KLObject* get_println_symbol_object (void) { return println_symbol_object; }
inline KLObject* get_quit_symbol_object (void) { return quit_symbol_object; }
inline KLObject* get_loop_symbol_object (void) { return loop_symbol_object; }
inline KLObject* get_recur_symbol_object (void) { return recur_symbol_object; }
inline KLObject* get_quote_symbol_object (void) { return quote_symbol_object; }

#endif
