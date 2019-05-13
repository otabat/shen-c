#ifndef SHEN_C_STRING_H
#define SHEN_C_STRING_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "exception.h"
#include "kl.h"
#include "number.h"

extern khash_t(StringTable)* string_table;

extern KLObject* empty_string_object;
extern KLObject* true_string_object;
extern KLObject* false_string_object;
extern KLObject* three_dots_string_object;

void register_string_objects (void);

char* string_to_double_quoted_string (char* string);
char* get_double_quoted_string (KLObject* string_object);
char* get_tail_string (char* string);
KLObject* get_tail_kl_string (KLObject* string_object);
char* concatenate_string (char* left_string, char* right_string);
KLObject* concatenate_kl_string (KLObject* left_string_object,
                                 KLObject* right_string_object);
char* code_point_to_string (long code_point);
KLObject* kl_number_code_point_to_kl_string (KLObject* number_object);
long string_to_code_point (char* string);
KLObject* kl_string_to_kl_number_code_point (KLObject* string_object);
char* append_string (char* string_destination,
                     size_t* string_destination_allocation_size_ref,
                     char* string_source);
char* append_character_to_string (char* string_destination,
                                  size_t* string_destination_allocation_size_ref,
                                  char char_source);
char* long_to_string (long x);
char* double_to_string (double x);
char* kl_number_to_string (KLObject* number_object);

inline KLObject* get_empty_string_object (void)
{
  return empty_string_object;
}

inline KLObject* get_true_string_object (void)
{
  return true_string_object;
}

inline KLObject* get_false_string_object (void)
{
  return false_string_object;
}

inline KLObject* get_three_dots_string_object (void)
{
  return three_dots_string_object;
}

inline char* get_string (KLObject* string_object)
{
  return string_object->value.string;
}

inline void set_string (KLObject* string_object, char* string)
{
  string_object->value.string = string;
}

inline KLObject* create_kl_string (char *string)
{
  KLObject* string_object = create_kl_object(KL_TYPE_STRING);

  set_string(string_object, string);

  return string_object;
}

inline khash_t(StringTable)* get_string_table (void)
{
  return string_table;
}

inline void initialize_string_table (void)
{
  string_table = kh_init(StringTable);
}

inline KLObject* lookup_string_table (char* string)
{
  khash_t(StringTable)* table = get_string_table();
  khiter_t hash_iterator = kh_get(StringTable, table, string);
  bool is_key_not_found = hash_iterator == kh_end(table);

  if (is_key_not_found || kh_exist(table, hash_iterator) == 0)
    return NULL;

  return kh_value(table, hash_iterator);
}

inline void extend_string_table (char* string, KLObject* object)
{
  khash_t(StringTable)* table = get_string_table();
  int put_result;
  khiter_t hash_iterator = kh_put(StringTable, table, string, &put_result);

  if (put_result == -1)
    throw_kl_exception("Failed to extend string table");

  kh_value(table, hash_iterator) = object;
}

inline KLObject* create_kl_string_with_intern (char* string)
{
  KLObject* string_object = lookup_string_table(string);

  if (is_null(string_object)) {
    string_object = create_kl_string(string);
    extend_string_table(string, string_object);
  }

  return string_object;
}

inline bool is_kl_string (KLObject* object)
{
  return get_kl_object_type(object) == KL_TYPE_STRING;
}

inline bool is_string_equal (char* left_string, char* right_string)
{
  return (strcmp(left_string, right_string) == 0);
}

inline bool is_kl_string_equal (KLObject* left_object, KLObject* right_object)
{
  return left_object == right_object;
}

inline char* get_position_string (char* string, long index)
{
  if (index >= (long)strlen(string) || index < 0)
    throw_kl_exception("Invalid index");

  char *position_string = malloc(2);

  position_string[0] = string[index];
  position_string[1] = '\0';

  return position_string;
}

inline KLObject* get_position_kl_string (KLObject* string_object,
                                  KLObject* number_object)
{
  char* string = get_position_string(get_string(string_object),
                                     get_kl_number_number_l(number_object));

  return create_kl_string_with_intern(string);
}

#endif
