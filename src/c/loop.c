#include "loop.h"

static LoopFrameStack* loop_frame_stack;
static LoopFramePair* empty_loop_frame_pair;

Vector* get_loop_frame_arguments (LoopFrame* frame)
{
  return frame->arguments;
}

void set_loop_frame_arguments (LoopFrame* frame, Vector* arguments)
{
  frame->arguments = arguments;
}

Vector* get_loop_frame_parameters (LoopFrame* frame)
{
  return frame->parameters;
}

void set_loop_frame_parameters (LoopFrame* frame, Vector* parameters)
{
  frame->parameters = parameters;
}

jmp_buf* get_loop_frame_jump_buffer (LoopFrame* frame)
{
  return frame->jump_buffer;
}

void set_loop_frame_jump_buffer (LoopFrame* frame, jmp_buf* jump_buffer)
{
  frame->jump_buffer = jump_buffer;
}

LoopFrame* create_loop_frame (void)
{
  LoopFrame* frame = malloc(sizeof(LoopFrame));

  set_loop_frame_arguments(frame, NULL);
  set_loop_frame_parameters(frame, NULL);
  set_loop_frame_jump_buffer(frame, NULL);

  return frame;
}

LoopFrame* get_loop_frame_pair_car (LoopFramePair* frame_pair)
{
  return frame_pair->car;
}

void set_loop_frame_pair_car (LoopFramePair* frame_pair, LoopFrame* frame)
{
  frame_pair->car = frame;
}

LoopFramePair* get_loop_frame_pair_cdr (LoopFramePair* frame_pair)
{
  return frame_pair->cdr;
}

void set_loop_frame_pair_cdr (LoopFramePair* frame_pair,
                              LoopFramePair* cdr_frame_pair)
{
  frame_pair->cdr = cdr_frame_pair;
}

LoopFramePair* create_loop_frame_pair (LoopFrame* car_frame,
                                       LoopFramePair* cdr_frame_pair)
{
  LoopFramePair* frame_pair = malloc(sizeof(LoopFramePair));

  set_loop_frame_pair_car(frame_pair, car_frame);
  set_loop_frame_pair_cdr(frame_pair, cdr_frame_pair);

  return frame_pair;
}

void initialize_empty_loop_frame_pair (void)
{
  empty_loop_frame_pair = create_loop_frame_pair(NULL, NULL);
}

LoopFramePair* get_empty_loop_frame_pair (void)
{
  return empty_loop_frame_pair;
}

bool is_empty_loop_frame_pair (LoopFramePair* frame_pair)
{
  return frame_pair == get_empty_loop_frame_pair();
}

LoopFrameStack* get_loop_frame_stack (void)
{
  return loop_frame_stack;
}

void set_loop_frame_stack (LoopFrameStack* frame_stack)
{
  loop_frame_stack = frame_stack;
}

LoopFramePair* get_loop_frame_stack_top (LoopFrameStack* frame_stack)
{
  return frame_stack->top;
}

void set_loop_frame_stack_top (LoopFrameStack* frame_stack,
                               LoopFramePair* frame_pair)
{
  frame_stack->top = frame_pair;
}

size_t get_loop_frame_stack_size (LoopFrameStack* frame_stack)
{
  return frame_stack->size;
}

void set_loop_frame_stack_size (LoopFrameStack* frame_stack,
                                size_t frame_stack_size)
{
  frame_stack->size = frame_stack_size;
}

void initialize_loop_frame_stack (void)
{
  LoopFrameStack* frame_stack = malloc(sizeof(LoopFrameStack));

  set_loop_frame_stack_top(frame_stack, get_empty_loop_frame_pair());
  set_loop_frame_stack_size(frame_stack, 0);
  set_loop_frame_stack(frame_stack);
}

void push_loop_frame_stack_with_frame_pair (LoopFramePair* frame_pair)
{
  LoopFramePair* top_frame_pair =
    get_loop_frame_stack_top(get_loop_frame_stack());
  size_t new_frame_stack_size =
    get_loop_frame_stack_size(get_loop_frame_stack()) + 1;

  set_loop_frame_pair_cdr(frame_pair, top_frame_pair);
  set_loop_frame_stack_top(get_loop_frame_stack(), frame_pair);
  set_loop_frame_stack_size(get_loop_frame_stack(), new_frame_stack_size);
}

LoopFrame* pop_loop_frame_stack (void)
{
  LoopFramePair* top_frame_pair =
    get_loop_frame_stack_top(get_loop_frame_stack());

  if (is_empty_loop_frame_pair(top_frame_pair))
    return NULL;

  LoopFrame* car_frame = get_loop_frame_pair_car(top_frame_pair);
  LoopFramePair* cdr_frame_pair = get_loop_frame_pair_cdr(top_frame_pair);
  size_t new_frame_stack_size =
    get_loop_frame_stack_size(get_loop_frame_stack()) - 1;

  set_loop_frame_stack_top(get_loop_frame_stack(), cdr_frame_pair);
  set_loop_frame_stack_size(get_loop_frame_stack(), new_frame_stack_size);

  return car_frame;
}

LoopFrame* peek_loop_frame_stack (void)
{
  LoopFramePair* top_frame_pair =
    get_loop_frame_stack_top(get_loop_frame_stack());

  if (is_empty_loop_frame_pair(top_frame_pair))
    return NULL;

  return get_loop_frame_pair_car(top_frame_pair);
}
