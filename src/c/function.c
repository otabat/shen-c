#include "function.h"

extern size_t get_primitive_function_parameter_size
(PrimitiveFunction* primitive_function);
extern void set_primitive_function_parameter_size
(PrimitiveFunction* primitive_function, size_t parameter_size);
extern NativeFunction* get_primitive_function_native_function
(PrimitiveFunction* primitive_function);
extern void set_primitive_function_native_function
(PrimitiveFunction* primitive_function, NativeFunction* native_function);
extern PrimitiveFunction* create_primitive_function (void);

extern Vector* get_user_function_parameters (UserFunction* user_function);
extern void set_user_function_parameters (UserFunction* user_function,
                                          Vector* parameters);
extern KLObject* get_user_function_body (UserFunction* user_function);
extern void set_user_function_body (UserFunction* user_function,
                                    KLObject* body_object);
extern UserFunction* create_user_function (void);

extern KLObject* get_closure_parameter (Closure* closure);
extern void set_closure_parameter (Closure* closure, KLObject* parameter);
extern KLObject* get_closure_body (Closure* closure);
extern void set_closure_body (Closure* closure, KLObject* body_object);
extern Environment* get_closure_parent_function_environment (Closure* closure);
extern void set_closure_parent_function_environment
(Closure* closure, Environment* parent_function_environment);
extern Environment* get_closure_parent_variable_environment (Closure* closure);
extern void set_closure_parent_variable_environment
(Closure* closure, Environment* parent_variable_environment);
extern Closure* create_closure (void);

extern KLFunctionType get_function_function_type (Function* function);
extern void set_function_function_type (Function* function,
                                        KLFunctionType function_type);
extern PrimitiveFunction* get_function_primitive_function (Function* function);
extern void set_function_primitive_function
(Function* function, PrimitiveFunction* primitive_function);

extern UserFunction* get_function_user_function (Function* function);
extern void set_function_user_function (Function* function,
                                        UserFunction* user_function);
extern Closure* get_function_closure (Function* function);
extern void set_function_closure (Function* function, Closure* closure);
extern bool is_primitive_function (Function* function);
extern bool is_user_function (Function* function);
extern bool is_closure (Function* function);
extern Function* create_function (KLFunctionType function_type);

extern Function* get_function (KLObject* function_object);
extern void set_function (KLObject* function_object, Function* function);
extern bool is_kl_function (KLObject* object);
extern bool is_primitive_kl_function (KLObject* object);
extern bool is_user_kl_function (KLObject* object);
extern bool is_closure_kl_function (KLObject* object);
extern KLFunctionType get_kl_function_type (KLObject* function_object);
extern void set_kl_function_type (KLObject* function_object,
                                  KLFunctionType function_type);

extern KLObject* create_primitive_kl_function (size_t parameter_size,
                                               NativeFunction* native_function);
extern PrimitiveFunction* get_kl_function_primitive_function
(KLObject* function_object);
extern void set_kl_function_primitive_function
(KLObject* function_object, PrimitiveFunction* primitive_function);

extern KLObject* create_user_kl_function (void);
extern UserFunction* get_kl_function_user_function (KLObject* function_object);
extern void set_kl_function_user_function (KLObject* function_object,
                                           UserFunction* user_function);

extern KLObject* create_closure_kl_function (void);
extern Closure* get_kl_function_closure (KLObject* function_object);
extern void set_kl_function_closure (KLObject* function_object, Closure* closure);

extern void check_function_argument_size (size_t argument_size,
                                          size_t parameter_size);
extern bool is_kl_function_equal (KLObject* left_object, KLObject* right_object);
extern void check_function_user_parameters (Vector* parameters);
