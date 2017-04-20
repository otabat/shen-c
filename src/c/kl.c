#include "kl.h"

KLObject* empty_list_object = NULL;

extern KLType get_kl_object_type (KLObject* object);
extern void set_kl_object_type (KLObject* object, KLType type);
extern KLObject* create_kl_object (KLType type);
extern bool is_null (void* object);
extern bool is_not_null (void* object);

extern KLObject* get_pair_car (Pair* pair);
extern void set_pair_car (Pair* pair, KLObject* object);
extern KLObject* get_pair_cdr (Pair* pair);
extern void set_pair_cdr (Pair* pair, KLObject* object);
extern Pair* create_pair (KLObject* car_object, KLObject* cdr_object);

extern void initialize_empty_kl_list (void);
extern KLObject* get_empty_kl_list (void);
extern bool is_empty_kl_list (KLObject* object);
