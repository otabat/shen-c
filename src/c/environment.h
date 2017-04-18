#ifndef SHEN_C_ENVIRONMENT_H
#define SHEN_C_ENVIRONMENT_H

#include "khash.h"

#include "kl.h"
#include "object.h"
#include "symbol.h"

khash_t(SymbolTable)* get_environment_symbol_table (Environment* environment);
void set_environment_symbol_table (Environment* environment,
                                   khash_t(SymbolTable)* symbol_table);
Environment* get_parent_environment (Environment* environment);
void set_parent_environment (Environment* environment,
                             Environment* parent_environment);
Environment* create_environment (void);
void initialize_global_function_environment (void);
Environment* get_global_function_environment (void);
void initialize_global_variable_environment (void);
Environment* get_global_variable_environment (void);
KLObject* lookup_environment (KLObject* symbol_object, Environment* environment,
                              Environment** matched_environment);
void extend_environment (KLObject* symbol_object, KLObject* object,
                         Environment* environment);

#endif
