#include "symbol.h"

static unsigned long auto_increment_symbol_id = 0;
static char* auto_increment_symbol_prefix = "G__";

static inline unsigned long get_auto_increment_symbol_id ()
{
  return auto_increment_symbol_id;
}

static inline unsigned long pre_increment_auto_increment_symbol_id ()
{
  return ++auto_increment_symbol_id;
}

static inline char* get_auto_increment_symbol_prefix ()
{
  return auto_increment_symbol_prefix;
}

char* get_symbol (KLObject* symbol_object)
{
  return symbol_object->value.symbol;
}

void set_symbol (KLObject* symbol_object, char* symbol)
{
  symbol_object->value.symbol = symbol;
}

KLObject* create_kl_symbol (char* symbol)
{
  KLObject* symbol_object = create_kl_object(KL_TYPE_SYMBOL);

  set_symbol(symbol_object, symbol);
  
  return symbol_object;
}

static inline char* create_auto_increment_symbol (void)
{
  pre_increment_auto_increment_symbol_id();

  size_t symbol_allocation_size =
    count_unsigned_digits_length(get_auto_increment_symbol_id()) + 1;
  char* symbol = malloc(symbol_allocation_size);

  sprintf(symbol, "%s%zu", get_auto_increment_symbol_prefix(),
          get_auto_increment_symbol_id());

  return symbol;
}

KLObject* create_auto_increment_kl_symbol (void)
{
  return create_kl_symbol(create_auto_increment_symbol());
}

bool is_kl_symbol (KLObject* object)
{
  return get_kl_object_type(object) == KL_TYPE_SYMBOL;
}

KLObject* kl_string_to_kl_symbol (KLObject* string_object)
{
  char* string = get_string(string_object);
  char* symbol = malloc(strlen(string) + 1);

  strcpy(symbol, string);

  return create_kl_symbol(symbol);
}

KLObject* kl_string_to_kl_symbol_or_kl_boolean (KLObject* string_object)
{
  if (!is_kl_string(string_object))
    throw_kl_exception("Should be a string object");

  char* string = get_string(string_object);

  if (strcmp(string, "true") == 0)
    return create_kl_boolean(true);
  else if (strcmp(string, "false") == 0)
    return create_kl_boolean(false);

  return kl_string_to_kl_symbol(string_object);
}

bool is_symbol_equal (char* left_symbol, char* right_symbol)
{
  return strcmp(left_symbol, right_symbol) == 0;
}

bool is_kl_symbol_equal (KLObject* left_object, KLObject* right_object)
{
  return (is_kl_symbol(left_object) && is_kl_symbol(right_object) &&
          is_symbol_equal(get_symbol(left_object), get_symbol(right_object)));
}
