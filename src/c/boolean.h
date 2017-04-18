#ifndef SHEN_C_BOOLEAN_H
#define SHEN_C_BOOLEAN_H

#include <stdbool.h>

#include "kl.h"

KLObject* create_kl_boolean (bool boolean);
bool get_boolean (KLObject* boolean_object);
void set_boolean (KLObject* boolean_object, bool boolean);
bool is_kl_boolean (KLObject* boolean_object);
char* kl_boolean_to_string (KLObject* boolean_object);
bool is_kl_boolean_equal (KLObject* left_object, KLObject* right_object);

#endif
