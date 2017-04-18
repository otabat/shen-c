#ifndef STRING_H
#define STRING_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "exception.h"
#include "kl.h"
#include "number.h"

char* get_string (KLObject* string_object);
void set_string (KLObject* string_object, char* string);
KLObject* create_kl_string (char *string);
bool is_kl_string (KLObject* object);
char* string_to_double_quoted_string (char* string);
char* get_double_quoted_string (KLObject* string_object);
char* get_position_string (char* string, long index);
KLObject* get_position_kl_string (KLObject* string_object,
                                  KLObject* number_object);
char* get_tail_string (char* string);
KLObject* get_tail_kl_string (KLObject* string_object);
char* concatenate_string (char* left_string, char* right_string);
KLObject* concatenate_kl_string (KLObject* left_string_object,
                                 KLObject* right_string_object);
char* code_point_to_string (long code_point);
KLObject* kl_number_code_point_to_kl_string (KLObject* number_object);
long string_to_code_point (char* string);
KLObject* kl_string_to_kl_number_code_point (KLObject* string_object);
bool is_string_equal (char* left_string, char* right_string);
bool is_kl_string_equal (KLObject* left_object, KLObject* right_object);
char* append_string (char* string_destination,
                     size_t* string_destination_allocation_size_ref,
                     char* string_source);
char* append_character_to_string (char* string_destination,
                                  size_t* string_destination_allocation_size_ref,
                                  char char_source);
char* long_to_string (long x);
char* double_to_string (double x);
char* kl_number_to_string (KLObject* number_object);

#endif
