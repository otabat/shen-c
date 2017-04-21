#ifndef SHEN_C_OVERWRITE_H
#define SHEN_C_OVERWRITE_H

#include <stdbool.h>

#include "boolean.h"
#include "exception.h"
#include "hash.h"
#include "kl.h"
#include "number.h"
#include "primitive.h"
#include "vector.h"

void register_overwrite_sys_primitive_kl_functions (void);
void register_overwrite_reader_primitive_kl_functions (void);
void register_overwrite_prolog_primitive_kl_functions (void);

#endif
