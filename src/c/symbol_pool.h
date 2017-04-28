#ifndef SHEN_C_SYMBOL_POOL_H
#define SHEN_C_SYMBOL_POOL_H

#include "kl.h"
#include "symbol.h"

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

void register_overwrite_symbol_objects (void);

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

#endif
