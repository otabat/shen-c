#include "environment.h"

Environment* global_function_environment = NULL;
Environment* global_variable_environment = NULL;

extern khash_t(SymbolTable)* get_environment_symbol_table (Environment* environment);
extern void set_environment_symbol_table (Environment* environment,
                                          khash_t(SymbolTable)* symbol_table);
extern Environment* get_parent_environment (Environment* environment);
extern void set_parent_environment (Environment* environment,
                                    Environment* parent_environment);
extern Environment* create_environment (void);
extern void initialize_global_function_environment (void);
extern void initialize_global_variable_environment (void);
extern Environment* get_global_function_environment (void);
extern Environment* get_global_variable_environment (void);
extern KLObject* lookup_environment (KLObject* symbol_object,
                                     Environment* environment,
                                     Environment** matched_environment_ref);
extern void extend_environment (KLObject* symbol_object, KLObject* object,
                                Environment* environment);

inline KLObject* lookup_environment (KLObject* symbol_object,
                                     Environment* environment,
                                     Environment** matched_environment_ref)
{ 
  khash_t(SymbolTable)* symbol_table;
  char* symbol;
  khiter_t hash_iterator;
  bool is_key_not_found;
  Environment* new_environment = environment;
  Environment* parent_environment;

  while (true) {
    symbol_table = get_environment_symbol_table(new_environment);
    symbol = get_symbol(symbol_object);
    hash_iterator = kh_get(SymbolTable, symbol_table, symbol);
    is_key_not_found = hash_iterator == kh_end(symbol_table);

    if (is_key_not_found || kh_exist(symbol_table, hash_iterator) == 0) {
      parent_environment = get_parent_environment(new_environment);

      if (is_null(parent_environment)) {
        *matched_environment_ref = NULL;

        return NULL;
      }

      new_environment = parent_environment;

      continue;
    }

    *matched_environment_ref = new_environment;

    return kh_value(symbol_table, hash_iterator);
  }
}
