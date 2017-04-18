#ifndef SHEN_C_SYMBOL_H
#define SHEN_C_SYMBOL_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "boolean.h"
#include "exception.h"
#include "kl.h"
#include "string.h"

KLObject* create_kl_symbol (char* symbol);
char* get_symbol (KLObject* symbol_object);
void set_symbol (KLObject* symbol_object, char* symbol);
KLObject* create_auto_increment_kl_symbol (void);
bool is_kl_symbol (KLObject* object);
KLObject* kl_string_to_kl_symbol (KLObject* string_object);
KLObject* kl_string_to_kl_symbol_or_kl_boolean (KLObject* string_object);
bool is_symbol_equal (char* left_symbol, char* right_symbol);
bool is_kl_symbol_equal (KLObject* left_object, KLObject* right_object);

#endif
