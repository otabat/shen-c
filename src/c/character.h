#ifndef SHEN_C_CHARACTER_H
#define SHEN_C_CHARACTER_H

#include <stdbool.h>

extern char* symbol_characters;

inline char* get_symbol_characters(void)
{
  return symbol_characters;
}

inline bool is_left_parenthesis_character (char c)
{
  return c == '(';
}

inline bool is_right_parenthesis_character (char c)
{
  return c == ')';
}

inline bool is_double_quotation_character (char c)
{
  return c == '"';
}

inline bool is_plus_character (char c)
{
  return c == '+';
}

inline bool is_minus_character (char c)
{
  return c == '-';
}

inline bool is_dot_character (char c)
{
  return c == '.';
}

inline bool is_whitespace_character (char c)
{
  return (c == ' ' || c == '\t' || c == '\n' || c == '\r' ||
          c == '\f' || c == '\b');
}

inline bool is_lowercase_alphabet_character (char c)
{
  return (c == 'a' || c == 'b' || c == 'c' || c == 'd' || c == 'e' || c == 'f' ||
          c == 'g' || c == 'h' || c == 'i' || c == 'j' || c == 'k' || c == 'l' ||
          c == 'm' || c == 'n' || c == 'o' || c == 'p' || c == 'q' || c == 'r' ||
          c == 's' || c == 't' || c == 'u' || c == 'v' || c == 'w' || c == 'x' ||
          c == 'y' || c == 'z');
}

inline bool is_uppercase_alphabet_character (char c)
{
  return (c == 'A' || c == 'B' || c == 'C' || c == 'D' || c == 'E' || c == 'F' ||
          c == 'G' || c == 'H' || c == 'I' || c == 'J' || c == 'K' || c == 'L' ||
          c == 'M' || c == 'N' || c == 'O' || c == 'P' || c == 'Q' || c == 'R' ||
          c == 'S' || c == 'T' || c == 'U' || c == 'V' || c == 'W' || c == 'X' ||
          c == 'Y' || c == 'Z');
}

inline bool is_alphabet_character (char c)
{
  return (is_lowercase_alphabet_character(c) ||
          is_uppercase_alphabet_character (c));
}

inline bool is_numeric_character (char c)
{
  return (c == '0' || c == '1' || c == '2' || c == '3' || c == '4' ||
          c == '5' || c == '6' || c == '7' || c == '8' || c == '9');
}

inline bool is_alphanumeric_character (char c)
{
  return is_alphabet_character(c) || is_numeric_character(c);
}

inline bool is_non_alphanumeric_symbol_character (char c)
{
  return (c == '=' || c == '+' || c == '-' || c == '*' || c == '/' || c == '_' ||
          c == '?' || c == '$' || c == '!' || c == '@' || c == '~' || c == '.' ||
          c == '>' || c == '<' || c == '&' || c == '%' || c == '#' || c == '`' ||
          c == '\'' || c == ';' || c == ':' || c == '{' || c == '}');
}

inline bool is_symbol_character (int c)
{
  return (is_alphabet_character((char)c) || is_numeric_character((char)c) ||
          is_non_alphanumeric_symbol_character((char)c));
}

#endif
