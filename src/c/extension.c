#include "extension.h"

KLObject* println_symbol_object;
KLObject* quit_symbol_object;
KLObject* loop_symbol_object;
KLObject* recur_symbol_object;

extern KLObject* get_println_symbol_object (void);
extern KLObject* get_quit_symbol_object (void);
extern KLObject* get_loop_symbol_object (void);
extern KLObject* get_recur_symbol_object (void);

static inline KLObject* primitive_function_println (KLObject* function_object,
                                                    Vector* arguments)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  println_kl_object(objects[0]);

  return objects[0];
}

static inline void initialize_println_symbol_object (KLObject* function_object)
{
  println_symbol_object = create_kl_symbol("println");
  set_kl_symbol_function(println_symbol_object, function_object);
}

static inline void register_primitive_kl_function_println (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_println);

  initialize_println_symbol_object(function_object);
  extend_symbol_name_table("println", get_println_symbol_object());
}

static inline KLObject* primitive_function_quit (KLObject* function_object,
                                                 Vector* arguments)
{
  get_kl_function_arguments_with_count_check(function_object, arguments);
  exit(EXIT_SUCCESS);

  return NULL;
}

static inline void initialize_quit_symbol_object (KLObject* function_object)
{
  quit_symbol_object = create_kl_symbol("quit");
  set_kl_symbol_function(quit_symbol_object, function_object);
}

static inline void register_primitive_kl_function_quit (void)
{
  KLObject* function_object =
    create_primitive_kl_function(0, &primitive_function_quit);

  initialize_quit_symbol_object(function_object);
  extend_symbol_name_table("quit", get_quit_symbol_object());
}

static inline void initialize_loop_symbol_object (void)
{
  loop_symbol_object = create_kl_symbol("loop");
}

static inline void register_primitive_kl_function_loop (void)
{
  initialize_loop_symbol_object();
  extend_symbol_name_table("loop", get_loop_symbol_object());
}

static inline void initialize_recur_symbol_object (void)
{
  recur_symbol_object = create_kl_symbol("recur");
}

static inline void register_primitive_kl_function_recur (void)
{
  initialize_recur_symbol_object();
  extend_symbol_name_table("recur", get_recur_symbol_object());
}

void register_extension_primitive_kl_functions (void)
{
  register_primitive_kl_function_println();
  register_primitive_kl_function_quit();
  register_primitive_kl_function_loop();
  register_primitive_kl_function_recur();
}
