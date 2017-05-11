#ifndef SHEN_C_FUNCTION_H
#define SHEN_C_FUNCTION_H

#include <stdint.h>
#include <stdbool.h>

#include "environment.h"
#include "exception.h"
#include "kl.h"
#include "symbol.h"
#include "vector.h"

inline long get_primitive_function_parameter_size
(PrimitiveFunction* primitive_function)
{
  return primitive_function->parameter_size;
}

inline void set_primitive_function_parameter_size
(PrimitiveFunction* primitive_function, long parameter_size)
{
  primitive_function->parameter_size = parameter_size;
}

inline NativeFunction* get_primitive_function_native_function
(PrimitiveFunction* primitive_function)
{
  return primitive_function->native_function;
}

inline void set_primitive_function_native_function
(PrimitiveFunction* primitive_function, NativeFunction* native_function)
{
  primitive_function->native_function = native_function;
}

inline PrimitiveFunction* create_primitive_function (void)
{
  PrimitiveFunction* primitive_function = malloc(sizeof(PrimitiveFunction));

  set_primitive_function_parameter_size(primitive_function, 0);
  set_primitive_function_native_function(primitive_function, NULL);

  return primitive_function;
}

inline Vector* get_user_function_parameters (UserFunction* user_function)
{
  return user_function->parameters;
}

inline void set_user_function_parameters (UserFunction* user_function,
                                          Vector* parameters)
{
  user_function->parameters = parameters;
}

inline KLObject* get_user_function_body (UserFunction* user_function)
{
  return user_function->body;
}

inline void set_user_function_body (UserFunction* user_function,
                                    KLObject* body_object)
{
  user_function->body = body_object;
}

inline UserFunction* create_user_function (void)
{
  UserFunction* user_function = malloc(sizeof(UserFunction));

  set_user_function_parameters(user_function, NULL);
  set_user_function_body(user_function, NULL);

  return user_function;
}

inline KLObject* get_closure_parameter (Closure* closure)
{
  return closure->parameter;
}

inline void set_closure_parameter (Closure* closure, KLObject* parameter)
{
  closure->parameter = parameter;
}

inline KLObject* get_closure_body (Closure* closure)
{
  return closure->body;
}

inline void set_closure_body (Closure* closure, KLObject* body_object)
{
  closure->body = body_object;
}

inline Environment* get_closure_parent_function_environment (Closure* closure)
{
  return closure->parent_function_environment;
}

inline void set_closure_parent_function_environment
(Closure* closure, Environment* parent_function_environment)
{
  closure->parent_function_environment = parent_function_environment;
}

inline Environment* get_closure_parent_variable_environment (Closure* closure)
{
  return closure->parent_variable_environment;
}

inline void set_closure_parent_variable_environment
(Closure* closure, Environment* parent_variable_environment)
{
  closure->parent_variable_environment = parent_variable_environment;
}

inline Closure* create_closure (void)
{
  Closure* closure = malloc(sizeof(Closure));

  set_closure_parameter(closure, NULL);
  set_closure_body(closure, NULL);
  set_closure_parent_function_environment(closure, NULL);
  set_closure_parent_variable_environment(closure, NULL);

  return closure;
}

inline KLFunctionType get_function_function_type (Function* function)
{
  return function->function_type;
}

inline void set_function_function_type (Function* function,
                                        KLFunctionType function_type)
{
  function->function_type = function_type;
}

inline PrimitiveFunction* get_function_primitive_function (Function* function)
{
  return function->value.primitive_function;
}

inline void set_function_primitive_function (Function* function,
                                             PrimitiveFunction* primitive_function)
{
  function->value.primitive_function = primitive_function;
}

inline UserFunction* get_function_user_function (Function* function)
{
  return function->value.user_function;
}

inline void set_function_user_function (Function* function,
                                        UserFunction* user_function)
{
  function->value.user_function = user_function;
}

inline Closure* get_function_closure (Function* function)
{
  return function->value.closure;
}

inline void set_function_closure (Function* function, Closure* closure)
{
  function->value.closure = closure;
}

inline bool is_primitive_function (Function* function)
{
  return (get_function_function_type(function) ==
          KL_FUNCTION_TYPE_PRIMITIVE_FUNCTION);
}

inline bool is_user_function (Function* function)
{
  return get_function_function_type(function) == KL_FUNCTION_TYPE_USER_FUNCTION;
}

inline bool is_closure (Function* function)
{
  return get_function_function_type(function) == KL_FUNCTION_TYPE_CLOSURE;
}

inline Function* create_function (KLFunctionType function_type)
{
  Function* function = malloc(sizeof(Function));

  set_function_function_type(function, function_type);

  if (is_primitive_function(function))
    set_function_primitive_function(function, create_primitive_function());
  else if (is_user_function(function))
    set_function_user_function(function, create_user_function());
  else if (is_closure(function))
    set_function_closure(function, create_closure());
  else
    throw_kl_exception("Unknown type of function");

  return function;
}

inline Function* get_function (KLObject* function_object)
{
  return function_object->value.function;
}

inline void set_function (KLObject* function_object, Function* function)
{
  function_object->value.function = function;
}

inline bool is_kl_function (KLObject* object)
{
  return get_kl_object_type(object) == KL_TYPE_FUNCTION;
}

inline bool is_primitive_kl_function (KLObject* object)
{
  return is_kl_function(object) && is_primitive_function(get_function(object));
}

inline bool is_user_kl_function (KLObject* object)
{
  return is_kl_function(object) && is_user_function(get_function(object));
}

inline bool is_closure_kl_function (KLObject* object)
{
  return is_kl_function(object) && is_closure(get_function(object));
}

inline KLFunctionType get_kl_function_type (KLObject* function_object)
{
  return get_function_function_type(get_function(function_object));
}

inline void set_kl_function_type (KLObject* function_object,
                                  KLFunctionType function_type)
{
  set_function_function_type(get_function(function_object), function_type);
}

inline KLObject* create_primitive_kl_function (long parameter_size,
                                               NativeFunction* native_function)
{
  KLObject* function_object = create_kl_object(KL_TYPE_FUNCTION);
  Function* function = create_function(KL_FUNCTION_TYPE_PRIMITIVE_FUNCTION);
  PrimitiveFunction* primitive_function =
    get_function_primitive_function(function);

  set_primitive_function_parameter_size(primitive_function, parameter_size);
  set_primitive_function_native_function(primitive_function, native_function);
  set_function(function_object, function);

  return function_object;
}

inline PrimitiveFunction* get_kl_function_primitive_function
(KLObject* function_object)
{
  return get_function_primitive_function(get_function(function_object));
}

inline void set_kl_function_primitive_function
(KLObject* function_object, PrimitiveFunction* primitive_function)
{
  set_function_primitive_function(get_function(function_object),
                                  primitive_function);
}

inline KLObject* create_user_kl_function (void)
{
  KLObject* function_object = create_kl_object(KL_TYPE_FUNCTION);
  Function* function = create_function(KL_FUNCTION_TYPE_USER_FUNCTION);

  set_function(function_object, function);

  return function_object;
}

inline UserFunction* get_kl_function_user_function (KLObject* function_object)
{
  return get_function_user_function(get_function(function_object));
}

inline void set_kl_function_user_function (KLObject* function_object,
                                           UserFunction* user_function)
{
  set_function_user_function(get_function(function_object),
                             user_function);
}

inline KLObject* create_closure_kl_function (void)
{
  KLObject* function_object = create_kl_object(KL_TYPE_FUNCTION);
  Function* function = create_function(KL_FUNCTION_TYPE_CLOSURE);

  set_function(function_object, function);

  return function_object;
}

inline Closure* get_kl_function_closure (KLObject* function_object)
{
  return get_function_closure(get_function(function_object));
}

inline void set_kl_function_closure (KLObject* function_object, Closure* closure)
{
  set_function_closure(get_function(function_object), closure);
}

inline void check_function_argument_size (long argument_size, long parameter_size)
{
  if (argument_size != parameter_size)
    throw_kl_exception("Wrong number of arguments passed to function");
}

inline bool is_kl_function_equal (KLObject* left_object, KLObject* right_object)
{
  return left_object == right_object;
}

inline void check_function_user_parameters (Vector* parameters)
{
  if (is_not_null(parameters)) {
    KLObject** objects = get_vector_objects(parameters);
    long parameters_size = get_vector_size(parameters);

    for (long i = 0; i < parameters_size; ++i) {
      if (!is_kl_symbol(objects[i]))
        throw_kl_exception("Function parameters should be symbols");
    }
  }
}

#endif
