#ifndef SHEN_C_SYSTEM_H
#define SHEN_C_SYSTEM_H

#include <time.h>

#include "exception.h"
#include "kl.h"
#include "number.h"
#include "symbol.h"

void initialize_start_clock (void);
long get_unix_time (void);
KLObject* get_kl_number_unix_time (void);
double get_run_time (void);
KLObject* get_kl_number_run_time (void);
KLObject* get_kl_number_time (KLObject* symbol_object);

#endif
