#ifndef STRING_H
#define STRING_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "exception.h"
#include "kl.h"
#include "number.h"

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
  return (is_kl_string(left_object) && is_kl_string(right_object) &&
          is_string_equal(get_string(left_object), get_string(right_object)));
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

  return create_kl_string(string);
}

#endif
