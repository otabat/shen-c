#ifndef SHEN_C_STACK_H
#define SHEN_C_STACK_H

#include "kl.h"

KLObject* get_stack_top (Stack* stack);
void set_stack_top (Stack* stack, KLObject* top_object);
size_t get_stack_size (Stack* stack);
void set_stack_size (Stack* stack, size_t size);
Stack* create_stack (void);
void push_stack (Stack* stack, KLObject* object);
KLObject* pop_stack (Stack* stack);
KLObject* peek_stack (Stack* stack);

#endif
