#ifndef SHEN_C_OBJECT_H
#define SHEN_C_OBJECT_H

#include <stdbool.h>
#include <stdio.h>
#include <inttypes.h>

#include "boolean.h"
#include "exception.h"
#include "function.h"
#include "kl.h"
#include "list.h"
#include "number.h"
#include "stream.h"
#include "string.h"
#include "symbol.h"
#include "vector.h"

char* kl_list_to_string (KLObject* list_object);
char* vector_to_string (Vector* vector);
char* kl_vector_to_string (KLObject* object);
char* kl_function_to_string (KLObject* function_object);
char* kl_object_to_string (KLObject* object);
void print_kl_object (KLObject* object);
void println_kl_object (KLObject* object);
void printlnln_kl_object (KLObject* object);
bool is_kl_list_equal (KLObject* left_object, KLObject* right_object);
bool is_kl_vector_equal (KLObject* left_object, KLObject* right_object);
bool is_kl_object_equal (KLObject* left_object, KLObject* right_object);

inline Vector* kl_list_to_vector (KLObject* list_object)
{
  long size = get_kl_list_size(list_object);
  Vector* vector = create_vector(size);
  KLObject* object = list_object;

  for (long i = 0; i < size; ++i) {
    vector->objects[i] = CAR(object);
    object = CDR(object);
  }

  return vector;
}

#endif
