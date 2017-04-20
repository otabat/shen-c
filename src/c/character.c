#include "character.h"

char* symbol_characters =
  "=-*/+_?$!@~.><&%\'#`;:{}"
  "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
  "012356789";

extern char* get_symbol_characters(void);
extern bool is_left_parenthesis_character (char c);
extern bool is_right_parenthesis_character (char c);
extern bool is_double_quotation_character (char c);
extern bool is_plus_character (char c);
extern bool is_minus_character (char c);
extern bool is_dot_character (char c);
extern bool is_whitespace_character (char c);
extern bool is_lowercase_alphabet_character (char c);
extern bool is_uppercase_alphabet_character (char c);
extern bool is_alphabet_character (char c);
extern bool is_numeric_character (char c);
extern bool is_alphanumeric_character (char c);
extern bool is_non_alphanumeric_symbol_character (char c);
extern bool is_symbol_character (int c);
