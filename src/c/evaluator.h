#ifndef SHEN_C_EVALUATOR_H
#define SHEN_C_EVALUATOR_H

#include <stdio.h>
#include <stdbool.h>
#include <setjmp.h>

#include "boolean.h"
#include "character.h"
#include "environment.h"
#include "exception.h"
#include "function.h"
#include "kl.h"
#include "list.h"
#include "loop.h"
#include "object.h"
#include "number.h"
#include "primitive.h"
#include "reader.h"
#include "string.h"
#include "symbol.h"
#include "symbol_pool.h"

KLObject* eval_freeze_expression (KLObject* body_object,
                                  Environment* function_environment,
                                  Environment* variable_environment);
KLObject* eval_simple_closure_function_application
(KLObject* function_object);
KLObject* eval_kl_object (KLObject* object, Environment* function_environment,
                          Environment* variable_environment);

#endif
