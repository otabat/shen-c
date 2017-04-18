#include "boolean.h"

KLObject* create_kl_boolean (bool boolean)
{
  KLObject* object = create_kl_object(KL_TYPE_BOOLEAN);

  object->value.boolean = boolean;

  return object;
}

bool get_boolean (KLObject* boolean_object)
{
  return boolean_object->value.boolean;
}

void set_boolean (KLObject* boolean_object, bool boolean)
{
  boolean_object->value.boolean = boolean;
}

bool is_kl_boolean (KLObject* object)
{
  return get_kl_object_type(object) == KL_TYPE_BOOLEAN;
}

char* kl_boolean_to_string (KLObject* boolean_object)
{
  return (get_boolean(boolean_object)) ? "true" : "false";
}

bool is_kl_boolean_equal (KLObject* left_object, KLObject* right_object)
{
  return (is_kl_boolean(left_object) && is_kl_boolean(right_object) &&
          get_boolean(left_object) == get_boolean(right_object));
}
