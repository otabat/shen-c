#include "boolean.h"

KLObject* true_boolean_object;
KLObject* false_boolean_object;

extern bool get_boolean (KLObject* boolean_object);
extern void set_boolean (KLObject* boolean_object, bool boolean);
extern KLObject* create_kl_boolean (bool boolean);
extern void initialize_true_boolean_object (void);
extern void initialize_false_boolean_object (void);
extern void initialize_boolean_objects (void);
extern KLObject* get_true_boolean_object (void);
extern KLObject* get_false_boolean_object (void);
extern bool is_kl_boolean (KLObject* boolean_object);
extern char* kl_boolean_to_string (KLObject* boolean_object);
extern bool is_kl_boolean_equal (KLObject* left_object, KLObject* right_object);
