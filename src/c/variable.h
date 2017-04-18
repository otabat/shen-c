#ifndef SHEN_C_VARIABLE_H
#define SHEN_C_VARIABLE_H

#include <stdio.h>

#include "environment.h"
#include "exception.h"
#include "kl.h"
#include "object.h"
#include "symbol.h"

KLObject* get_variable_value (KLObject* symbol_object,
                              Environment* variable_environment);
KLObject* set_variable_value (KLObject* symbol_object, KLObject* object,
                              Environment* variable_environment);

#endif
