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

#define CONS(car_object, cdr_object) create_kl_list(car_object, cdr_object)

#define CAR(list_object) get_head_kl_list(list_object)
#define CAAR(list_object) CAR(CAR(list_object))
#define CAAAR(list_object) CAR(CAAR(list_object))
#define CAAAAR(list_object) CAR(CAAAR(list_object))
#define CAAAAAR(list_object) CAR(CAAAAR(list_object))
#define CAAAAAAR(list_object) CAR(CAAAAAR(list_object))
#define CAAAAAAAR(list_object) CAR(CAAAAAAR(list_object))
#define CAAAAAAAAR(list_object) CAR(CAAAAAAAR(list_object))
#define CAAAAAAAAAR(list_object) CAR(CAAAAAAAAR(list_object))

#define CDR(list_object) get_tail_kl_list(list_object)
#define CDDR(list_object) CDR(CDR(list_object))
#define CDDDR(list_object) CDR(CDDR(list_object))
#define CDDDDR(list_object) CDR(CDDDR(list_object))
#define CDDDDDR(list_object) CDR(CDDDDR(list_object))
#define CDDDDDDR(list_object) CDR(CDDDDDR(list_object))
#define CDDDDDDDR(list_object) CDR(CDDDDDDR(list_object))
#define CDDDDDDDDR(list_object) CDR(CDDDDDDDR(list_object))
#define CDDDDDDDDDR(list_object) CDR(CDDDDDDDDR(list_object))

#define CADR(list_object) CAR(CDR(list_object))
#define CDAR(list_object) CDR(CAR(list_object))
#define CADDR(list_object) CAR(CDR(CDR(list_object)))
#define CDADR(list_object) CDR(CAR(CDR(list_object)))
#define CDDAR(list_object) CDR(CDR(CAR(list_object)))
#define CAADR(list_object) CAR(CAR(CDR(list_object)))
#define CADAR(list_object) CAR(CDR(CAR(list_object)))
#define CDAAR(list_object) CDR(CAR(CAR(list_object)))
#define CADDDR(list_object) CAR(CDR(CDR(CDR(list_object))))
#define CDADDR(list_object) CDR(CAR(CDR(CDR(list_object))))
#define CDDADR(list_object) CDR(CDR(CAR(CDR(list_object))))
#define CDDDAR(list_object) CDR(CDR(CDR(CAR(list_object))))
#define CAADDR(list_object) CAR(CAR(CDR(CDR(list_object))))
#define CADADR(list_object) CAR(CDR(CAR(CDR(list_object))))
#define CADDAR(list_object) CAR(CDR(CDR(CAR(list_object))))
#define CDAADR(list_object) CDR(CAR(CAR(CDR(list_object))))
#define CDADAR(list_object) CDR(CAR(CDR(CAR(list_object))))
#define CDDAAR(list_object) CDR(CDR(CAR(CAR(list_object))))
#define CAAADR(list_object) CAR(CAR(CAR(CDR(list_object))))
#define CAADAR(list_object) CAR(CAR(CDR(CAR(list_object))))
#define CADAAR(list_object) CAR(CDR(CAR(CAR(list_object))))
#define CDAAAR(list_object) CDR(CAR(CAR(CAR(list_object))))

#endif
