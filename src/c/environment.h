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

inline khash_t(SymbolTable)* get_environment_symbol_table
(Environment* environment)
{
  return environment->symbol_table;
}

inline void set_environment_symbol_table (Environment* environment,
                                          khash_t(SymbolTable)* symbol_table)
{
  environment->symbol_table = symbol_table;
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

  set_environment_symbol_table(environment, kh_init(SymbolTable));
  set_parent_environment(environment, NULL);

  return environment;
}

inline void initialize_global_function_environment (void)
{
  global_function_environment = create_environment();
}

inline void initialize_global_variable_environment (void)
{
  global_variable_environment = create_environment();
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
  khash_t(SymbolTable)* symbol_table = get_environment_symbol_table(environment);
  char* symbol = get_symbol(symbol_object);
  int put_result;
  khiter_t hash_iterator = kh_put(SymbolTable, symbol_table, symbol, &put_result);

  if (put_result == -1)
    throw_kl_exception("Failed to extend environment");

  kh_value(symbol_table, hash_iterator) = object;
}

#endif
