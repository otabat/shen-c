#ifndef SHEN_C_SYSTEM_H
#define SHEN_C_SYSTEM_H

#include <time.h>

#include "exception.h"
#include "kl.h"
#include "number.h"
#include "symbol.h"

extern clock_t start_clock;

inline void initialize_start_clock (void)
{
  start_clock = clock();
}

KLObject* get_kl_number_time (KLObject* symbol_object);

#endif
