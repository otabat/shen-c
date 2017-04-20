#include "loop.h"

LoopFrameStack* loop_frame_stack;
LoopFramePair* empty_loop_frame_pair;

extern Vector* get_loop_frame_arguments (LoopFrame* frame);
extern void set_loop_frame_arguments (LoopFrame* frame, Vector* arguments);
extern Vector* get_loop_frame_parameters (LoopFrame* frame);
extern void set_loop_frame_parameters (LoopFrame* frame, Vector* parameters);
extern jmp_buf* get_loop_frame_jump_buffer (LoopFrame* frame);
extern void set_loop_frame_jump_buffer (LoopFrame* frame, jmp_buf* jump_buffer);
extern LoopFrame* create_loop_frame (void);

extern LoopFrame* get_loop_frame_pair_car (LoopFramePair* frame_pair);
extern void set_loop_frame_pair_car (LoopFramePair* frame_pair, LoopFrame* frame);
extern LoopFramePair* get_loop_frame_pair_cdr (LoopFramePair* frame_pair);
extern void set_loop_frame_pair_cdr (LoopFramePair* frame_pair,
                                     LoopFramePair* cdr_frame_pair);
extern LoopFramePair* create_loop_frame_pair (LoopFrame* car_frame,
                                              LoopFramePair* cdr_frame_pair);
extern void initialize_empty_loop_frame_pair (void);
extern LoopFramePair* get_empty_loop_frame_pair (void);
extern bool is_empty_loop_frame_pair (LoopFramePair* frame_pair);

extern LoopFrameStack* get_loop_frame_stack (void);
extern void set_loop_frame_stack (LoopFrameStack* frame_stack);
extern LoopFramePair* get_loop_frame_stack_top (LoopFrameStack* frame_stack);
extern void set_loop_frame_stack_top (LoopFrameStack* frame_stack,
                                      LoopFramePair* frame_pair);
extern size_t get_loop_frame_stack_size (LoopFrameStack* frame_stack);
extern void set_loop_frame_stack_size (LoopFrameStack* frame_stack,
                                       size_t frame_stack_size);
extern void initialize_loop_frame_stack (void);

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
