#ifndef SHEN_C_CHARACTER_H
#define SHEN_C_CHARACTER_H

#include <stdbool.h>

char* get_symbol_characters(void);
bool is_left_parenthesis_character (char c);
bool is_right_parenthesis_character (char c);
bool is_double_quotation_character (char c);
bool is_plus_character (char c);
bool is_minus_character (char c);
bool is_dot_character (char c);
bool is_whitespace_character (char c);
bool is_lowercase_alphabet_character (char c);
bool is_uppercase_alphabet_character (char c);
bool is_alphabet_character (char c);
bool is_numeric_character (char c);
bool is_alphanumeric_character (char c);
bool is_non_alphanumeric_symbol_character (char c);
bool is_symbol_character (int c);

#endif
