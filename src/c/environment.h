#ifndef SHEN_C_ENVIRONMENT_H
#define SHEN_C_ENVIRONMENT_H

#include "khash.h"

#include "kl.h"
#include "object.h"
#include "symbol.h"

extern Environment* global_function_environment;
extern Environment* global_variable_environment;

KLObject* lookup_environment (KLObject* symbol_object,
                              Environment* environment,
                              Environment** matched_environment_ref);

inline khash_t(SymbolObjectTable)* get_environment_symbol_object_table
(Environment* environment)
{
  return environment->symbol_object_table;
}

inline void set_environment_symbol_object_table
(Environment* environment, khash_t(SymbolObjectTable)* symbol_object_table)
{
  environment->symbol_object_table = symbol_object_table;
}

inline Environment* get_parent_environment (Environment* environment)
{
  return environment->parent;
}

inline void set_parent_environment (Environment* environment,
                                    Environment* parent_environment)
{
  environment->parent = parent_environment;
}

inline Environment* create_environment (void)
{
  Environment* environment = malloc(sizeof(Environment));

  set_environment_symbol_object_table(environment, kh_init(SymbolObjectTable));
  set_parent_environment(environment, NULL);

  return environment;
}

inline Environment* get_global_function_environment (void)
{
  return global_function_environment;
}

inline Environment* get_global_variable_environment (void)
{
  return global_variable_environment;
}

inline void extend_environment (KLObject* symbol_object, KLObject* object,
                                Environment* environment)
{
  khash_t(SymbolObjectTable)* symbol_object_table =
    get_environment_symbol_object_table(environment);
  int put_result;
  khiter_t hash_iterator = kh_put(SymbolObjectTable, symbol_object_table,
                                  (khint64_t)symbol_object, &put_result);

  if (put_result == -1)
    throw_kl_exception("Failed to extend environment");

  kh_value(symbol_object_table, hash_iterator) = object;
}

#endif
