#include "boolean.h"

extern KLObject* create_kl_boolean (bool boolean);
extern bool get_boolean (KLObject* boolean_object);
extern void set_boolean (KLObject* boolean_object, bool boolean);
extern bool is_kl_boolean (KLObject* boolean_object);
extern char* kl_boolean_to_string (KLObject* boolean_object);
extern bool is_kl_boolean_equal (KLObject* left_object, KLObject* right_object);
