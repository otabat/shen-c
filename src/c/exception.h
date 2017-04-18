#ifndef SHEN_C_EXCEPTION_H
#define SHEN_C_EXCEPTION_H

#include <stdio.h>
#include <inttypes.h>
#include <setjmp.h>

#include "kl.h"
#include "stack.h"

char* get_exception_error_message (Exception* exception);
void set_exception_error_message (Exception* exception, char* error_message);
jmp_buf* get_exception_jump_buffer (Exception* exception);
void set_exception_jump_buffer (Exception* exception, jmp_buf* jump_buffer);
Exception* create_exception (void);

Exception* get_exception (KLObject* exception_object);
void set_exception (KLObject* exception_object, Exception* exception);
KLObject* create_kl_exception (void);
jmp_buf* get_kl_exception_jump_buffer (KLObject* exception_object);
void set_kl_exception_jump_buffer (KLObject* exception_object,
                                   jmp_buf* jump_buffer);
Stack* get_trapped_kl_exception_stack (void);
void set_trapped_kl_exception_stack (Stack* stack);
void initialize_trapped_kl_exception_stack (void);
void throw_kl_exception (char* error_message);
bool is_kl_exception (KLObject* object);
bool is_kl_exception_equal (KLObject* left_object, KLObject* right_object);
char* kl_exception_to_string (KLObject* exception_object);

#endif
