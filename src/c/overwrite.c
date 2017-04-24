#include "overwrite.h"

KLObject* hash_symbol_object;
KLObject* is_symbol_symbol_object;
KLObject* is_integer_symbol_object;
KLObject* is_boolean_symbol_object;
KLObject* is_variable_symbol_object;
KLObject* not_symbol_object;
KLObject* shen_is_numbyte_symbol_object;
KLObject* shen_byte_to_digit_symbol_object;
KLObject* shen_pvar_symbol_object;
KLObject* shen_is_pvar_symbol_object;

extern KLObject* get_hash_symbol_object (void);
extern KLObject* get_is_symbol_symbol_object (void);
extern KLObject* get_is_integer_symbol_object (void);
extern KLObject* get_is_boolean_symbol_object (void);
extern KLObject* get_is_variable_symbol_object (void);
extern KLObject* get_not_symbol_object (void);
extern KLObject* get_shen_is_numbyte_symbol_object (void);
extern KLObject* get_shen_byte_to_digit_symbol_object (void);
extern KLObject* get_shen_is_pvar_symbol_object (void);

static inline void initialize_hash_symbol_object (void)
{
  hash_symbol_object = create_kl_symbol("hash");
}

static inline void register_hash_symbol_object (void)
{
  initialize_hash_symbol_object();
  extend_symbol_name_table("hash", get_hash_symbol_object());
}

static inline KLObject* primitive_function_hash (KLObject* function_object,
                                                 Vector* arguments)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  return kl_object_bounded_hash(objects[0], objects[1]);
}

static inline void register_primitive_kl_function_hash (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_hash);

  set_kl_symbol_function(get_hash_symbol_object(), function_object);
}

static inline void initialize_is_symbol_symbol_object (void)
{
  is_symbol_symbol_object = create_kl_symbol("symbol?");
}

static inline void register_is_symbol_symbol_object (void)
{
  initialize_is_symbol_symbol_object();
  extend_symbol_name_table("symbol?", get_is_symbol_symbol_object());
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

static inline void register_primitive_kl_function_is_symbol (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_is_symbol);

  set_kl_symbol_function(get_is_symbol_symbol_object(), function_object);
}

static inline void initialize_is_boolean_symbol_object (void)
{
  is_boolean_symbol_object = create_kl_symbol("boolean?");
}

static inline void register_is_boolean_symbol_object (void)
{
  initialize_is_boolean_symbol_object();
  extend_symbol_name_table("boolean?", get_is_boolean_symbol_object());
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

static inline void register_primitive_kl_function_is_boolean (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_is_boolean);

  set_kl_symbol_function(get_is_boolean_symbol_object(), function_object);
}

static inline void initialize_is_integer_symbol_object (void)
{
  is_integer_symbol_object = create_kl_symbol("integer?");
}

static inline void register_is_integer_symbol_object (void)
{
  initialize_is_integer_symbol_object();
  extend_symbol_name_table("integer?", get_is_integer_symbol_object());
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

static inline void register_primitive_kl_function_is_integer (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_is_integer);

  set_kl_symbol_function(get_is_integer_symbol_object(), function_object);
}

static inline void initialize_is_variable_symbol_object (void)
{
  is_variable_symbol_object = create_kl_symbol("variable?");
}

static inline void register_is_variable_symbol_object (void)
{
  initialize_is_variable_symbol_object();
  extend_symbol_name_table("variable?", get_is_variable_symbol_object());
}

static inline KLObject* primitive_function_is_variable (KLObject* function_object,
                                                        Vector* arguments)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  if (is_kl_symbol(objects[0])) {
    char* symbol_name = get_kl_symbol_name(objects[0]);

    if (is_uppercase_alphabet_character(symbol_name[0]))
      return get_true_boolean_object();

    return get_false_boolean_object();
  }

  return get_false_boolean_object();
}

static inline void register_primitive_kl_function_is_variable (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_is_variable);

  set_kl_symbol_function(get_is_variable_symbol_object(), function_object);
}

static inline void initialize_not_symbol_object (void)
{
  not_symbol_object = create_kl_symbol("not");
}

static inline void register_not_symbol_object (void)
{
  initialize_not_symbol_object();
  extend_symbol_name_table("not", get_not_symbol_object());
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

static inline void register_primitive_kl_function_not (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_not);

  set_kl_symbol_function(get_not_symbol_object(), function_object);
}

static inline void initialize_shen_is_numbyte_symbol_object (void)
{
  shen_is_numbyte_symbol_object = create_kl_symbol("shen.numbyte?");
}

static inline void register_shen_is_numbyte_symbol_object (void)
{
  initialize_shen_is_numbyte_symbol_object();
  extend_symbol_name_table("shen.numbyte?", get_shen_is_numbyte_symbol_object());
}

static inline KLObject* primitive_function_shen_is_numbyte
(KLObject* function_object, Vector* arguments)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);
  long x = get_kl_number_number_l(objects[0]);

  if ((x >= 48 && x <= 57))
    return get_true_boolean_object();

  return get_false_boolean_object();
}

static inline void register_primitive_kl_function_shen_is_numbyte (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_shen_is_numbyte);

  set_kl_symbol_function(get_shen_is_numbyte_symbol_object(), function_object);
}

static inline void initialize_shen_byte_to_digit_symbol_object (void)
{
  shen_byte_to_digit_symbol_object = create_kl_symbol("shen.byte->digit");
}

static inline void register_shen_byte_to_digit_symbol_object (void)
{
  initialize_shen_byte_to_digit_symbol_object();
  extend_symbol_name_table("shen.byte->digit",
                           get_shen_byte_to_digit_symbol_object());
}

static inline KLObject* primitive_function_shen_byte_to_digit
(KLObject* function_object, Vector* arguments)
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

static inline void register_primitive_kl_function_shen_byte_to_digit (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_shen_byte_to_digit);

  set_kl_symbol_function(get_shen_byte_to_digit_symbol_object(), function_object);
}

static inline void initialize_shen_pvar_symbol_object (void)
{
  shen_pvar_symbol_object = create_kl_symbol("shen.pvar");
}

static inline void register_shen_pvar_symbol_object (void)
{
  initialize_shen_pvar_symbol_object();
  extend_symbol_name_table("shen.pvar", get_shen_pvar_symbol_object());
}

static inline void initialize_shen_is_pvar_symbol_object (void)
{
  shen_is_pvar_symbol_object = create_kl_symbol("shen.pvar?");
}

static inline void register_shen_is_pvar_symbol_object (void)
{
  initialize_shen_is_pvar_symbol_object();
  extend_symbol_name_table("shen.pvar?", get_shen_is_pvar_symbol_object());
}

static inline KLObject* primitive_function_shen_is_pvar
(KLObject* function_object, Vector* arguments)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);

  if (is_kl_vector(objects[0])) {
    Vector* vector = get_vector(objects[0]);
    KLObject* object = get_vector_element(vector, 0);

    if (object == get_shen_pvar_symbol_object())
      return get_true_boolean_object();

    return get_false_boolean_object();
  }

  return get_false_boolean_object();
}

static inline void register_primitive_kl_function_shen_is_pvar (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_shen_is_pvar);

  set_kl_symbol_function(get_shen_is_pvar_symbol_object(), function_object);
}

void register_overwrite_symbol_objects (void)
{
  register_hash_symbol_object();
  register_is_symbol_symbol_object();
  register_is_boolean_symbol_object();
  register_is_integer_symbol_object();
  register_is_variable_symbol_object();
  register_not_symbol_object();
  register_shen_is_numbyte_symbol_object();
  register_shen_byte_to_digit_symbol_object();
  register_shen_pvar_symbol_object();
  register_shen_is_pvar_symbol_object();
}

void register_overwrite_sys_primitive_kl_functions (void)
{
  register_primitive_kl_function_hash();
  register_primitive_kl_function_is_symbol();
  register_primitive_kl_function_is_integer();
  register_primitive_kl_function_is_boolean();
  register_primitive_kl_function_is_variable();
  register_primitive_kl_function_not();
}

void register_overwrite_reader_primitive_kl_functions (void)
{
  register_primitive_kl_function_shen_is_numbyte();
  register_primitive_kl_function_shen_byte_to_digit();
}

void register_overwrite_prolog_primitive_kl_functions (void)
{
  register_primitive_kl_function_shen_is_pvar();
}
