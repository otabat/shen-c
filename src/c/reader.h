#ifndef SHEN_C_READER_H
#define SHEN_C_READER_H

#include <stdbool.h>

#include "boolean.h"
#include "character.h"
#include "exception.h"
#include "kl.h"
#include "list.h"
#include "stream.h"
#include "string.h"
#include "symbol.h"

KLObject* read_string (KLObject* stream);

#endif
