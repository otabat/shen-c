#include "extension.h"

static inline KLObject* primitive_function_println
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  println_kl_object(objects[0]);

  return objects[0];
}

static inline void register_primitive_kl_function_println (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_println);

  set_kl_symbol_function(get_println_symbol_object(), function_object);
}

static inline KLObject* primitive_function_quit (KLObject* function_object,
                                                 Vector* arguments,
                                                 Environment* function_environment,
                                                 Environment* variable_environment)
{
  get_kl_function_arguments_with_count_check(function_object, arguments);
  exit(EXIT_SUCCESS);

  return NULL;
}

static inline void register_primitive_kl_function_quit (void)
{
  KLObject* function_object =
    create_primitive_kl_function(0, &primitive_function_quit);

  set_kl_symbol_function(get_quit_symbol_object(), function_object);
}

void register_extension_primitive_kl_functions (void)
{
  register_primitive_kl_function_println();
  register_primitive_kl_function_quit();
}
