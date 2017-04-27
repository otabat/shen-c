#ifndef SHEN_C_DEVELOPMENT_H
#define SHEN_C_DEVELOPMENT_H

#include <stdio.h>

#include "exception.h"
#include "kl.h"
#include "list.h"
#include "number.h"
#include "object.h"
#include "primitive.h"
#include "symbol.h"

extern KLObject* eval_kl_object (KLObject* object,
                                 Environment* function_environment,
                                 Environment* variable_environment);

KLObject* inject_symbol_counter (KLObject* function_symbol_object,
                                 KLObject* body_object);
void initialize_symbol_counter (void);

#endif
