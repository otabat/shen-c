#ifndef SHEN_C_VARIABLE_H
#define SHEN_C_VARIABLE_H

#include <stdio.h>

#include "environment.h"
#include "exception.h"
#include "kl.h"
#include "list.h"
#include "object.h"
#include "stream.h"
#include "string.h"
#include "symbol.h"

extern KLObject* earmuff_language_symbol_object;
extern KLObject* earmuff_implementation_symbol_object;
extern KLObject* earmuff_home_directory_symbol_object;
extern KLObject* earmuff_release_symbol_object;
extern KLObject* earmuff_port_symbol_object;
extern KLObject* earmuff_porters_symbol_object;
extern KLObject* earmuff_stinput_symbol_object;
extern KLObject* earmuff_stoutput_symbol_object;
extern KLObject* earmuff_sterror_symbol_object;
extern KLObject* earmuff_argv_symbol_object;

KLObject* get_variable_value (KLObject* symbol_object,
                              Environment* variable_environment);
KLObject* set_variable_value (KLObject* symbol_object, KLObject* object,
                              Environment* variable_environment);
void register_global_variables (void);

inline KLObject* get_earmuff_language_symbol_object (void)
{
  return earmuff_language_symbol_object;
}

inline KLObject* get_earmuff_implementation_symbol_object (void)
{
  return earmuff_implementation_symbol_object;
}

inline KLObject* get_earmuff_home_directory_symbol_object (void)
{
  return earmuff_home_directory_symbol_object;
}

inline KLObject* get_earmuff_release_symbol_object (void)
{
  return earmuff_release_symbol_object;
}

inline KLObject* get_earmuff_port_symbol_object (void)
{
  return earmuff_port_symbol_object;
}

inline KLObject* get_earmuff_porters_symbol_object (void)
{
  return earmuff_porters_symbol_object;
}

inline KLObject* get_earmuff_stinput_symbol_object (void)
{
  return earmuff_stinput_symbol_object;
}

inline KLObject* get_earmuff_stoutput_symbol_object (void)
{
  return earmuff_stoutput_symbol_object;
}

inline KLObject* get_earmuff_sterror_symbol_object (void)
{
  return earmuff_sterror_symbol_object;
}

inline KLObject* get_earmuff_argv_symbol_object (void)
{
  return earmuff_argv_symbol_object;
}

#endif
