#ifndef SHEN_C_STACK_H
#define SHEN_C_STACK_H

#include "kl.h"

void push_stack (Stack* stack, KLObject* object);
KLObject* pop_stack (Stack* stack);
KLObject* peek_stack (Stack* stack);

inline KLObject* get_stack_top (Stack* stack)
{
  return stack->top;
}

inline void set_stack_top (Stack* stack, KLObject* top_object)
{
  stack->top = top_object;
}

inline long get_stack_size (Stack* stack)
{
  return stack->size;
}

inline void set_stack_size (Stack* stack, long size)
{
  stack->size = size;
}

inline Stack* create_stack (void)
{
  Stack* stack = malloc(sizeof(Stack));

  set_stack_top(stack, EL);
  set_stack_size(stack, 0);

  return stack;
}

#endif
