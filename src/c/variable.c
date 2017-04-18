#include "variable.h"

KLObject* get_variable_value (KLObject* symbol_object,
                              Environment* variable_environment)
{
  if (!is_kl_symbol(symbol_object)) {
    char length_string[1]; 
    int error_message_length =
      snprintf(length_string, 1,
               "Failed to get a value of %s, which is not a symbol",
               kl_object_to_string(symbol_object));
    char* error_message = malloc(error_message_length + 1);

    sprintf(error_message, "Failed to get a value of %s, which is not a symbol",
            kl_object_to_string(symbol_object));

    throw_kl_exception(error_message);
  }
  
  Environment* matched_variable_environment = NULL;
  KLObject* object = lookup_environment(symbol_object, variable_environment,
                                        &matched_variable_environment);

  if (is_null(matched_variable_environment))
    throw_kl_exception("Undefined variable");

  return object;
}

KLObject* set_variable_value (KLObject* symbol_object, KLObject* object,
                              Environment* variable_environment)
{
  if (!is_kl_symbol(symbol_object)) {
    char length_string[1]; 
    int error_message_length =
      snprintf(length_string, 1,
               "Failed to set value to %s, which is not a symbol",
               kl_object_to_string(symbol_object));
    char* error_message = malloc(error_message_length + 1);

    sprintf(error_message, "Failed to set value to %s, which is not a symbol",
            kl_object_to_string(symbol_object));

    throw_kl_exception(error_message);
  }

  extend_environment(symbol_object, object, variable_environment);

  return object;
}
