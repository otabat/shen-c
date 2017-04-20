#ifndef SHEN_C_PRIMITIVE_H
#define SHEN_C_PRIMITIVE_H

#include "boolean.h"
#include "exception.h"
#include "function.h"
#include "kl.h"
#include "list.h"
#include "object.h"
#include "stream.h"
#include "string.h"
#include "symbol.h"
#include "system.h"
#include "variable.h"
#include "vector.h"

void register_primitive_kl_functions (void);

inline KLObject** get_kl_function_arguments_with_count_check
(KLObject* function_object, Vector* arguments)
{
  PrimitiveFunction* primitive_function =
    get_kl_function_primitive_function(function_object);
  size_t argument_size = (is_null(arguments)) ? 0 : get_vector_size(arguments);
  size_t parameter_size =
    get_primitive_function_parameter_size(primitive_function);

  check_function_argument_size(argument_size, parameter_size);

  return (is_null(arguments))? NULL : get_vector_objects(arguments);
}

inline void register_primitive_kl_function
(char* symbol, KLObject* (*create_primitive_kl_function) (void))
{
  KLObject* symbol_object = create_kl_symbol(symbol);
  KLObject* function_object = create_primitive_kl_function();

  extend_environment(symbol_object, function_object,
                     get_global_function_environment());
}

#endif
