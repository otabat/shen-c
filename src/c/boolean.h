#ifndef SHEN_C_BOOLEAN_H
#define SHEN_C_BOOLEAN_H

#include <stdbool.h>

#include "kl.h"

inline KLObject* create_kl_boolean (bool boolean)
{
  KLObject* object = create_kl_object(KL_TYPE_BOOLEAN);

  object->value.boolean = boolean;

  return object;
}

inline bool get_boolean (KLObject* boolean_object)
{
  return boolean_object->value.boolean;
}

inline void set_boolean (KLObject* boolean_object, bool boolean)
{
  boolean_object->value.boolean = boolean;
}

inline bool is_kl_boolean (KLObject* object)
{
  return get_kl_object_type(object) == KL_TYPE_BOOLEAN;
}

inline char* kl_boolean_to_string (KLObject* boolean_object)
{
  return (get_boolean(boolean_object)) ? "true" : "false";
}

inline bool is_kl_boolean_equal (KLObject* left_object, KLObject* right_object)
{
  return (is_kl_boolean(left_object) && is_kl_boolean(right_object) &&
          get_boolean(left_object) == get_boolean(right_object));
}

#endif
