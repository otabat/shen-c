#ifndef SHEN_C_EXTENSION_H
#define SHEN_C_EXTENSION_H

#include <stdio.h>
#include <stdlib.h>

#include "exception.h"
#include "kl.h"
#include "list.h"
#include "object.h"
#include "primitive.h"
#include "stream.h"
#include "symbol_pool.h"

void register_extension_primitive_kl_functions (void);

#endif
