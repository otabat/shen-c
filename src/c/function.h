#ifndef SHEN_C_FUNCTION_H
#define SHEN_C_FUNCTION_H

#include <stdint.h>
#include <stdbool.h>

#include "environment.h"
#include "exception.h"
#include "kl.h"
#include "symbol.h"
#include "vector.h"

size_t get_primitive_function_parameter_size
(PrimitiveFunction* primitive_function);
void set_primitive_function_parameter_size
(PrimitiveFunction* primitive_function, size_t parameter_size);
NativeFunction* get_primitive_function_native_function
(PrimitiveFunction* primitive_function);
void set_primitive_function_native_function
(PrimitiveFunction* primitive_function, NativeFunction* native_function);
PrimitiveFunction* create_primitive_function (void);

Vector* get_user_function_parameters (UserFunction* user_function);
void set_user_function_parameters (UserFunction* user_function,
                                   Vector* parameters);
KLObject* get_user_function_body (UserFunction* user_function);
void set_user_function_body (UserFunction* user_function, KLObject* body_object);
UserFunction* create_user_function (void);

KLObject* get_closure_parameter (Closure* closure);
void set_closure_parameter (Closure* closure, KLObject* parameter);
KLObject* get_closure_body (Closure* closure);
void set_closure_body (Closure* closure, KLObject* body_object);
Environment* get_closure_parent_function_environment (Closure* closure);
void set_closure_parent_function_environment
(Closure* closure, Environment* parent_function_environment);
Environment* get_closure_parent_variable_environment (Closure* closure);
void set_closure_parent_variable_environment
(Closure* closure, Environment* parent_variable_environment);
Closure* create_closure (void);

bool is_primitive_function (Function* function);
bool is_user_function (Function* function);
bool is_closure (Function* function);
KLFunctionType get_function_function_type (Function* function);
void set_function_function_type (Function* function, KLFunctionType function_type);
PrimitiveFunction* get_function_primitive_function (Function* function);
void set_function_primitive_function (Function* function,
                                      PrimitiveFunction* primitive_function);

UserFunction* get_function_user_function (Function* function);
void set_function_user_function (Function* function, UserFunction* user_function);
Closure* get_function_closure (Function* function);
void set_function_closure (Function* function, Closure* closure);
Function* create_function (KLFunctionType function_type);

bool is_kl_function (KLObject* object);
bool is_primitive_kl_function (KLObject* object);
bool is_user_kl_function (KLObject* object);
bool is_closure_kl_function (KLObject* object);
KLFunctionType get_kl_function_type (KLObject* function_object);
void set_kl_function_type (KLObject* function_object,
                           KLFunctionType function_type);
Function* get_function (KLObject* function_object);
void set_function (KLObject* function_object, Function* function);

KLObject* create_primitive_kl_function (size_t parameter_size,
                                        NativeFunction* native_function);
PrimitiveFunction* get_kl_function_primitive_function (KLObject* function_object);
void set_kl_function_primitive_function (KLObject* function_object,
                                         PrimitiveFunction* primitive_function);

KLObject* create_user_kl_function (void);
UserFunction* get_kl_function_user_function (KLObject* function_object);
void set_kl_function_user_function (KLObject* function_object,
                                    UserFunction* user_function);

KLObject* create_closure_kl_function (void);
Closure* get_kl_function_closure (KLObject* function_object);
void set_kl_function_closure (KLObject* function_object, Closure* closure);

void check_function_argument_size (size_t argument_size, size_t parameter_size);
bool is_kl_function_equal (KLObject* left_object, KLObject* right_object);
void check_function_user_parameters (Vector* parameters);

#endif
