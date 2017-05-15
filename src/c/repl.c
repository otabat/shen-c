#include "repl.h"

void load_kl_file (char* shen_c_home_path, char* file_path)
{
  char* absolute_file_path = concatenate_string(shen_c_home_path, file_path);
  KLObject* stream = create_kl_stream(absolute_file_path, get_in_symbol_object());

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

void load_shen_kl_files (char* shen_c_home_path)
{
  load_kl_file(shen_c_home_path, "/shen/src/kl/toplevel.kl");
  register_overwrite_toplevel_primitive_kl_functions();

  load_kl_file(shen_c_home_path, "/shen/src/kl/core.kl");
  register_overwrite_core_primitive_kl_functions();

  load_kl_file(shen_c_home_path, "/shen/src/kl/sys.kl");
  register_overwrite_sys_primitive_kl_functions();

  load_kl_file(shen_c_home_path, "/shen/src/kl/sequent.kl");

  load_kl_file(shen_c_home_path, "/shen/src/kl/yacc.kl");
  register_overwrite_yacc_primitive_kl_functions();

  load_kl_file(shen_c_home_path, "/shen/src/kl/reader.kl");
  register_overwrite_reader_primitive_kl_functions();

  load_kl_file(shen_c_home_path, "/shen/src/kl/prolog.kl");
  register_overwrite_prolog_primitive_kl_functions();

  load_kl_file(shen_c_home_path, "/shen/src/kl/track.kl");
  load_kl_file(shen_c_home_path, "/shen/src/kl/load.kl");

  load_kl_file(shen_c_home_path, "/shen/src/kl/writer.kl");
  register_overwrite_writer_primitive_kl_functions();

  load_kl_file(shen_c_home_path, "/shen/src/kl/macros.kl");
  register_overwrite_macros_primitive_kl_functions();

  load_kl_file(shen_c_home_path, "/shen/src/kl/declarations.kl");
  load_kl_file(shen_c_home_path, "/shen/src/kl/types.kl");
  load_kl_file(shen_c_home_path, "/shen/src/kl/t-star.kl");
}

void load_development_kl_file (char* shen_c_home_path)
{
  load_kl_file(shen_c_home_path, "/src/kl/development.kl");
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
  KLObject* shen_symbol_object = lookup_symbol_name_table("shen.shen");
  KLObject* list_object = CONS(shen_symbol_object, EL);

  eval_kl_object(list_object, get_global_function_environment(),
                 get_global_variable_environment());
}
