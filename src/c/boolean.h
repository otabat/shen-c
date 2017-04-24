#ifndef SHEN_C_BOOLEAN_H
#define SHEN_C_BOOLEAN_H

#include <stdbool.h>

#include "kl.h"

extern KLObject* true_boolean_object;
extern KLObject* false_boolean_object;

inline bool get_boolean (KLObject* boolean_object)
{
  return boolean_object->value.boolean;
}

inline void set_boolean (KLObject* boolean_object, bool boolean)
{
  boolean_object->value.boolean = boolean;
}

inline KLObject* create_kl_boolean (bool boolean)
{
  KLObject* boolean_object = create_kl_object(KL_TYPE_BOOLEAN);

  set_boolean(boolean_object, boolean);

  return boolean_object;
}

inline void initialize_true_boolean_object (void)
{
  true_boolean_object = create_kl_boolean(true);
}

inline void initialize_false_boolean_object (void)
{
  false_boolean_object = create_kl_boolean(false);
}

inline void initialize_boolean_objects (void)
{
  initialize_true_boolean_object();
  initialize_false_boolean_object();
}

inline KLObject* get_true_boolean_object (void)
{
  return true_boolean_object;
}

inline KLObject* get_false_boolean_object (void)
{
  return false_boolean_object;
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
  return left_object == right_object;
}

#endif
