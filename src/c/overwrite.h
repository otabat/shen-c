#ifndef SHEN_C_OVERWRITE_H
#define SHEN_C_OVERWRITE_H

#include <stdbool.h>

#include "boolean.h"
#include "exception.h"
#include "hash.h"
#include "kl.h"
#include "number.h"
#include "primitive.h"
#include "vector.h"

extern KLObject* hash_symbol_object;
extern KLObject* is_symbol_symbol_object;
extern KLObject* is_integer_symbol_object;
extern KLObject* is_boolean_symbol_object;
extern KLObject* is_variable_symbol_object;
extern KLObject* not_symbol_object;
extern KLObject* shen_is_numbyte_symbol_object;
extern KLObject* shen_byte_to_digit_symbol_object;
extern KLObject* shen_pvar_symbol_object;
extern KLObject* shen_is_pvar_symbol_object;

void register_overwrite_symbol_objects (void);
void register_overwrite_sys_primitive_kl_functions (void);
void register_overwrite_reader_primitive_kl_functions (void);
void register_overwrite_prolog_primitive_kl_functions (void);

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

inline KLObject* get_shen_is_numbyte_symbol_object (void)
{
  return shen_is_numbyte_symbol_object;
}

inline KLObject* get_shen_byte_to_digit_symbol_object (void)
{
  return shen_byte_to_digit_symbol_object;
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
