#include "extension.h"

static inline KLObject* primitive_function_println (KLObject* function_object,
                                                    Vector* arguments)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  println_kl_object(objects[0]);

  return objects[0];
}

static inline KLObject* create_primitive_kl_function_println (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_println);

  return function_object;
}

static inline KLObject* primitive_function_quit (KLObject* function_object,
                                                 Vector* arguments)
{
  get_kl_function_arguments_with_count_check(function_object, arguments);
  exit(EXIT_SUCCESS);

  return NULL;
}

static inline KLObject* create_primitive_kl_function_quit (void)
{
  KLObject* function_object =
    create_primitive_kl_function(0, &primitive_function_quit);

  return function_object;
}

static inline KLObject* primitive_function_exit (KLObject* function_object,
                                                 Vector* arguments)
{
  get_kl_function_arguments_with_count_check(function_object, arguments);
  exit(EXIT_SUCCESS);

  return NULL;
}

static inline KLObject* create_primitive_kl_function_exit (void)
{
  KLObject* function_object =
    create_primitive_kl_function(0, &primitive_function_exit);

  return function_object;
}

void register_extension_primitive_kl_functions (void)
{
  register_primitive_kl_function("println",
                                 &create_primitive_kl_function_println);
  register_primitive_kl_function("quit", &create_primitive_kl_function_quit);
  register_primitive_kl_function("exit", &create_primitive_kl_function_exit);
}
