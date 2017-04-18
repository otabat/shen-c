#ifndef SHEN_C_LIST_H
#define SHEN_C_LIST_H

#include "exception.h"
#include "kl.h"

Pair* get_pair (KLObject* list_object);
void set_pair (KLObject* list_object, Pair* pair);
KLObject* create_kl_list (KLObject* car_object, KLObject* cdr_object);
KLObject* get_head_kl_list (KLObject* list_object);
void set_head_kl_list (KLObject* list_object, KLObject* car_object);
KLObject* get_tail_kl_list (KLObject* list_object);
void set_tail_kl_list (KLObject* list_object, KLObject* cdr_object);
bool is_kl_list (KLObject* object);
bool is_non_empty_kl_list (KLObject* object);
size_t get_kl_list_size (KLObject* list_object);

#endif
