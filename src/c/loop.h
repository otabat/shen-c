#ifndef SHEN_C_LOOP_H
#define SHEN_C_LOOP_H

#include <stdbool.h>
#include <setjmp.h>

#include "kl.h"
#include "vector.h"

Vector* get_loop_frame_arguments (LoopFrame* frame);
void set_loop_frame_arguments (LoopFrame* frame, Vector* arguments);
Vector* get_loop_frame_parameters (LoopFrame* frame);
void set_loop_frame_parameters (LoopFrame* frame, Vector* parameters);
jmp_buf* get_loop_frame_jump_buffer (LoopFrame* frame);
void set_loop_frame_jump_buffer (LoopFrame* frame, jmp_buf* jump_buffer);
LoopFrame* create_loop_frame (void);

LoopFrame* get_loop_frame_pair_car (LoopFramePair* frame_pair);
void set_loop_frame_pair_car (LoopFramePair* frame_pair, LoopFrame* frame);
LoopFramePair* get_loop_frame_pair_cdr (LoopFramePair* frame_pair);
void set_loop_frame_pair_cdr (LoopFramePair* frame_pair,
                              LoopFramePair* cdr_frame_pair);
LoopFramePair* create_loop_frame_pair (LoopFrame* car_frame,
                                       LoopFramePair* cdr_frame_pair);
void initialize_empty_loop_frame_pair (void);
LoopFramePair* get_empty_loop_frame_pair (void);
bool is_empty_loop_frame_pair (LoopFramePair* frame_pair);

LoopFrameStack* get_loop_frame_stack (void);
void set_loop_frame_stack (LoopFrameStack* frame_stack);
LoopFramePair* get_loop_frame_stack_top (LoopFrameStack* frame_stack);
void set_loop_frame_stack_top (LoopFrameStack* frame_stack,
                               LoopFramePair* frame_pair);
size_t get_loop_frame_stack_size (LoopFrameStack* frame_stack);
void set_loop_frame_stack_size (LoopFrameStack* frame_stack,
                                size_t frame_stack_size);
void initialize_loop_frame_stack (void);

void push_loop_frame_stack_with_frame_pair (LoopFramePair* frame_pair);
LoopFrame* pop_loop_frame_stack (void);
LoopFrame* peek_loop_frame_stack (void);

#endif
