#include "exception.h"

static Stack* trapped_kl_exception_stack;

char* get_exception_error_message (Exception* exception)
{
  return exception->error_message;
}

void set_exception_error_message (Exception* exception, char* error_message)
{
  exception->error_message = error_message;
}

jmp_buf* get_exception_jump_buffer (Exception* exception)
{
  return exception->jump_buffer;
}

void set_exception_jump_buffer (Exception* exception, jmp_buf* jump_buffer)
{
  exception->jump_buffer = jump_buffer;
}

Exception* create_exception (void)
{
  Exception* exception = malloc(sizeof(Exception));

  return exception;
}

Exception* get_exception (KLObject* exception_object)
{
  return exception_object->value.exception;
}

void set_exception (KLObject* exception_object, Exception* exception)
{
  exception_object->value.exception = exception; 
}

KLObject* create_kl_exception (void)
{
  KLObject* exception_object = create_kl_object(KL_TYPE_EXCEPTION);
  Exception* exception = create_exception();
  
  set_exception(exception_object, exception);

  return exception_object;
}

jmp_buf* get_kl_exception_jump_buffer (KLObject* exception_object)
{
  return get_exception_jump_buffer(get_exception(exception_object));
}

void set_kl_exception_jump_buffer (KLObject* exception_object,
                                   jmp_buf* jump_buffer)
{
  set_exception_jump_buffer(get_exception(exception_object),
                            jump_buffer);
}

Stack* get_trapped_kl_exception_stack (void)
{
  return trapped_kl_exception_stack;
}

void set_trapped_kl_exception_stack (Stack* stack)
{
  trapped_kl_exception_stack = stack;
}

void initialize_trapped_kl_exception_stack (void)
{
  set_trapped_kl_exception_stack(create_stack());
}

void throw_kl_exception (char* error_message)
{
  KLObject* exception_object = peek_stack(get_trapped_kl_exception_stack());

  if (is_empty_kl_list(exception_object)) {
    fprintf(stderr, "%s\n", error_message);
    exit(EXIT_FAILURE);
  }

  Exception* exception = get_exception(exception_object);

  set_exception_error_message(exception, error_message);

  jmp_buf* jump_buffer = get_exception_jump_buffer(exception);

  siglongjmp(*jump_buffer, 1);
}

bool is_kl_exception (KLObject* object)
{
  return get_kl_object_type(object) == KL_TYPE_EXCEPTION;
}

bool is_kl_exception_equal (KLObject* left_object, KLObject* right_object)
{
  return left_object == right_object;
}

char* kl_exception_to_string (KLObject* exception_object)
{
  Exception* exception = get_exception(exception_object);
  char* error_message = get_exception_error_message(exception);
  char length_string[1];
  int object_string_length = snprintf(length_string, 1,
                                      "#<Exception {0x%016" PRIxPTR "} %s>",
                                      (uintptr_t)exception_object,
                                      error_message);
  char* object_string = malloc((size_t)object_string_length + 1);
  
  sprintf(object_string, "#<Exception {0x%016" PRIxPTR "} %s>",
          (uintptr_t)exception_object,
          error_message);

  return object_string;
}
