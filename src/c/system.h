#ifndef SHEN_C_SYSTEM_H
#define SHEN_C_SYSTEM_H

#include <time.h>

#include "exception.h"
#include "kl.h"
#include "number.h"
#include "symbol.h"

extern KLObject* unix_symbol_object;
extern KLObject* run_symbol_object;
extern clock_t start_clock;

KLObject* get_kl_number_time (KLObject* symbol_object);
void register_system_symbol_objects (void);

inline KLObject* get_unix_symbol_object (void) { return unix_symbol_object; }
inline KLObject* get_run_symbol_object (void) { return run_symbol_object; }

inline void initialize_start_clock (void)
{
  start_clock = clock();
}

#endif
