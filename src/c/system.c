#include "system.h"

static clock_t start_clock;

void initialize_start_clock (void)
{
  start_clock = clock();
}

long get_unix_time (void)
{
  return (long)time(NULL);
}

KLObject* get_kl_number_unix_time (void)
{
  KLObject* number_object = create_kl_number_l(get_unix_time());

  return number_object;
}

double get_run_time (void)
{
  return (double)(clock() - start_clock) / CLOCKS_PER_SEC;
}

KLObject* get_kl_number_run_time (void)
{
  KLObject* number_object = create_kl_number_d(get_run_time());

  return number_object;
}

KLObject* get_kl_number_time (KLObject* symbol_object)
{
  if (!is_kl_symbol(symbol_object))
    throw_kl_exception("Parameter should be a symbol");

  char* symbol = get_symbol(symbol_object);

  if (strcmp(symbol, "unix") == 0)
    return get_kl_number_unix_time();
  else if (strcmp(symbol, "run") == 0)
    return get_kl_number_run_time();

  throw_kl_exception("Parameter should be a symbol unix or run");

  return NULL;
}
