#include "number.h"

extern KLNumberType get_number_number_type (Number* number);
extern void set_number_number_type (Number* number, KLNumberType number_type);
extern long get_number_number_l (Number* number);
extern void set_number_number_l (Number* number, long x);
extern double get_number_number_d (Number* number);
extern void set_number_number_d (Number* number, double x);
extern Number* create_number_l (long x);
extern Number* create_number_d (double x);

extern Number* get_number (KLObject* number_object);
extern void set_number (KLObject* number_object, Number* number);
extern KLObject* create_kl_number_l (long x);
extern KLObject* create_kl_number_d (double x);
extern long get_kl_number_number_l (KLObject* number_object);
extern double get_kl_number_number_d (KLObject* number_object);
extern KLNumberType get_kl_number_number_type (KLObject* number_object);

extern bool is_kl_number (KLObject* object);
extern bool is_kl_number_l (KLObject* object);
extern bool is_kl_number_d (KLObject* object);
extern KLObject* kl_number_l_to_kl_number_d (KLObject* number_object);
extern KLObject* kl_number_d_to_kl_number_l (KLObject* number_object);

static inline long add_number_l_l (long x, long y) { return x + y; }
static inline double add_number_l_d (long x, double y) { return (double)x + y; }
static inline double add_number_d_l (double x, long y) { return x + (double)y; }
static inline double add_number_d_d (double x, double y) { return x + y; }

static inline KLObject* add_kl_number_l_l (KLObject* k, KLObject* l)
{
  long x = add_number_l_l(get_kl_number_number_l(k), get_kl_number_number_l(l));

  return  create_kl_number_l(x);
}

static inline KLObject* add_kl_number_l_d (KLObject* k, KLObject* l)
{
  double x = add_number_l_d(get_kl_number_number_l(k), get_kl_number_number_d(l));

  return create_kl_number_d(x);
}

static inline KLObject* add_kl_number_d_l (KLObject* k, KLObject* l)
{
  double x = add_number_d_l(get_kl_number_number_d(k), get_kl_number_number_l(l));

  return create_kl_number_d(x);
}

static inline KLObject* add_kl_number_d_d (KLObject* k, KLObject* l)
{
  double x = add_number_d_d(get_kl_number_number_d(k), get_kl_number_number_d(l));

  return create_kl_number_d(x);
}

KLObject* add_kl_number (KLObject* k, KLObject* l)
{
  if (is_kl_number_l(k)) {
    if (is_kl_number_l(l))
      return add_kl_number_l_l(k, l);

    return add_kl_number_l_d(k, l);
  }

  if (is_kl_number_l(l))
    return add_kl_number_d_l(k, l);

  return add_kl_number_d_d(k, l);
}

static inline long subtract_number_l_l (long x, long y) { return x - y; }

static inline double subtract_number_l_d (long x, double y)
{
  return (double)x - y;
}

static inline double subtract_number_d_l (double x, long y)
{
  return x - (double)y;
}

static inline double subtract_number_d_d (double x, double y) { return x - y; }

static inline KLObject* subtract_kl_number_l_l (KLObject* k, KLObject* l)
{
  long x = subtract_number_l_l(get_kl_number_number_l(k),
                               get_kl_number_number_l(l));

  return  create_kl_number_l(x);
}

static inline KLObject* subtract_kl_number_l_d (KLObject* k, KLObject* l)
{
  double x = subtract_number_l_d(get_kl_number_number_l(k),
                                 get_kl_number_number_d(l));

  return create_kl_number_d(x);
}

static inline KLObject* subtract_kl_number_d_l (KLObject* k, KLObject* l)
{
  double x = subtract_number_d_l(get_kl_number_number_d(k),
                                 get_kl_number_number_l(l));

  return create_kl_number_d(x);
}

static inline KLObject* subtract_kl_number_d_d (KLObject* k, KLObject* l)
{
  double x = subtract_number_d_d(get_kl_number_number_d(k),
                                 get_kl_number_number_d(l));

  return create_kl_number_d(x);
}

KLObject* subtract_kl_number (KLObject* k, KLObject* l)
{
  if (is_kl_number_l(k)) {
    if (is_kl_number_l(l))
      return subtract_kl_number_l_l(k, l);

    return subtract_kl_number_l_d(k, l);
  }

  if (is_kl_number_l(l))
    return subtract_kl_number_d_l(k, l);

  return subtract_kl_number_d_d(k, l);
}

static inline long multiply_number_l_l (long x, long y) { return x * y; }

static inline double multiply_number_l_d (long x, double y)
{
  return (double)x * y;
}

static inline double multiply_number_d_l (double x, long y)
{
  return x * (double)y;
} 

static inline double multiply_number_d_d (double x, double y) { return x * y; }

static inline KLObject* multiply_kl_number_l_l (KLObject* k, KLObject* l)
{
  long x = multiply_number_l_l(get_kl_number_number_l(k),
                               get_kl_number_number_l(l));

  return  create_kl_number_l(x);
}

static inline KLObject* multiply_kl_number_l_d (KLObject* k, KLObject* l)
{
  double x = multiply_number_l_d(get_kl_number_number_l(k),
                                 get_kl_number_number_d(l));

  return create_kl_number_d(x);
}

static inline KLObject* multiply_kl_number_d_l (KLObject* k, KLObject* l)
{
  double x = multiply_number_d_l(get_kl_number_number_d(k),
                                 get_kl_number_number_l(l));

  return create_kl_number_d(x);
}

static inline KLObject* multiply_kl_number_d_d (KLObject* k, KLObject* l)
{
  double x = multiply_number_d_d(get_kl_number_number_d(k),
                                 get_kl_number_number_d(l));

  return create_kl_number_d(x);
}

KLObject* multiply_kl_number (KLObject* k, KLObject* l)
{
  if (is_kl_number_l(k)) {
    if (is_kl_number_l(l))
      return multiply_kl_number_l_l(k, l);

    return multiply_kl_number_l_d(k, l);
  }

  if (is_kl_number_l(l))
    return multiply_kl_number_d_l(k, l);

  return multiply_kl_number_d_d(k, l);
}

static inline long divide_number_l_l (long x, long y) { return x / y; }
static inline double divide_number_l_d (long x, double y) { return (double)x / y; }
static inline double divide_number_d_l (double x, long y) { return x / (double)y; }
static inline double divide_number_d_d (double x, double y) { return x / y; }

static inline KLObject* divide_kl_number_l_l (KLObject* k, KLObject* l)
{
  long x = divide_number_l_l(get_kl_number_number_l(k),
                             get_kl_number_number_l(l));

  return  create_kl_number_l(x);
}

static inline KLObject* divide_kl_number_l_d (KLObject* k, KLObject* l)
{
  double x = divide_number_l_d(get_kl_number_number_l(k),
                               get_kl_number_number_d(l));

  return create_kl_number_d(x);
}

static inline KLObject* divide_kl_number_d_l (KLObject* k, KLObject* l)
{
  double x = divide_number_d_l(get_kl_number_number_d(k),
                               get_kl_number_number_l(l));

  return create_kl_number_d(x);
}

static inline KLObject* divide_kl_number_d_d (KLObject* k, KLObject* l)
{
  double x = divide_number_d_d(get_kl_number_number_d(k),
                               get_kl_number_number_d(l));

  return create_kl_number_d(x);
}

static inline void check_kl_number_l_zero_division (KLObject* number_object)
{
  if (get_kl_number_number_l(number_object) == 0) {
    throw_kl_exception("Division by zero");
  }
}

static inline void check_kl_number_d_zero_division (KLObject* number_object)
{
  if (get_kl_number_number_d(number_object) == 0.0) {
    throw_kl_exception("Division by zero");
  }
}

KLObject* divide_kl_number (KLObject* k, KLObject* l)
{
  if (is_kl_number_l(k)) {
    if (is_kl_number_l(l)) {
      check_kl_number_l_zero_division(l);
      
      if (get_kl_number_number_l(k) % get_kl_number_number_l(l) == 0)
        return divide_kl_number_l_l(k, l);

      return divide_kl_number_l_d(k, kl_number_l_to_kl_number_d(l));
    }
    
    check_kl_number_d_zero_division(l);

    return divide_kl_number_l_d(k, l);
  }

  if (is_kl_number_l(l)) {
    check_kl_number_l_zero_division(l);

    return divide_kl_number_d_l(k, l);
  }

  check_kl_number_d_zero_division(l);

  return divide_kl_number_d_d(k, l);
}

static inline bool is_number_equal_l_l (long x, long y) { return x == y; }

static inline bool is_number_equal_l_d (long x, double y)
{
  return (double)x == y;
}

static inline bool is_number_equal_d_l (double x, long y)
{
  return x == (double)y;
}

static inline bool is_number_equal_d_d (double x, double y) { return x == y; }

static inline bool is_kl_number_equal_l_l (KLObject* k, KLObject* l)
{
  return is_number_equal_l_l(get_kl_number_number_l(k),
                             get_kl_number_number_l(l));
}

static inline bool is_kl_number_equal_l_d (KLObject* k, KLObject* l)
{
  return is_number_equal_l_d(get_kl_number_number_l(k),
                             get_kl_number_number_d(l));
}

static inline bool is_kl_number_equal_d_l (KLObject* k, KLObject* l)
{
  return is_number_equal_d_l(get_kl_number_number_d(k),
                             get_kl_number_number_l(l));
}

static inline bool is_kl_number_equal_d_d (KLObject* k, KLObject* l)
{
  return is_number_equal_d_d(get_kl_number_number_d(k),
                             get_kl_number_number_d(l));
}

bool is_kl_number_equal (KLObject* k, KLObject* l)
{
  if (is_kl_number(k) && is_kl_number(l)) {
    if (is_kl_number_l(k)) {
      if (is_kl_number_l(l))
        return is_kl_number_equal_l_l(k, l);

      return is_kl_number_equal_l_d(k, l);
    }

    if (is_kl_number_l(l))
      return is_kl_number_equal_d_l(k, l);

    return is_kl_number_equal_d_d(k, l);
  }

  return false;
}

static inline bool is_number_greater_l_l (long x, long y) { return x > y; }

static inline bool is_number_greater_l_d (long x, double y)
{
  return (double)x > y;
}

static inline bool is_number_greater_d_l (double x, long y)
{
  return x > (double)y;
}
static inline bool is_number_greater_d_d (double x, double y) { return x > y; }

static inline bool is_kl_number_greater_l_l (KLObject* k, KLObject* l)
{
  return is_number_greater_l_l(get_kl_number_number_l(k),
                               get_kl_number_number_l(l));
}

static inline bool is_kl_number_greater_l_d (KLObject* k, KLObject* l)
{
  return is_number_greater_l_d(get_kl_number_number_l(k),
                               get_kl_number_number_d(l));
}

static inline bool is_kl_number_greater_d_l (KLObject* k, KLObject* l)
{
  return is_number_greater_d_l(get_kl_number_number_d(k),
                               get_kl_number_number_l(l));
}

static inline bool is_kl_number_greater_d_d (KLObject* k, KLObject* l)
{
  return is_number_greater_d_d(get_kl_number_number_d(k),
                               get_kl_number_number_d(l));
}

bool is_kl_number_greater (KLObject* k, KLObject* l)
{
  if (is_kl_number(k) && is_kl_number(l)) {
    if (is_kl_number_l(k)) {
      if (is_kl_number_l(l))
        return is_kl_number_greater_l_l(k, l);

      return is_kl_number_greater_l_d(k, l);
    }

    if (is_kl_number_l(l))
      return is_kl_number_greater_d_l(k, l);

    return is_kl_number_greater_d_d(k, l);
  }

  throw_kl_exception("Comparison of non numbers"); 

  return false;
}

static inline bool is_number_less_l_l (long x, long y) { return x < y; }
static inline bool is_number_less_l_d (long x, double y) { return (double)x < y; }
static inline bool is_number_less_d_l (double x, long y) { return x < (double)y; }
static inline bool is_number_less_d_d (double x, double y) { return x < y; }

static inline bool is_kl_number_less_l_l (KLObject* k, KLObject* l)
{
  return is_number_less_l_l(get_kl_number_number_l(k), get_kl_number_number_l(l));
}

static inline bool is_kl_number_less_l_d (KLObject* k, KLObject* l)
{
  return is_number_less_l_d(get_kl_number_number_l(k), get_kl_number_number_d(l));
}

static inline bool is_kl_number_less_d_l (KLObject* k, KLObject* l)
{
  return is_number_less_d_l(get_kl_number_number_d(k), get_kl_number_number_l(l));
}

static inline bool is_kl_number_less_d_d (KLObject* k, KLObject* l)
{
  return is_number_less_d_d(get_kl_number_number_d(k), get_kl_number_number_d(l));
}

bool is_kl_number_less (KLObject* k, KLObject* l)
{
  if (is_kl_number(k) && is_kl_number(l)) {
    if (is_kl_number_l(k)) {
      if (is_kl_number_l(l))
        return is_kl_number_less_l_l(k, l);

      return is_kl_number_less_l_d(k, l);
    }

    if (is_kl_number_l(l))
      return is_kl_number_less_d_l(k, l);

    return is_kl_number_less_d_d(k, l);
  }

  throw_kl_exception("Comparison of non numbers");

  return false;
}

static inline bool is_number_greater_or_equal_l_l (long x, long y)
{
  return x >= y;
}

static inline bool is_number_greater_or_equal_l_d (long x, double y)
{
  return (double)x >= y;
}

static inline bool is_number_greater_or_equal_d_l (double x, long y)
{
  return x >= (double)y;
}

static inline bool is_number_greater_or_equal_d_d (double x, double y)
{
  return x >= y;
}

static inline bool is_kl_number_greater_or_equal_l_l (KLObject* k, KLObject* l)
{
  return is_number_greater_or_equal_l_l(get_kl_number_number_l(k),
                                        get_kl_number_number_l(l));
}

static inline bool is_kl_number_greater_or_equal_l_d (KLObject* k, KLObject* l)
{
  return is_number_greater_or_equal_l_d(get_kl_number_number_l(k),
                                        get_kl_number_number_d(l));
}

static inline bool is_kl_number_greater_or_equal_d_l (KLObject* k, KLObject* l)
{
  return is_number_greater_or_equal_d_l(get_kl_number_number_d(k),
                                        get_kl_number_number_l(l));
}

static inline bool is_kl_number_greater_or_equal_d_d (KLObject* k, KLObject* l)
{
  return is_number_greater_or_equal_d_d(get_kl_number_number_d(k),
                                        get_kl_number_number_d(l));
}

bool is_kl_number_greater_or_equal (KLObject* k, KLObject* l)
{
  if (is_kl_number(k) && is_kl_number(l)) {
    if (is_kl_number_l(k)) {
      if (is_kl_number_l(l))
        return is_kl_number_greater_or_equal_l_l(k, l);

      return is_kl_number_greater_or_equal_l_d(k, l);
    }

    if (is_kl_number_l(l))
      return is_kl_number_greater_or_equal_d_l(k, l);

    return is_kl_number_greater_or_equal_d_d(k, l);
  }

  throw_kl_exception("Comparison of non numbers");

  return false;
}

static inline bool is_number_less_or_equal_l_l (long x, long y)
{
  return x <= y;
}

static inline bool is_number_less_or_equal_l_d (long x, double y)
{
  return (double)x <= y;
}

static inline bool is_number_less_or_equal_d_l (double x, long y)
{
  return x <= (double)y;
}

static inline bool is_number_less_or_equal_d_d (double x, double y)
{
  return x <= y;
}

static inline bool is_kl_number_less_or_equal_l_l (KLObject* k, KLObject* l)
{
  return is_number_less_or_equal_l_l(get_kl_number_number_l(k),
                                     get_kl_number_number_l(l));
}

static inline bool is_kl_number_less_or_equal_l_d (KLObject* k, KLObject* l)
{
  return is_number_less_or_equal_l_d(get_kl_number_number_l(k),
                                     get_kl_number_number_d(l));
}

static inline bool is_kl_number_less_or_equal_d_l (KLObject* k, KLObject* l)
{
  return is_number_less_or_equal_d_l(get_kl_number_number_d(k),
                                     get_kl_number_number_l(l));
}

static inline bool is_kl_number_less_or_equal_d_d (KLObject* k, KLObject* l)
{
  return is_number_less_or_equal_d_d(get_kl_number_number_d(k),
                                     get_kl_number_number_d(l));
}

bool is_kl_number_less_or_equal (KLObject* k, KLObject* l)
{
  if (is_kl_number(k) && is_kl_number(l)) {
    if (is_kl_number_l(k)) {
      if (is_kl_number_l(l))
        return is_kl_number_less_or_equal_l_l(k, l);

      return is_kl_number_less_or_equal_l_d(k, l);
    }

    if (is_kl_number_l(l))
      return is_kl_number_less_or_equal_d_l(k, l);

    return is_kl_number_less_or_equal_d_d(k, l);
  }

  throw_kl_exception("Comparison of non numbers");

  return false;
}

unsigned long count_unsigned_digits_length (unsigned long x)
{
    unsigned long y = 1;

    while (x > 9) {
        x /= 10;
        ++y;
    }

    return y;
}
