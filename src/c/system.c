#include "system.h"

KLObject* unix_symbol_object;
KLObject* run_symbol_object;
clock_t start_clock;

extern KLObject* get_unix_symbol_object (void);
extern KLObject* get_run_symbol_object (void);

extern void initialize_start_clock (void);

static inline clock_t get_start_clock (void)
{
  return start_clock;
}

static inline long get_unix_time (void)
{
  return (long)time(NULL);
}

static inline KLObject* get_kl_number_unix_time (void)
{
  KLObject* number_object = create_kl_number_l(get_unix_time());

  return number_object;
}

static inline double get_run_time (void)
{
  return (double)(clock() - get_start_clock()) / CLOCKS_PER_SEC;
}

static inline KLObject* get_kl_number_run_time (void)
{
  KLObject* number_object = create_kl_number_d(get_run_time());

  return number_object;
}

static inline void initialize_unix_symbol_object (void)
{
  unix_symbol_object = create_kl_symbol("unix");
}

static inline void register_unix_symbol_object ()
{
  initialize_unix_symbol_object();
  extend_symbol_name_table("unix", get_unix_symbol_object());
}

static inline void initialize_run_symbol_object (void)
{
  run_symbol_object = create_kl_symbol("run");
}

static inline void register_run_symbol_object ()
{
  initialize_run_symbol_object();
  extend_symbol_name_table("run", get_run_symbol_object());
}

void register_system_symbol_objects (void)
{
  register_unix_symbol_object();
  register_run_symbol_object();
}

KLObject* get_kl_number_time (KLObject* symbol_object)
{
  if (!is_kl_symbol(symbol_object))
    throw_kl_exception("Parameter should be a symbol");

  if (symbol_object == get_unix_symbol_object())
    return get_kl_number_unix_time();
  else if (symbol_object == get_run_symbol_object())
    return get_kl_number_run_time();

  throw_kl_exception("Parameter should be a symbol unix or run");

  return NULL;
}
