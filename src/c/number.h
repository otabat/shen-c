#ifndef SHEN_C_NUMBER_H
#define SHEN_C_NUMBER_H

#include <stdbool.h>
#include <float.h>

#include "character.h"
#include "exception.h"
#include "kl.h"

KLNumberType get_number_number_type (Number* number);
void set_number_number_type (Number* number, KLNumberType number_type);
long get_number_number_l (Number* number);
void set_number_number_l (Number* number, long x);
double get_number_number_d (Number* number);
void set_number_number_d (Number* number, double x);
Number* create_number_l (long x);
Number* create_number_d (double x);

Number* get_number (KLObject* number_object);
void set_number (KLObject* number_object, Number* number);
KLObject* create_kl_number_l (long x);
KLObject* create_kl_number_d (double x);
long get_kl_number_number_l (KLObject* number_object);
double get_kl_number_number_d (KLObject* number_object);
KLNumberType get_kl_number_number_type (KLObject* number_object);

bool is_kl_number (KLObject* object);
bool is_kl_number_l (KLObject* object);
bool is_kl_number_d (KLObject* object);
KLObject* kl_number_l_to_kl_number_d (KLObject* number_object);
KLObject* kl_number_d_to_kl_number_l (KLObject* number_object);
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

#endif
