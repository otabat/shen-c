#ifndef SHEN_C_LOOP_H
#define SHEN_C_LOOP_H

#include <stdbool.h>
#include <setjmp.h>

#include "kl.h"
#include "vector.h"

extern LoopFrameStack* loop_frame_stack;
extern LoopFramePair* empty_loop_frame_pair;

void push_loop_frame_stack_with_frame_pair (LoopFramePair* frame_pair);
LoopFrame* pop_loop_frame_stack (void);
LoopFrame* peek_loop_frame_stack (void);

inline Vector* get_loop_frame_arguments (LoopFrame* frame)
{
  return frame->arguments;
}

inline void set_loop_frame_arguments (LoopFrame* frame, Vector* arguments)
{
  frame->arguments = arguments;
}

inline Vector* get_loop_frame_parameters (LoopFrame* frame)
{
  return frame->parameters;
}

inline void set_loop_frame_parameters (LoopFrame* frame, Vector* parameters)
{
  frame->parameters = parameters;
}

inline jmp_buf* get_loop_frame_jump_buffer (LoopFrame* frame)
{
  return frame->jump_buffer;
}

inline void set_loop_frame_jump_buffer (LoopFrame* frame, jmp_buf* jump_buffer)
{
  frame->jump_buffer = jump_buffer;
}

inline LoopFrame* create_loop_frame (void)
{
  LoopFrame* frame = malloc(sizeof(LoopFrame));

  set_loop_frame_arguments(frame, NULL);
  set_loop_frame_parameters(frame, NULL);
  set_loop_frame_jump_buffer(frame, NULL);

  return frame;
}

inline LoopFrame* get_loop_frame_pair_car (LoopFramePair* frame_pair)
{
  return frame_pair->car;
}

inline void set_loop_frame_pair_car (LoopFramePair* frame_pair, LoopFrame* frame)
{
  frame_pair->car = frame;
}

inline LoopFramePair* get_loop_frame_pair_cdr (LoopFramePair* frame_pair)
{
  return frame_pair->cdr;
}

inline void set_loop_frame_pair_cdr (LoopFramePair* frame_pair,
                                     LoopFramePair* cdr_frame_pair)
{
  frame_pair->cdr = cdr_frame_pair;
}

inline LoopFramePair* create_loop_frame_pair (LoopFrame* car_frame,
                                              LoopFramePair* cdr_frame_pair)
{
  LoopFramePair* frame_pair = malloc(sizeof(LoopFramePair));

  set_loop_frame_pair_car(frame_pair, car_frame);
  set_loop_frame_pair_cdr(frame_pair, cdr_frame_pair);

  return frame_pair;
}

inline void initialize_empty_loop_frame_pair (void)
{
  empty_loop_frame_pair = create_loop_frame_pair(NULL, NULL);
}

inline LoopFramePair* get_empty_loop_frame_pair (void)
{
  return empty_loop_frame_pair;
}

inline bool is_empty_loop_frame_pair (LoopFramePair* frame_pair)
{
  return frame_pair == get_empty_loop_frame_pair();
}

inline LoopFrameStack* get_loop_frame_stack (void)
{
  return loop_frame_stack;
}

inline void set_loop_frame_stack (LoopFrameStack* frame_stack)
{
  loop_frame_stack = frame_stack;
}

inline LoopFramePair* get_loop_frame_stack_top (LoopFrameStack* frame_stack)
{
  return frame_stack->top;
}

inline void set_loop_frame_stack_top (LoopFrameStack* frame_stack,
                                      LoopFramePair* frame_pair)
{
  frame_stack->top = frame_pair;
}

inline size_t get_loop_frame_stack_size (LoopFrameStack* frame_stack)
{
  return frame_stack->size;
}

inline void set_loop_frame_stack_size (LoopFrameStack* frame_stack,
                                       size_t frame_stack_size)
{
  frame_stack->size = frame_stack_size;
}

inline void initialize_loop_frame_stack (void)
{
  LoopFrameStack* frame_stack = malloc(sizeof(LoopFrameStack));

  set_loop_frame_stack_top(frame_stack, get_empty_loop_frame_pair());
  set_loop_frame_stack_size(frame_stack, 0);
  set_loop_frame_stack(frame_stack);
}

#endif
