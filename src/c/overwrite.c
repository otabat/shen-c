#include "overwrite.h"

static inline KLObject* primitive_function_hash (KLObject* function_object,
                                                 Vector* arguments)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return kl_object_bounded_hash(objects[0], objects[1]);
}

static inline KLObject* create_primitive_kl_function_hash (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_hash);

  return function_object;
}

static inline KLObject* primitive_function_is_symbol (KLObject* function_object,
                                                      Vector* arguments)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  if (is_kl_symbol(objects[0]))
    return get_true_boolean_object();

  return get_false_boolean_object();
}

static inline KLObject* create_primitive_kl_function_is_symbol (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_is_symbol);

  return function_object;
}

static inline KLObject* primitive_function_is_boolean (KLObject* function_object,
                                                       Vector* arguments)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  if (is_kl_boolean(objects[0]))
    return get_true_boolean_object();

  return get_false_boolean_object();
}

static inline KLObject* create_primitive_kl_function_is_boolean (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_is_boolean);

  return function_object;
}

static inline KLObject* primitive_function_is_integer (KLObject* function_object,
                                                       Vector* arguments)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  if (is_kl_number_l(objects[0]))
    return get_true_boolean_object();

  return get_false_boolean_object();
}

static inline KLObject* create_primitive_kl_function_is_integer (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_is_integer);

  return function_object;
}

static inline KLObject* primitive_function_is_variable (KLObject* function_object,
                                                        Vector* arguments)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  if (is_kl_symbol(objects[0])) {
    char* symbol = get_symbol(objects[0]);

    if (is_uppercase_alphabet_character(symbol[0]))
      return get_true_boolean_object();

    return get_false_boolean_object();
  }

  return get_false_boolean_object();
}

static inline KLObject* create_primitive_kl_function_is_variable (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_is_variable);

  return function_object;
}

static inline KLObject* primitive_function_not (KLObject* function_object,
                                                Vector* arguments)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  if (get_boolean(objects[0]))
    return get_false_boolean_object();

  return get_true_boolean_object();
}

static inline KLObject* create_primitive_kl_function_not (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_not);

  return function_object;
}

static inline KLObject* primitive_function_is_numbyte (KLObject* function_object,
                                                       Vector* arguments)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);
  long x = get_kl_number_number_l(objects[0]);

  if ((x >= 48 && x <= 57))
    return get_true_boolean_object();

  return get_false_boolean_object();
}

static inline KLObject* create_primitive_kl_function_is_numbyte (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_is_numbyte);

  return function_object;
}

static inline KLObject* primitive_function_byte_to_digit (KLObject* function_object,
                                                          Vector* arguments)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  long x = get_kl_number_number_l(objects[0]);

  switch (x) {
  case 48: return create_kl_number_l(0);
  case 49: return create_kl_number_l(1);
  case 50: return create_kl_number_l(2);
  case 51: return create_kl_number_l(3);
  case 52: return create_kl_number_l(4);
  case 53: return create_kl_number_l(5);
  case 54: return create_kl_number_l(6);
  case 55: return create_kl_number_l(7);
  case 56: return create_kl_number_l(8);
  case 57: return create_kl_number_l(9);
  default: throw_kl_exception("Out of range error in shen.byte->digit");
  }

  return create_kl_number_l(0);
}

static inline KLObject* create_primitive_kl_function_byte_to_digit (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_byte_to_digit);

  return function_object;
}

static inline KLObject* primitive_function_is_pvar (KLObject* function_object,
                                                    Vector* arguments)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  if (is_kl_vector(objects[0])) {
    Vector* vector = get_vector(objects[0]);
    KLObject* object = get_vector_element(vector, 0);

    if (is_kl_symbol(object) && strcmp(get_symbol(object), "shen.pvar") == 0)
      return get_true_boolean_object();

    return get_false_boolean_object();
  }

  return get_false_boolean_object();
}

static inline KLObject* create_primitive_kl_function_is_pvar (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_is_pvar);

  return function_object;
}

void register_overwrite_sys_primitive_kl_functions (void)
{
  register_primitive_kl_function("hash", &create_primitive_kl_function_hash);
  register_primitive_kl_function("symbol?",
                                 &create_primitive_kl_function_is_symbol);
  register_primitive_kl_function("integer?",
                                 &create_primitive_kl_function_is_integer);
  register_primitive_kl_function("boolean?",
                                 &create_primitive_kl_function_is_boolean);
  register_primitive_kl_function("variable?",
                                 &create_primitive_kl_function_is_variable);
  register_primitive_kl_function("not", &create_primitive_kl_function_not);
}

void register_overwrite_reader_primitive_kl_functions (void)
{
  register_primitive_kl_function("shen.numbyte?",
                                 &create_primitive_kl_function_is_numbyte);
  register_primitive_kl_function("shen.byte->digit",
                                 &create_primitive_kl_function_byte_to_digit);
}

void register_overwrite_prolog_primitive_kl_functions (void)
{
  register_primitive_kl_function("shen.pvar?",
                                 &create_primitive_kl_function_is_pvar);
}
