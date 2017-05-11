#ifndef SHEN_C_LIST_H
#define SHEN_C_LIST_H

#include "exception.h"
#include "kl.h"

inline Pair* get_pair (KLObject* list_object)
{
  return list_object->value.pair;
}

inline void set_pair (KLObject* list_object, Pair* pair)
{
  list_object->value.pair = pair;
}

inline KLObject* create_kl_list (KLObject* car_object, KLObject* cdr_object)
{
  KLObject* list_object = create_kl_object(KL_TYPE_LIST);
  Pair* pair = create_pair(car_object, cdr_object);

  set_pair(list_object, pair);

  return list_object;
}

inline KLObject* get_head_kl_list (KLObject* list_object)
{
  return get_pair_car(get_pair(list_object));;
}

inline void set_head_kl_list (KLObject* list_object, KLObject* car_object)
{
  set_pair_car(get_pair(list_object), car_object);
}

inline KLObject* get_tail_kl_list (KLObject* list_object)
{
  return get_pair_cdr(get_pair(list_object));
}

inline void set_tail_kl_list (KLObject* list_object, KLObject* cdr_object)
{
  set_pair_cdr(get_pair(list_object), cdr_object);
}

inline bool is_kl_list (KLObject* object)
{
  return get_kl_object_type(object) == KL_TYPE_LIST;
}

inline bool is_non_empty_kl_list (KLObject* object)
{
  return is_kl_list(object) && !is_empty_kl_list(object);
}

inline long get_kl_list_size (KLObject* list_object)
{
  KLObject* object = list_object;
  long size = 0;

  while (!is_empty_kl_list(object)) {
    ++size;
    object = get_tail_kl_list(object);
  }

  return size;
}

#endif
