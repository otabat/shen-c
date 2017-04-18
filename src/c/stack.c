#include "stack.h"

KLObject* get_stack_top (Stack* stack)
{
  return stack->top;
}

void set_stack_top (Stack* stack, KLObject* top_object)
{
  stack->top = top_object;
}

size_t get_stack_size (Stack* stack)
{
  return stack->size;
}

void set_stack_size (Stack* stack, size_t size)
{
  stack->size = size;
}

Stack* create_stack (void)
{
  Stack* stack = malloc(sizeof(Stack));

  set_stack_top(stack, get_empty_kl_list());
  set_stack_size(stack, 0);

  return stack;
}

void push_stack (Stack* stack, KLObject* object)
{
  KLObject* top_object = get_stack_top(stack);
  KLObject* new_top_object = create_kl_object(KL_TYPE_LIST);
  Pair* pair = create_pair(object, top_object);
  size_t new_stack_size = get_stack_size(stack) + 1;

  new_top_object->value.pair = pair;
  set_stack_top(stack, new_top_object);
  set_stack_size(stack, new_stack_size);
}

KLObject* pop_stack (Stack* stack)
{
  KLObject* top_object = get_stack_top(stack);

  if (is_empty_kl_list(top_object))
    return top_object;

  Pair* pair = top_object->value.pair;
  KLObject* car_object = get_pair_car(pair);
  KLObject* cdr_object = get_pair_cdr(pair);
  size_t new_stack_size = get_stack_size(stack) - 1;
  
  set_stack_top(stack, cdr_object);
  set_stack_size(stack, new_stack_size);
  
  return car_object;
}

KLObject* peek_stack (Stack* stack)
{
  KLObject* top_object = get_stack_top(stack);

  if (is_empty_kl_list(top_object))
    return top_object;

  Pair* pair = top_object->value.pair;
  KLObject* car_object = get_pair_car(pair);

  return car_object;
}
