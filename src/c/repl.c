#include "repl.h"

void load_kl_file (char* file_path)
{
  KLObject* stream = create_kl_stream(file_path , "in");

  while (true) {
    KLObject* read_object = read_string(stream);

    if (is_null(read_object))
      break;

    eval_kl_object(read_object,
                   get_global_function_environment(),
                   get_global_variable_environment());
  } 

  close_kl_stream(stream);
}

void load_shen_kl_files (void)
{
  load_kl_file("src/kl/toplevel.kl");
  load_kl_file("src/kl/core.kl");
  load_kl_file("src/kl/sys.kl");
  load_kl_file("src/kl/sequent.kl");
  load_kl_file("src/kl/yacc.kl");
  load_kl_file("src/kl/reader.kl");
  load_kl_file("src/kl/prolog.kl");
  load_kl_file("src/kl/track.kl");
  load_kl_file("src/kl/load.kl");
  load_kl_file("src/kl/writer.kl");
  load_kl_file("src/kl/macros.kl");
  load_kl_file("src/kl/declarations.kl");
  load_kl_file("src/kl/types.kl");
  load_kl_file("src/kl/t-star.kl");
}

void run_kl_repl (void)
{
  KLObject* std_input_stream_object = get_std_input_stream_object();

  while (true) {
    jmp_buf jump_buffer;

    if (sigsetjmp(jump_buffer, 0) == 0) {
      KLObject* exception_object = create_kl_exception();
    
      set_kl_exception_jump_buffer(exception_object, &jump_buffer);
      push_stack(get_trapped_kl_exception_stack(), exception_object);
    
      while (true) {
        printf("> ");
        printlnln_kl_object(eval_kl_object(read_string(std_input_stream_object),
                                           get_global_function_environment(),
                                           get_global_variable_environment()));
      }
    } else {
      KLObject* exception_object = pop_stack(get_trapped_kl_exception_stack());
      char* error_message =
        get_exception_error_message(get_exception(exception_object));
      
      printf("Exception: %s\n\n", error_message);
    }
  }
}

void run_shen_repl (void)
{
  KLObject* list_object = create_kl_list(create_kl_symbol("shen"),
                                         get_empty_kl_list());

  eval_kl_object(list_object, get_global_function_environment(),
                 get_global_variable_environment());
}
