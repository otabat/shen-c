#ifndef SHEN_C_NUMBER_H
#define SHEN_C_NUMBER_H

#include <stdbool.h>
#include <float.h>

#include "character.h"
#include "exception.h"
#include "kl.h"

KLObject* add_kl_number (KLObject* k, KLObject* l);
KLObject* subtract_kl_number (KLObject* k, KLObject* l);
KLObject* multiply_kl_number (KLObject* k, KLObject* l);
KLObject* divide_kl_number (KLObject* k, KLObject* l);
bool is_kl_number_equal (KLObject* k, KLObject* l);
bool is_kl_number_greater (KLObject* k, KLObject* l);
bool is_kl_number_less (KLObject* k, KLObject* l);
bool is_kl_number_greater_or_equal (KLObject* k, KLObject* l);
bool is_kl_number_less_or_equal (KLObject* k, KLObject* l);

unsigned long count_unsigned_digits_length (unsigned long x);

inline KLNumberType get_number_number_type (Number* number)
{
  return number->number_type;
}

inline void set_number_number_type (Number* number, KLNumberType number_type)
{
  number->number_type = number_type;
}

inline long get_number_number_l (Number* number)
{
  return number->value.number_l;
}

inline void set_number_number_l (Number* number, long x)
{
  number->value.number_l = x;
}

inline double get_number_number_d (Number* number)
{
  return number->value.number_d;
}

inline void set_number_number_d (Number* number, double x)
{
  number->value.number_d = x;
}

inline Number* create_number_l (long x)
{
  Number* number = malloc(sizeof(Number));

  set_number_number_type(number, KL_NUMBER_TYPE_LONG);
  set_number_number_l(number, x);

  return number;
}

inline Number* create_number_d (double x)
{
  Number* number = malloc(sizeof(Number));

  set_number_number_type(number, KL_NUMBER_TYPE_DOUBLE);
  set_number_number_d(number, x);

  return number;
}

inline Number* get_number (KLObject* number_object)
{
  return number_object->value.number;
}

inline void set_number (KLObject* number_object, Number* number)
{
  number_object->value.number = number;
}

inline KLObject* create_kl_number_l (long x)
{
  KLObject* number_object = create_kl_object(KL_TYPE_NUMBER);
  Number* number = create_number_l(x);

  set_number(number_object, number);

  return number_object;
}

inline KLObject* create_kl_number_d (double x)
{
  KLObject* number_object = create_kl_object(KL_TYPE_NUMBER);
  Number* number = create_number_d(x);

  set_number(number_object, number);

  return number_object;
}

inline long get_kl_number_number_l (KLObject* number_object)
{
  return get_number_number_l(get_number(number_object));
}

inline double get_kl_number_number_d (KLObject* number_object)
{
  return get_number_number_d(get_number(number_object));
}

inline KLNumberType get_kl_number_number_type (KLObject* number_object)
{
  return get_number_number_type(get_number(number_object));
}

inline bool is_kl_number (KLObject* object)
{
  return get_kl_object_type(object) == KL_TYPE_NUMBER;
}

inline bool is_kl_number_l (KLObject* object)
{
  return (is_kl_number(object) &&
          get_kl_number_number_type(object) == KL_NUMBER_TYPE_LONG);
}

inline bool is_kl_number_d (KLObject* object)
{
  return (is_kl_number(object) &&
          get_kl_number_number_type(object) == KL_NUMBER_TYPE_DOUBLE);
}

inline KLObject* kl_number_l_to_kl_number_d (KLObject* number_object)
{
  return create_kl_number_d((double)get_kl_number_number_l(number_object));
}

inline KLObject* kl_number_d_to_kl_number_l (KLObject* number_object)
{
  return create_kl_number_l((long)get_kl_number_number_d(number_object));
}

#endif
