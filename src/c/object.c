#include "object.h"

static size_t kl_list_to_string_allocation_size = 10;
static size_t vector_to_string_allocation_size = 10;

extern Vector* kl_list_to_vector (KLObject* list_object);

static inline size_t get_kl_list_to_string_allocation_size ()
{
  return kl_list_to_string_allocation_size;
}

static inline size_t get_vector_to_string_allocation_size ()
{
  return vector_to_string_allocation_size;
}

static char* kl_list_to_string_helper
(KLObject* object, char* object_string, size_t object_string_allocation_size,
 bool is_list_head)
{
  if (is_empty_kl_list(object)) {
    if (is_list_head)
      object_string = append_string(object_string,
                                    &object_string_allocation_size,
                                    "[]");
    else
      object_string = append_string(object_string,
                                    &object_string_allocation_size,
                                    "]");
  } else if (is_non_empty_kl_list(object)) {
    if (is_list_head)
      object_string = append_string(object_string,
                                    &object_string_allocation_size,
                                    "[");
    
    KLObject* car_object = get_head_kl_list(object);
    KLObject* cdr_object = get_tail_kl_list(object); 
    
    if (is_kl_list(car_object))
      object_string = kl_list_to_string_helper(car_object, object_string,
                                               object_string_allocation_size,
                                               true);
    else
      object_string = kl_list_to_string_helper(car_object, object_string,
                                               object_string_allocation_size,
                                               false);
    
    if (!is_empty_kl_list(cdr_object)) {
      if (is_kl_list(cdr_object))
        object_string = append_string(object_string,
                                      &object_string_allocation_size, " ");
      else
        object_string = append_string(object_string,
                                      &object_string_allocation_size, " | ");
    }
    
    object_string = kl_list_to_string_helper(cdr_object, object_string,
                                             object_string_allocation_size, false);

    if (!is_kl_list(cdr_object))
      object_string = append_string(object_string,
                                    &object_string_allocation_size,
                                    "]");
  } else
    object_string = append_string(object_string,
                                  &object_string_allocation_size,
                                  kl_object_to_string(object)); 

  return object_string;
}

char* kl_list_to_string (KLObject* list_object)
{
  size_t list_object_string_allocation_size =
    get_kl_list_to_string_allocation_size();
  char* list_object_string = malloc(list_object_string_allocation_size);

  return kl_list_to_string_helper(list_object, list_object_string,
                                  list_object_string_allocation_size,
                                  true);
}

char* vector_to_string (Vector* vector)
{
  size_t vector_size = get_vector_size(vector);
  KLObject** objects = get_vector_objects(vector);
  size_t vector_string_allocation_size = get_vector_to_string_allocation_size();
  char* vector_string = malloc(vector_string_allocation_size);

  for (size_t i = 0; i < vector_size; ++i) {
    if (i == 0)
      vector_string =
        append_string(vector_string, &vector_string_allocation_size, "<<");

    vector_string = append_string(vector_string,
                                  &vector_string_allocation_size,
                                  kl_object_to_string(objects[i]));

    if (i == vector_size - 1)
      vector_string =
        append_string(vector_string, &vector_string_allocation_size, ">>");
    else
      vector_string = 
        append_string(vector_string, &vector_string_allocation_size, " ");
  }

  return vector_string;
}

char* kl_vector_to_string (KLObject* vector_object)
{
  return vector_to_string (get_vector(vector_object));
}

char* kl_function_to_string (KLObject* function_object)
{
  char* function_object_string = NULL;
  char length_string[1];
  int function_object_string_length;

  if (is_closure_kl_function(function_object)) {
    Closure* closure = get_kl_function_closure(function_object);
    char* parameter_object_string =
      kl_object_to_string(get_closure_parameter(closure));
    char* body_object_string = kl_object_to_string(get_closure_body(closure));

    function_object_string_length =
      snprintf(length_string, 1,
               "#<Closure {0x%016" PRIxPTR "} [lambda %s %s]>",
               (uintptr_t)function_object,
               parameter_object_string,
               body_object_string);
    function_object_string = malloc((size_t)function_object_string_length + 1);
    sprintf(function_object_string,
            "#<Closure {0x%016" PRIxPTR "} [lambda %s %s]>",
            (uintptr_t)function_object,
            parameter_object_string,
            body_object_string);
  } else if (is_primitive_kl_function(function_object)) {
    function_object_string_length =
      snprintf(length_string, 1, "#<PrimitiveFunction {0x%016" PRIxPTR "}>",
               (uintptr_t)function_object);
    function_object_string = malloc((size_t)function_object_string_length + 1);
    sprintf(function_object_string, "#<PrimitiveFunction {0x%016" PRIxPTR "}>",
            (uintptr_t)function_object);
  } else if (is_user_kl_function(function_object)) {
    UserFunction* user_function = get_kl_function_user_function(function_object);
    Vector* parameters = get_user_function_parameters(user_function);
    size_t parameter_size =
      (is_null(parameters)) ? 0 : get_vector_size(parameters);
    KLObject* body_object = get_user_function_body(user_function);
    char* body_object_string = kl_object_to_string(body_object);
    char* parameter_object_string = "";

    if (parameter_size > 0) {
      KLObject** objects = get_vector_objects(parameters);

      for (size_t i = 0; i < parameter_size ;++i) {
        if (i != 0)
          parameter_object_string =
            concatenate_string(parameter_object_string, " ");
        
        parameter_object_string =
          concatenate_string(parameter_object_string,
                             kl_object_to_string(objects[i]));
      }
    }

    function_object_string_length =
      snprintf(length_string, 1,
               "#<Function {0x%016" PRIxPTR "} [function [%s] %s]>",
               (uintptr_t)function_object,
               parameter_object_string,
               body_object_string);
    function_object_string = malloc((size_t)function_object_string_length + 1); 
    sprintf(function_object_string,
            "#<Function {0x%016" PRIxPTR "} [function [%s] %s]>",
            (uintptr_t)function_object,
            parameter_object_string,
            body_object_string);
  } else
    throw_kl_exception("Unknown type of function");

  return function_object_string;
}

char* kl_object_to_string (KLObject* object)
{
  if (is_kl_symbol(object))
    return get_kl_symbol_name(object);
  else if (is_kl_string(object))
    return get_double_quoted_string(object);
  else if (is_kl_number(object))
    return kl_number_to_string(object);
  else if (is_kl_boolean(object))
    return kl_boolean_to_string(object);
  else if (is_kl_function(object))
    return kl_function_to_string(object);
  else if (is_kl_stream(object))
    return kl_stream_to_string(object);
  else if (is_kl_exception(object))
    return kl_exception_to_string(object);
  else if (is_kl_list(object))
    return kl_list_to_string(object);
  else if (is_kl_vector(object))
    return kl_vector_to_string(object);

  throw_kl_exception("Unknown type of object");

  return NULL;
}

void print_kl_object (KLObject* object)
{
  printf("%s", kl_object_to_string(object));
}

void println_kl_object (KLObject* object)
{
  printf("%s\n", kl_object_to_string(object));
}

void printlnln_kl_object (KLObject* object)
{
  printf("%s\n\n", kl_object_to_string(object));
}

bool is_kl_list_equal (KLObject* left_object, KLObject* right_object)
{
  KLObject* lo = left_object;
  KLObject* ro = right_object;

  if (is_empty_kl_list(lo) && is_empty_kl_list(ro))
    return true;
  else if (is_non_empty_kl_list(lo) && is_non_empty_kl_list(ro)) {
    KLObject* car_lo = get_head_kl_list(lo);
    KLObject* car_ro = get_head_kl_list(ro);
    
    if (is_kl_object_equal(car_lo, car_ro)) {
      KLObject* cdr_lo = get_tail_kl_list(lo);
      KLObject* cdr_ro = get_tail_kl_list(ro);
      
      if (is_kl_list(cdr_lo))
        return is_kl_list_equal(cdr_lo, cdr_ro);

      return is_kl_object_equal(cdr_lo, cdr_ro);
    }
    
    return false;
  } 
  
  return false;
}

bool is_kl_vector_equal (KLObject* left_object, KLObject* right_object)
{
  if (!is_kl_vector(left_object) || !is_kl_vector(right_object))
    return false;

  size_t left_object_size = get_kl_vector_size(left_object);
  size_t right_object_size = get_kl_vector_size(right_object);

  if (left_object_size != right_object_size)
    return false;

  KLObject** left_object_objects = get_kl_vector_objects(left_object);
  KLObject** right_object_objects = get_kl_vector_objects(right_object);

  for (size_t i = 0; i < left_object_size; ++i) {
    if (!is_kl_object_equal(left_object_objects[i], right_object_objects[i]))
      return false;
  }

  return true;
}

bool is_kl_object_equal (KLObject* left_object, KLObject* right_object)
{
  if (is_kl_symbol(left_object))
    return is_kl_symbol_equal(left_object, right_object);
  else if (is_kl_string(left_object))
    return is_kl_string_equal(left_object, right_object);
  else if (is_kl_number(left_object))
    return is_kl_number_equal(left_object, right_object);
  else if (is_kl_boolean(left_object))
    return is_kl_boolean_equal(left_object, right_object);
  else if (is_kl_function(left_object))
    return is_kl_function_equal(left_object, right_object);
  else if (is_kl_stream(left_object))
    return is_kl_stream_equal(left_object, right_object);
  else if (is_kl_exception(left_object))
    return is_kl_exception_equal(left_object, right_object);
  else if (is_kl_list(left_object))
    return is_kl_list_equal(left_object, right_object);
  else if (is_kl_vector(left_object))
    return is_kl_vector_equal(left_object, right_object);
  
  return false;
}
