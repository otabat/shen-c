#include "variable.h"

KLObject* earmuff_language_symbol_object;
KLObject* earmuff_implementation_symbol_object;
KLObject* earmuff_home_directory_symbol_object;
KLObject* earmuff_release_symbol_object;
KLObject* earmuff_port_symbol_object;
KLObject* earmuff_porters_symbol_object;
KLObject* earmuff_stinput_symbol_object;
KLObject* earmuff_stoutput_symbol_object;
KLObject* earmuff_sterror_symbol_object;
KLObject* earmuff_argv_symbol_object;

extern KLObject* get_earmuff_language_symbol_object (void);
extern KLObject* get_earmuff_implementation_symbol_object (void);
extern KLObject* get_earmuff_home_directory_symbol_object (void);
extern KLObject* get_earmuff_release_symbol_object (void);
extern KLObject* get_earmuff_port_symbol_object (void);
extern KLObject* get_earmuff_porters_symbol_object (void);
extern KLObject* get_earmuff_stinput_symbol_object (void);
extern KLObject* get_earmuff_stoutput_symbol_object (void);
extern KLObject* get_earmuff_sterror_symbol_object (void);
extern KLObject* get_earmuff_argv_symbol_object (void);

KLObject* get_variable_value (KLObject* symbol_object,
                              Environment* variable_environment)
{
  if (!is_kl_symbol(symbol_object)) {
    int error_message_length =
      snprintf(NULL, 0,
               "Failed to get a value of %s, which is not a symbol",
               kl_object_to_string(symbol_object));
    char* error_message = malloc(error_message_length + 1);

    sprintf(error_message, "Failed to get a value of %s, which is not a symbol",
            kl_object_to_string(symbol_object));

    throw_kl_exception(error_message);
  }
  
  KLObject* object = get_kl_symbol_variable_value(symbol_object);

  if (is_null(object))
    throw_kl_exception("Undefined variable");

  return object;
}

KLObject* set_variable_value (KLObject* symbol_object, KLObject* object,
                              Environment* variable_environment)
{
  if (!is_kl_symbol(symbol_object)) {
    int error_message_length =
      snprintf(NULL, 0,
               "Failed to set value to %s, which is not a symbol",
               kl_object_to_string(symbol_object));
    char* error_message = malloc((size_t)error_message_length + 1);

    sprintf(error_message, "Failed to set value to %s, which is not a symbol",
            kl_object_to_string(symbol_object));

    throw_kl_exception(error_message);
  }

  set_kl_symbol_variable_value(symbol_object, object);

  return object;
}

static inline void initialize_earmuff_language_symbol_object (void)
{
  earmuff_language_symbol_object = create_kl_symbol_by_name("*language*");
  set_kl_symbol_variable_value(earmuff_language_symbol_object,
                               create_kl_symbol_by_name("C"));
}

static inline void register_global_variable_earmuff_language (void)
{
  initialize_earmuff_language_symbol_object();
  extend_symbol_table(create_kl_string_with_intern("*language*"),
                      get_earmuff_language_symbol_object());
}

static inline void initialize_earmuff_implementation_symbol_object (void)
{
  earmuff_implementation_symbol_object = create_kl_symbol_by_name("*implementation*");
  set_kl_symbol_variable_value(earmuff_implementation_symbol_object,
                               create_kl_symbol_by_name("C"));
}

static inline void register_global_variable_earmuff_implementation (void)
{
  initialize_earmuff_implementation_symbol_object();
  extend_symbol_table(create_kl_string_with_intern("*implementation*"),
                      get_earmuff_implementation_symbol_object());
}

static inline void initialize_earmuff_home_directory_symbol_object (void)
{
  earmuff_home_directory_symbol_object = create_kl_symbol_by_name("*home-directory*");
  set_kl_symbol_variable_value(earmuff_home_directory_symbol_object,
                               get_empty_string_object());
}

static inline void register_global_variable_earmuff_home_directory (void)
{
  initialize_earmuff_home_directory_symbol_object();
  extend_symbol_table(create_kl_string_with_intern("*home-directory*"),
                      get_earmuff_home_directory_symbol_object());
}

static inline void initialize_earmuff_release_symbol_object (void)
{
  earmuff_release_symbol_object = create_kl_symbol_by_name("*release*");
  set_kl_symbol_variable_value(earmuff_release_symbol_object,
                               create_kl_number_d(0.1));
}

static inline void register_global_variable_earmuff_release (void)
{
  initialize_earmuff_release_symbol_object();
  extend_symbol_table(create_kl_string_with_intern("*release*"),
                      get_earmuff_release_symbol_object());
}

static inline void initialize_earmuff_port_symbol_object (void)
{
  earmuff_port_symbol_object = create_kl_symbol_by_name("*port*");
  set_kl_symbol_variable_value(earmuff_port_symbol_object,
                               create_kl_string_with_intern("0.2.3"));
}

static inline void register_global_variable_earmuff_port (void)
{
  initialize_earmuff_port_symbol_object();
  extend_symbol_table(create_kl_string_with_intern("*port*"),
                      get_earmuff_port_symbol_object());
}

static inline void initialize_earmuff_porters_symbol_object (void)
{
  earmuff_porters_symbol_object = create_kl_symbol_by_name("*porters*");
  set_kl_symbol_variable_value(earmuff_porters_symbol_object,
                               create_kl_string_with_intern("Tatsuya Tsuda"));
}

static inline void register_global_variable_earmuff_porters (void)
{
  initialize_earmuff_porters_symbol_object();
  extend_symbol_table(create_kl_string_with_intern("*porters*"),
                      get_earmuff_porters_symbol_object());
}

static inline void initialize_earmuff_stinput_symbol_object (void)
{
  earmuff_stinput_symbol_object = create_kl_symbol_by_name("*stinput*");
  set_kl_symbol_variable_value(earmuff_stinput_symbol_object,
                               get_std_input_stream_object());
}

static inline void register_global_variable_earmuff_stinput (void)
{
  initialize_earmuff_stinput_symbol_object();
  extend_symbol_table(create_kl_string_with_intern("*stinput*"),
                      get_earmuff_stinput_symbol_object());
}

static inline void initialize_earmuff_stoutput_symbol_object (void)
{
  earmuff_stoutput_symbol_object = create_kl_symbol_by_name("*stoutput*");
  set_kl_symbol_variable_value(earmuff_stoutput_symbol_object,
                               get_std_output_stream_object());
}

static inline void register_global_variable_earmuff_stoutput (void)
{
  initialize_earmuff_stoutput_symbol_object();
  extend_symbol_table(create_kl_string_with_intern("*stoutput*"),
                      get_earmuff_stoutput_symbol_object());
}

static inline void initialize_earmuff_sterror_symbol_object (void)
{
  earmuff_sterror_symbol_object = create_kl_symbol_by_name("*sterror*");
  set_kl_symbol_variable_value(earmuff_sterror_symbol_object,
                               get_std_error_stream_object());
}

static inline void register_global_variable_earmuff_sterror (void)
{
  initialize_earmuff_sterror_symbol_object();
  extend_symbol_table(create_kl_string_with_intern("*sterror*"),
                      get_earmuff_sterror_symbol_object());
}

static inline void initialize_earmuff_argv_symbol_object (void)
{
  earmuff_argv_symbol_object = create_kl_symbol_by_name("argv");
  set_kl_symbol_variable_value(earmuff_argv_symbol_object,
                               CONS(create_kl_string_with_intern("shen"), EL));
}

static inline void register_global_variable_earmuff_argv (void)
{
  initialize_earmuff_argv_symbol_object();
  extend_symbol_table(create_kl_string_with_intern("*argv*"),
                      get_earmuff_argv_symbol_object());
}

void register_global_variables (void)
{
  register_global_variable_earmuff_language();
  register_global_variable_earmuff_implementation();
  register_global_variable_earmuff_home_directory();
  register_global_variable_earmuff_release();
  register_global_variable_earmuff_port();
  register_global_variable_earmuff_porters();
  register_global_variable_earmuff_stinput();
  register_global_variable_earmuff_stoutput();
  register_global_variable_earmuff_sterror();
  register_global_variable_earmuff_argv();
}
