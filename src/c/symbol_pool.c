#include "symbol_pool.h"

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

KLObject* in_symbol_object;
KLObject* out_symbol_object;

KLObject* unix_symbol_object;
KLObject* run_symbol_object;

KLObject* exit_symbol_object;
KLObject* slash_dot_symbol_object;
KLObject* shen_ebr_symbol_object;
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
KLObject* append_symbol_object;
KLObject* is_element_symbol_object;
KLObject* assoc_symbol_object;
KLObject* occurrences_symbol_object;
KLObject* nth_symbol_object;
KLObject* limit_symbol_object;
KLObject* dict_symbol_object;
KLObject* is_dict_symbol_object;
KLObject* dict_count_symbol_object;
KLObject* get_dict_value_symbol_object;
KLObject* get_dict_value_slash_or_symbol_object;
KLObject* set_dict_value_symbol_object;
KLObject* dict_rm_symbol_object;
KLObject* dict_keys_symbol_object;
KLObject* dict_values_symbol_object;
KLObject* dict_fold_symbol_object;
KLObject* length_symbol_object;
KLObject* shen_fail_exclamation_symbol_object;
KLObject* shen_hdtl_symbol_object;
KLObject* shen_is_numbyte_symbol_object;
KLObject* shen_byte_to_digit_symbol_object;
KLObject* read_file_as_charlist_symbol_object;
KLObject* shen_pvar_symbol_object;
KLObject* shen_is_pvar_symbol_object;
KLObject* shen_earmuff_prologvectors_symbol_object;
KLObject* shen_earmuff_varcounter_symbol_object;
KLObject* shen_valvector_symbol_object;
KLObject* shen_dash_null_symbol_object;
KLObject* shen_lazyderef_symbol_object;
KLObject* shen_deref_symbol_object;
KLObject* shen_is_occurs_symbol_object;
KLObject* shen_bindv_symbol_object;
KLObject* shen_unbindv_symbol_object;
KLObject* bind_symbol_object;
KLObject* shen_lzy_equal_exclamation_symbol_object;
KLObject* shen_mk_pvar_symbol_object;
KLObject* shen_copy_vector_symbol_object;
KLObject* shen_resize_vector_symbol_object;
KLObject* shen_resizeprocessvector_symbol_object;
KLObject* shen_newpv_symbol_object;
KLObject* shen_list_to_str_symbol_object;
KLObject* shen_str_to_str_symbol_object;
KLObject* shen_vector_to_str_symbol_object;
KLObject* shen_atom_to_str_symbol_object;
KLObject* shen_arg_to_str_symbol_object;
KLObject* shen_compose_symbol_object;

KLObject* c_loop_symbol_object;
KLObject* c_recur_symbol_object;
KLObject* c_quote_symbol_object;
KLObject* c_mcons_symbol_object;
KLObject* c_ocons_symbol_object;
KLObject* c_nth_hd_symbol_object;
KLObject* c_nth_tl_symbol_object;
KLObject* c_flush_symbol_object;

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

extern KLObject* get_in_symbol_object (void);
extern KLObject* get_out_symbol_object (void);

extern KLObject* get_unix_symbol_object (void);
extern KLObject* get_run_symbol_object (void);

extern KLObject* get_exit_symbol_object (void);
extern KLObject* get_slash_dot_symbol_object (void);
extern KLObject* get_shen_ebr_symbol_object (void);
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
extern KLObject* get_append_symbol_object (void);
extern KLObject* get_is_element_symbol_object (void);
extern KLObject* get_assoc_symbol_object (void);
extern KLObject* get_occurrences_symbol_object (void);
extern KLObject* get_nth_symbol_object (void);
extern KLObject* get_limit_symbol_object (void);
extern KLObject* get_dict_symbol_object (void);
extern KLObject* get_is_dict_symbol_object (void);
extern KLObject* get_dict_count_symbol_object (void);
extern KLObject* get_get_dict_value_symbol_object (void);
extern KLObject* get_get_dict_value_slash_or_symbol_object (void);
extern KLObject* get_set_dict_value_symbol_object (void);
extern KLObject* get_dict_rm_symbol_object (void);
extern KLObject* get_dict_keys_symbol_object (void);
extern KLObject* get_dict_values_symbol_object (void);
extern KLObject* get_dict_fold_symbol_object (void);
extern KLObject* get_length_symbol_object (void);
extern KLObject* get_shen_fail_exclamation_symbol_object (void);
extern KLObject* get_shen_hdtl_symbol_object (void);
extern KLObject* get_shen_is_numbyte_symbol_object (void);
extern KLObject* get_shen_byte_to_digit_symbol_object (void);
extern KLObject* get_read_file_as_charlist_symbol_object (void);
extern KLObject* get_shen_pvar_symbol_object (void);
extern KLObject* get_shen_is_pvar_symbol_object (void);
extern KLObject* get_shen_earmuff_prologvectors_symbol_object (void);
extern KLObject* get_shen_earmuff_varcounter_symbol_object (void);
extern KLObject* get_shen_valvector_symbol_object (void);
extern KLObject* get_shen_dash_null_symbol_object (void);
extern KLObject* get_shen_lazyderef_symbol_object (void);
extern KLObject* get_shen_deref_symbol_object (void);
extern KLObject* get_shen_is_occurs_symbol_object (void);
extern KLObject* get_shen_bindv_symbol_object (void);
extern KLObject* get_shen_unbindv_symbol_object (void);
extern KLObject* get_bind_symbol_object (void);
extern KLObject* get_shen_lzy_equal_exclamation_symbol_object (void);
extern KLObject* get_shen_mk_pvar_symbol_object (void);
extern KLObject* get_shen_copy_vector_symbol_object (void);
extern KLObject* get_shen_resize_vector_symbol_object (void);
extern KLObject* get_shen_resizeprocessvector_symbol_object (void);
extern KLObject* get_shen_newpv_symbol_object (void);
extern KLObject* get_shen_list_to_str_symbol_object (void);
extern KLObject* get_shen_str_to_str_symbol_object (void);
extern KLObject* get_shen_vector_to_str_symbol_object (void);
extern KLObject* get_shen_atom_to_str_symbol_object (void);
extern KLObject* get_shen_arg_to_str_symbol_object (void);
extern KLObject* get_shen_compose_symbol_object (void);

extern KLObject* get_c_loop_symbol_object (void);
extern KLObject* get_c_recur_symbol_object (void);
extern KLObject* get_c_quote_symbol_object (void);
extern KLObject* get_c_mcons_symbol_object (void);
extern KLObject* get_c_ocons_symbol_object (void);
extern KLObject* get_c_nth_hd_symbol_object (void);
extern KLObject* get_c_nth_tl_symbol_object (void);
extern KLObject* get_c_flush_symbol_object (void);

static inline void register_if_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("if");
  if_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, if_symbol_object);
}

static inline void register_and_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("and");
  and_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, and_symbol_object);
}

static inline void register_or_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("or");
  or_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, or_symbol_object);
}

static inline void register_cond_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("cond");
  cond_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, cond_symbol_object);
}

static inline void register_intern_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("intern");
  intern_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, intern_symbol_object);
}

static inline void register_pos_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("pos");
  pos_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, pos_symbol_object);
}

static inline void register_tlstr_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("tlstr");
  tlstr_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, tlstr_symbol_object);
}

static inline void register_cn_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("cn");
  cn_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, cn_symbol_object);
}

static inline void register_str_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("str");
  str_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, str_symbol_object);
}

static inline void register_is_string_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("string?");
  is_string_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, is_string_symbol_object);
}

static inline void register_n_to_string_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("n->string");
  n_to_string_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, n_to_string_symbol_object);
}

static inline void register_string_to_n_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("string->n");
  string_to_n_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, string_to_n_symbol_object);
}

static inline void register_set_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("set");
  set_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, set_symbol_object);
}

static inline void register_value_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("value");
  value_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, value_symbol_object);
}

static inline void register_simple_error_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("simple-error");
  simple_error_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, simple_error_symbol_object);
}

static inline void register_trap_error_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("trap-error");
  trap_error_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, trap_error_symbol_object);
}

static inline void register_error_to_string_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("error-to-string");
  error_to_string_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, error_to_string_symbol_object);
}

static inline void register_cons_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("cons");
  cons_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, cons_symbol_object);
}

static inline void register_hd_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("hd");
  hd_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, hd_symbol_object);
}

static inline void register_tl_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("tl");
  tl_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, tl_symbol_object);
}

static inline void register_is_cons_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("cons?");
  is_cons_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, is_cons_symbol_object);
}

static inline void register_defun_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("defun");
  defun_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, defun_symbol_object);
}

static inline void register_lambda_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("lambda");
  lambda_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, lambda_symbol_object);
}

static inline void register_let_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("let");
  let_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, let_symbol_object);
}

static inline void register_is_equal_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("=");
  is_equal_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, is_equal_symbol_object);
}

static inline void register_eval_kl_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("eval-kl");
  eval_kl_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, eval_kl_symbol_object);
}

static inline void register_freeze_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("freeze");
  freeze_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, freeze_symbol_object);
}

static inline void register_type_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("type");
  type_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, type_symbol_object);
}

static inline void register_absvector_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("absvector");
  absvector_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, absvector_symbol_object);
}

static inline void register_set_absvector_element_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("address->");
  set_absvector_element_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, set_absvector_element_symbol_object);
}

static inline void register_get_absvector_element_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("<-address");
  get_absvector_element_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, get_absvector_element_symbol_object);
}

static inline void register_is_absvector_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("absvector?");
  is_absvector_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, is_absvector_symbol_object);
}

static inline void register_write_byte_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("write-byte");
  write_byte_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, write_byte_symbol_object);
}

static inline void register_read_byte_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("read-byte");
  read_byte_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, read_byte_symbol_object);
}

static inline void register_open_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("open");
  open_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, open_symbol_object);
}

static inline void register_close_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("close");
  close_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, close_symbol_object);
}

static inline void register_get_time_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("get-time");
  get_time_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, get_time_symbol_object);
}

static inline void register_add_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("+");
  add_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, add_symbol_object);
}

static inline void register_subtract_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("-");
  subtract_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, subtract_symbol_object);
}

static inline void register_multiply_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("*");
  multiply_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, multiply_symbol_object);
}

static inline void register_divide_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("/");
  divide_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, divide_symbol_object);
}

static inline void register_is_greater_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern(">");
  is_greater_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, is_greater_symbol_object);
}

static inline void register_is_less_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("<");
  is_less_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, is_less_symbol_object);
}

static inline void register_is_greater_or_equal_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern(">=");
  is_greater_or_equal_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, is_greater_or_equal_symbol_object);
}

static inline void register_is_less_or_equal_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("<=");
  is_less_or_equal_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, is_less_or_equal_symbol_object);
}

static inline void register_is_number_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("number?");
  is_number_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, is_number_symbol_object);
}

static inline void register_primitive_symbol_objects (void)
{
  register_if_symbol_object();
  register_and_symbol_object();
  register_or_symbol_object();
  register_cond_symbol_object();
  register_intern_symbol_object();
  register_pos_symbol_object();
  register_tlstr_symbol_object();
  register_cn_symbol_object();
  register_str_symbol_object();
  register_is_string_symbol_object();
  register_n_to_string_symbol_object();
  register_string_to_n_symbol_object();
  register_set_symbol_object();
  register_value_symbol_object();
  register_simple_error_symbol_object();
  register_trap_error_symbol_object();
  register_error_to_string_symbol_object();
  register_cons_symbol_object();
  register_hd_symbol_object();
  register_tl_symbol_object();
  register_is_cons_symbol_object();
  register_defun_symbol_object();
  register_lambda_symbol_object();
  register_let_symbol_object();
  register_is_equal_symbol_object();
  register_eval_kl_symbol_object();
  register_freeze_symbol_object();
  register_type_symbol_object();
  register_absvector_symbol_object();
  register_set_absvector_element_symbol_object();
  register_get_absvector_element_symbol_object();
  register_is_absvector_symbol_object();
  register_write_byte_symbol_object();
  register_read_byte_symbol_object();
  register_open_symbol_object();
  register_close_symbol_object();
  register_get_time_symbol_object();
  register_add_symbol_object();
  register_subtract_symbol_object();
  register_multiply_symbol_object();
  register_divide_symbol_object();
  register_is_greater_symbol_object();
  register_is_less_symbol_object();
  register_is_greater_or_equal_symbol_object();
  register_is_less_or_equal_symbol_object();
  register_is_number_symbol_object();
}

static inline void register_in_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("in");
  in_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, in_symbol_object);
}

static inline void register_out_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("out");
  out_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, get_out_symbol_object());
}

static inline void register_stream_symbol_objects (void)
{
  register_in_symbol_object();
  register_out_symbol_object();
}

static inline void register_unix_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("unix");
  unix_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, unix_symbol_object);
}

static inline void register_run_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("run");
  run_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, run_symbol_object);
}

static inline void register_system_symbol_objects (void)
{
  register_unix_symbol_object();
  register_run_symbol_object();
}

static inline void register_exit_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("exit");
  exit_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, exit_symbol_object);
}

static inline void register_slash_dot_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("/.");
  slash_dot_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, slash_dot_symbol_object);
}

static inline void register_shen_ebr_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("shen.ebr");
  shen_ebr_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, shen_ebr_symbol_object);
}

static inline void register_hash_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("hash");
  hash_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, hash_symbol_object);
}

static inline void register_is_symbol_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("symbol?");
  is_symbol_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, is_symbol_symbol_object);
}

static inline void register_is_boolean_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("boolean?");
  is_boolean_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, is_boolean_symbol_object);
}

static inline void register_is_integer_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("integer?");
  is_integer_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, is_integer_symbol_object);
}

static inline void register_is_variable_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("variable?");
  is_variable_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, is_variable_symbol_object);
}

static inline void register_not_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("not");
  not_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, not_symbol_object);
}

static inline void register_value_slash_or_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("value/or");
  value_slash_or_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, value_slash_or_symbol_object);
}

static inline void register_get_absvector_element_slash_or_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("<-address/or");
  get_absvector_element_slash_or_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, get_absvector_element_slash_or_symbol_object);
}

static inline void register_map_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("map");
  map_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, map_symbol_object);
}

static inline void register_reverse_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("reverse");
  reverse_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, reverse_symbol_object);
}

static inline void register_append_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("append");
  append_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, append_symbol_object);
}

static inline void register_is_element_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("element?");
  is_element_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, is_element_symbol_object);
}

static inline void register_assoc_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("assoc");
  assoc_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, assoc_symbol_object);
}

static inline void register_occurrences_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("occurrences");
  occurrences_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, occurrences_symbol_object);
}

static inline void register_nth_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("nth");
  nth_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, nth_symbol_object);
}

static inline void register_limit_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("limit");
  limit_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, limit_symbol_object);
}

static inline void register_dict_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("dict");
  dict_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, dict_symbol_object);
}

static inline void register_is_dict_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("dict?");
  is_dict_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, is_dict_symbol_object);
}

static inline void register_dict_count_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("dict-count");
  dict_count_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, dict_count_symbol_object);
}

static inline void register_get_dict_value_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("<-dict");
  get_dict_value_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, get_dict_value_symbol_object);
}

static inline void register_get_dict_value_slash_or_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("<-dict/or");
  get_dict_value_slash_or_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, get_dict_value_slash_or_symbol_object);
}

static inline void register_set_dict_value_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("dict->");
  set_dict_value_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, set_dict_value_symbol_object);
}

static inline void register_dict_rm_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("dict-rm");
  dict_rm_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, dict_rm_symbol_object);
}

static inline void register_dict_keys_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("dict-keys");
  dict_keys_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, dict_keys_symbol_object);
}

static inline void register_dict_values_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("dict-values");
  dict_values_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, dict_values_symbol_object);
}

static inline void register_dict_fold_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("dict-fold");
  dict_fold_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, dict_fold_symbol_object);
}

static inline void register_length_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("length");
  length_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, length_symbol_object);
}

static inline void register_shen_fail_exclamation_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("shen.fail!");
  shen_fail_exclamation_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, shen_fail_exclamation_symbol_object);
}

static inline void register_shen_hdtl_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("shen.hdtl");
  shen_hdtl_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, shen_hdtl_symbol_object);
}

static inline void register_shen_is_numbyte_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("shen.numbyte?");
  shen_is_numbyte_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, shen_is_numbyte_symbol_object);
}

static inline void register_shen_byte_to_digit_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("shen.byte->digit");
  shen_byte_to_digit_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, shen_byte_to_digit_symbol_object);
}

static inline void register_read_file_as_charlist_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("read-file-as-charlist");
  read_file_as_charlist_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, read_file_as_charlist_symbol_object);
}

static inline void register_shen_pvar_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("shen.pvar");
  shen_pvar_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, shen_pvar_symbol_object);
}

static inline void register_shen_is_pvar_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("shen.pvar?");
  shen_is_pvar_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, shen_is_pvar_symbol_object);
}

static inline void register_shen_earmuff_prologvectors_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("shen.*prologvectors*");
  shen_earmuff_prologvectors_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, shen_earmuff_prologvectors_symbol_object);
}

static inline void register_shen_earmuff_varcounter_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("shen.*varcounter*");
  shen_earmuff_varcounter_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, shen_earmuff_varcounter_symbol_object);
}

static inline void register_shen_valvector_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("shen.valvector");
  shen_valvector_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, shen_valvector_symbol_object);
}

static inline void register_shen_dash_null_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("shen.-null-");
  shen_dash_null_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, shen_dash_null_symbol_object);
}

static inline void register_shen_lazyderef_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("shen.lazyderef");
  shen_lazyderef_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, shen_lazyderef_symbol_object);
}

static inline void register_shen_deref_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("shen.deref");
  shen_deref_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, shen_deref_symbol_object);
}

static inline void register_shen_is_occurs_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("shen.occurs?");
  shen_is_occurs_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, shen_is_occurs_symbol_object);
}

static inline void register_shen_bindv_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("shen.bindv");
  shen_bindv_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, shen_bindv_symbol_object);
}

static inline void register_shen_unbindv_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("shen.unbindv");
  shen_unbindv_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, shen_unbindv_symbol_object);
}

static inline void register_bind_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("bind");
  bind_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, bind_symbol_object);
}

static inline void register_shen_lzy_equal_exclamation_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("shen.lzy=!");
  shen_lzy_equal_exclamation_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, shen_lzy_equal_exclamation_symbol_object);
}

static inline void register_shen_mk_pvar_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("shen.mk-pvar");
  shen_mk_pvar_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, shen_mk_pvar_symbol_object);
}

static inline void register_shen_copy_vector_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("shen.copy-vector");
  shen_copy_vector_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, shen_copy_vector_symbol_object);
}

static inline void register_shen_resize_vector_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("shen.resize-vector");
  shen_resize_vector_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, shen_resize_vector_symbol_object);
}

static inline void register_shen_resizeprocessvector_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("shen.resizeprocessvector");
  shen_resizeprocessvector_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, shen_resizeprocessvector_symbol_object);
}

static inline void register_shen_newpv_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("shen.newpv");
  shen_newpv_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, shen_newpv_symbol_object);
}

static inline void register_shen_list_to_str_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("shen.list->str");
  shen_list_to_str_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, shen_list_to_str_symbol_object);
}

static inline void register_shen_str_to_str_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("shen.str->str");
  shen_str_to_str_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, shen_str_to_str_symbol_object);
}

static inline void register_shen_vector_to_str_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("shen.vector->str");
  shen_vector_to_str_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, shen_vector_to_str_symbol_object);
}

static inline void register_shen_atom_to_str_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("shen.atom->str");
  shen_atom_to_str_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, shen_atom_to_str_symbol_object);
}

static inline void register_shen_arg_to_str_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("shen.arg->str");
  shen_arg_to_str_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, shen_arg_to_str_symbol_object);
}

static inline void register_shen_compose_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("shen.compose");
  shen_compose_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, shen_compose_symbol_object);
}

static inline void register_overwrite_symbol_objects (void)
{
  register_exit_symbol_object();
  register_slash_dot_symbol_object();
  register_shen_ebr_symbol_object();
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
  register_append_symbol_object();
  register_is_element_symbol_object();
  register_assoc_symbol_object();
  register_occurrences_symbol_object();
  register_nth_symbol_object();
  register_limit_symbol_object();
  register_dict_symbol_object();
  register_is_dict_symbol_object();
  register_dict_count_symbol_object();
  register_get_dict_value_symbol_object();
  register_get_dict_value_slash_or_symbol_object();
  register_set_dict_value_symbol_object();
  register_dict_rm_symbol_object();
  register_dict_keys_symbol_object();
  register_dict_values_symbol_object();
  register_dict_fold_symbol_object();
  register_length_symbol_object();
  register_shen_fail_exclamation_symbol_object();
  register_shen_hdtl_symbol_object();
  register_shen_is_numbyte_symbol_object();
  register_read_file_as_charlist_symbol_object();
  register_shen_byte_to_digit_symbol_object();
  register_shen_pvar_symbol_object();
  register_shen_is_pvar_symbol_object();
  register_shen_earmuff_prologvectors_symbol_object();
  register_shen_earmuff_varcounter_symbol_object();
  register_shen_valvector_symbol_object();
  register_shen_dash_null_symbol_object();
  register_shen_lazyderef_symbol_object();
  register_shen_deref_symbol_object();
  register_shen_is_occurs_symbol_object();
  register_shen_bindv_symbol_object();
  register_shen_unbindv_symbol_object();
  register_bind_symbol_object();
  register_shen_lzy_equal_exclamation_symbol_object();
  register_shen_mk_pvar_symbol_object();
  register_shen_copy_vector_symbol_object();
  register_shen_resize_vector_symbol_object();
  register_shen_resizeprocessvector_symbol_object();
  register_shen_newpv_symbol_object();
  register_shen_list_to_str_symbol_object();
  register_shen_str_to_str_symbol_object();
  register_shen_vector_to_str_symbol_object();
  register_shen_atom_to_str_symbol_object();
  register_shen_arg_to_str_symbol_object();
  register_shen_compose_symbol_object();
}

static inline void register_c_loop_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("c.loop");
  c_loop_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, c_loop_symbol_object);
}

static inline void register_c_recur_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("c.recur");
  c_recur_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, c_recur_symbol_object);
}

static inline void register_c_quote_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("c.quote");
  c_quote_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, c_quote_symbol_object);
}

static inline void register_c_mcons_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("c.mcons");
  c_mcons_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, c_mcons_symbol_object);
}

static inline void register_c_ocons_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("c.ocons");
  c_ocons_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, c_ocons_symbol_object);
}

static inline void register_c_nth_hd_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("c.nth-hd");
  c_nth_hd_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, c_nth_hd_symbol_object);
}

static inline void register_c_nth_tl_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("c.nth-tl");
  c_nth_tl_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, c_nth_tl_symbol_object);
}

static inline void register_c_flush_symbol_object (void)
{
  KLObject* string_object = create_kl_string_with_intern("c.flush");
  c_flush_symbol_object = create_kl_symbol(string_object);
  extend_symbol_table(string_object, c_flush_symbol_object);
}

static inline void register_extension_symbol_objects (void)
{
  register_c_loop_symbol_object();
  register_c_recur_symbol_object();
  register_c_quote_symbol_object();
  register_c_mcons_symbol_object();
  register_c_ocons_symbol_object();
  register_c_nth_hd_symbol_object();
  register_c_nth_tl_symbol_object();
  register_c_flush_symbol_object();
}

void register_symbol_objects (void)
{
  register_primitive_symbol_objects();
  register_stream_symbol_objects();
  register_system_symbol_objects();
  register_overwrite_symbol_objects();
  register_extension_symbol_objects();
}
