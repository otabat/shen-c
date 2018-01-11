#include "extension.h"

static inline KLObject* primitive_function_c_nth_hd
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);
  KLObject* number_object = objects[0];
  KLObject* list_object = objects[1];
  long index = get_kl_number_number_l(number_object);

  if (index == 2)
    return CAAR(list_object);
  if (index == 3)
    return CAAAR(list_object);
  if (index == 4)
    return CAAAAR(list_object);
  if (index == 5)
    return CAAAAAR(list_object);
  if (index == 6)
    return CAAAAAAR(list_object);
  if (index == 7)
    return CAAAAAAAR(list_object);
  if (index == 8)
    return CAAAAAAAAR(list_object);
  if (index == 9)
    return CAAAAAAAAAR(list_object);
  if (index == 10)
    return CAAAAAAAAAAR(list_object);

  for (long i = index; i > 0; --i)
    list_object = CAR(list_object);

  return list_object;
}

static inline void register_primitive_kl_function_c_nth_hd (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_c_nth_hd);

  set_kl_symbol_function(get_c_nth_hd_symbol_object(), function_object);
}

static inline KLObject* primitive_function_c_nth_tl
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);
  KLObject* number_object = objects[0];
  KLObject* list_object = objects[1];
  long index = get_kl_number_number_l(number_object);

  if (index == 2)
    return CDDR(list_object);
  if (index == 3)
    return CDDDR(list_object);
  if (index == 4)
    return CDDDDR(list_object);
  if (index == 5)
    return CDDDDDR(list_object);
  if (index == 6)
    return CDDDDDDR(list_object);
  if (index == 7)
    return CDDDDDDDR(list_object);
  if (index == 8)
    return CDDDDDDDDR(list_object);
  if (index == 9)
    return CDDDDDDDDDR(list_object);
  if (index == 10)
    return CDDDDDDDDDDR(list_object);

  for (long i = index; i > 0; --i)
    list_object = CDR(list_object);

  return list_object;
}

static inline void register_primitive_kl_function_c_nth_tl (void)
{
  KLObject* function_object =
    create_primitive_kl_function(2, &primitive_function_c_nth_tl);

  set_kl_symbol_function(get_c_nth_tl_symbol_object(), function_object);
}

static inline KLObject* primitive_function_c_flush
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject** objects =
    get_kl_function_arguments_with_count_check(function_object, arguments);
  KLObject* stream_object = objects[0];

  if (!is_kl_stream(stream_object))
    throw_kl_exception("Non-stream argument passed to c.flush");

  FILE* file = get_kl_stream_file(stream_object);

  if (fflush(file) != 0)
    throw_kl_exception("Failed to flush stream");

  return get_empty_kl_list();
}

static inline void register_primitive_kl_function_c_flush (void)
{
  KLObject* function_object =
    create_primitive_kl_function(1, &primitive_function_c_flush);

  set_kl_symbol_function(get_c_flush_symbol_object(), function_object);
}

void register_extension_primitive_kl_functions (void)
{
  register_primitive_kl_function_c_nth_hd();
  register_primitive_kl_function_c_nth_tl();
  register_primitive_kl_function_c_flush();
}
