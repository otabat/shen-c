#include "list.h"

extern Pair* get_pair (KLObject* list_object);
extern void set_pair (KLObject* list_object, Pair* pair);
extern KLObject* create_kl_list (KLObject* car_object, KLObject* cdr_object);
extern KLObject* get_head_kl_list (KLObject* list_object);
extern void set_head_kl_list (KLObject* list_object, KLObject* car_object);
extern KLObject* get_tail_kl_list (KLObject* list_object);
extern void set_tail_kl_list (KLObject* list_object, KLObject* cdr_object);
extern bool is_kl_list (KLObject* object);
extern bool is_non_empty_kl_list (KLObject* object);
extern long get_kl_list_size (KLObject* list_object);
