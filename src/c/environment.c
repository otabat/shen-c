#include "environment.h"

static Environment* global_function_environment = NULL;
static Environment* global_variable_environment = NULL;

khash_t(SymbolTable)* get_environment_symbol_table (Environment* environment)
{
  return environment->symbol_table;
}

void set_environment_symbol_table (Environment* environment,
                                   khash_t(SymbolTable)* symbol_table)
{
  environment->symbol_table = symbol_table;
}

Environment* get_parent_environment (Environment* environment)
{
  return environment->parent;
}

void set_parent_environment (Environment* environment,
                             Environment* parent_environment)
{
  environment->parent = parent_environment;
}

Environment* create_environment (void)
{
  Environment* environment = malloc(sizeof(Environment));

  set_environment_symbol_table(environment, kh_init(SymbolTable));
  set_parent_environment(environment, NULL);

  return environment;
}

void initialize_global_function_environment (void)
{
  global_function_environment = create_environment();
}

Environment* get_global_function_environment (void)
{
  return global_function_environment;
}

void initialize_global_variable_environment (void)
{
  global_variable_environment = create_environment();
}

Environment* get_global_variable_environment (void)
{
  return global_variable_environment;
}

KLObject* lookup_environment (KLObject* symbol_object, Environment* environment,
                              Environment** matched_environment_ref)
{ 
  khash_t(SymbolTable)* symbol_table = get_environment_symbol_table(environment);
  char* symbol = get_symbol(symbol_object);
  khiter_t hash_iterator = kh_get(SymbolTable, symbol_table, symbol);
  bool is_key_not_found = hash_iterator == kh_end(symbol_table);

  if (is_key_not_found || kh_exist(symbol_table, hash_iterator) == 0) {
    Environment* parent_environment = get_parent_environment(environment);

    if (is_null(parent_environment)) {
      *matched_environment_ref = NULL;

      return NULL;
    }

    return lookup_environment(symbol_object, parent_environment,
                              matched_environment_ref);
  }

  *matched_environment_ref = environment;

  return kh_value(symbol_table, hash_iterator);
}

void extend_environment (KLObject* symbol_object, KLObject* object,
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
