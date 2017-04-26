#ifndef SHEN_C_EXTENSION_H
#define SHEN_C_EXTENSION_H

#include <stdlib.h>

#include "kl.h"
#include "object.h"
#include "primitive.h"

extern KLObject* println_symbol_object;
extern KLObject* quit_symbol_object;
extern KLObject* loop_symbol_object;
extern KLObject* recur_symbol_object;
extern KLObject* quote_symbol_object;

inline KLObject* get_println_symbol_object (void) { return println_symbol_object; }
inline KLObject* get_quit_symbol_object (void) { return quit_symbol_object; }
inline KLObject* get_loop_symbol_object (void) { return loop_symbol_object; }
inline KLObject* get_recur_symbol_object (void) { return recur_symbol_object; }
inline KLObject* get_quote_symbol_object (void) { return quote_symbol_object; }

void register_extension_primitive_kl_functions (void);

#endif
