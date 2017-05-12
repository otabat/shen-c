#ifndef SHEN_C_OVERWRITE_H
#define SHEN_C_OVERWRITE_H

#include <stdbool.h>
#include <stdlib.h>

#include "khash.h"

#include "boolean.h"
#include "dictionary.h"
#include "exception.h"
#include "extension.h"
#include "hash.h"
#include "kl.h"
#include "list.h"
#include "number.h"
#include "object.h"
#include "primitive.h"
#include "reader.h"
#include "string.h"
#include "symbol.h"
#include "symbol_pool.h"
#include "vector.h"
#include "variable.h"

void register_overwrite_toplevel_primitive_kl_functions (void);
void register_overwrite_core_primitive_kl_functions (void);
void register_overwrite_sys_primitive_kl_functions (void);
void register_overwrite_yacc_primitive_kl_functions (void);
void register_overwrite_reader_primitive_kl_functions (void);
void register_overwrite_prolog_primitive_kl_functions (void);
void register_overwrite_writer_primitive_kl_functions (void);
void register_overwrite_macros_primitive_kl_functions (void);

extern KLObject* eval_freeze_expression (KLObject* body_object,
                                         Environment* function_environment,
                                         Environment* variable_environment);
extern KLObject* eval_simple_closure_function_application
(KLObject* function_object);
extern KLObject* eval_kl_object (KLObject* object,
                                 Environment* function_environment,
                                 Environment* variable_environment);

#endif
