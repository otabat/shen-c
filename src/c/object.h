#ifndef SHEN_C_OBJECT_H
#define SHEN_C_OBJECT_H

#include <stdbool.h>
#include <stdio.h>
#include <inttypes.h>

#include "khash.h"

#include "boolean.h"
#include "dictionary.h"
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

inline KLObject* get_dictionary_value (Dictionary* dictionary,
                                       KLObject* key_object)
{
  khash_t(StringPairTable)* table = get_dictionary_table(dictionary);
  khiter_t hash_iterator = kh_get(StringPairTable, table,
                                  kl_object_to_string(key_object));
  bool is_key_not_found = hash_iterator == kh_end(table);

  if (is_key_not_found || kh_exist(table, hash_iterator) == 0)
    return NULL;

  return get_pair_cdr(kh_value(table, hash_iterator));
}

inline void set_dictionary_value (Dictionary* dictionary, KLObject* key_object,
                                  KLObject* value_object)
{
  khash_t(StringPairTable)* table = get_dictionary_table(dictionary);
  int put_result;
  khiter_t hash_iterator = kh_put(StringPairTable, table,
                                  kl_object_to_string(key_object), &put_result);

  if (put_result == -1)
    throw_kl_exception("Failed to set a value to a dictionary");
  else if (put_result == 0) {
    Pair* pair = kh_value(table, hash_iterator);

    set_pair_cdr(pair, value_object);
  } else {
    Pair* pair = create_pair(key_object, value_object);

    kh_value(table, hash_iterator) = pair;
  }
}

inline KLObject* get_kl_dictionary_value (KLObject* dictionary_object,
                                          KLObject* key_object)
{
  return get_dictionary_value(get_dictionary(dictionary_object), key_object);
}

inline KLObject* set_kl_dictionary_value (KLObject* dictionary_object,
                                          KLObject* key_object,
                                          KLObject* value_object)
{
  set_dictionary_value(get_dictionary(dictionary_object), key_object,
                       value_object);

  return value_object;
}

inline void delete_dictionary_key (Dictionary* dictionary, KLObject* key_object)
{
  khash_t(StringPairTable)* table = get_dictionary_table(dictionary);
  khiter_t hash_iterator = kh_get(StringPairTable, table,
                                  kl_object_to_string(key_object));

  kh_del(StringPairTable, table, hash_iterator);
}

inline KLObject* delete_kl_dictionary_key (KLObject* dictionary_object,
                                           KLObject* key_object)
{
  delete_dictionary_key(get_dictionary(dictionary_object), key_object);

  return key_object;
}

inline char* kl_dictionary_to_string (KLObject* dictionary_object)
{
  return "(dict ...)";
}

#endif
