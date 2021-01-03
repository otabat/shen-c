#ifndef SHEN_C_INIT_H
#define SHEN_C_INIT_H

#include "boolean.h"
#include "environment.h"
#include "extension.h"
#include "kl.h"
#include "loop.h"
#include "number.h"
#include "object.h"
#include "primitive.h"
#include "repl.h"
#include "repl_socket.h"
#include "stream.h"
#include "string.h"
#include "symbol_pool.h"
#include "variable.h"
#include "vector.h"

inline void initialize (void)
{
  initialize_boolean_objects();
  initialize_empty_kl_list();
  initialize_empty_vector();
  initialize_empty_loop_frame_pair();
  initialize_start_clock();
  initialize_trapped_kl_exception_stack();
  initialize_loop_frame_stack();
  initialize_string_table();
  initialize_symbol_table();
  register_string_objects();
  register_symbol_objects();
  register_primitive_kl_functions();
  register_extension_primitive_kl_functions();
  initialize_read_buffer();

  #ifdef SHEN_C_MOBILE
  initialize_repl_socket_std_stream_objects();
  #else
  initialize_std_stream_objects();
  #endif

  register_global_variables();
}

inline void initialize_and_run_shen_repl (const char* home_path, int argc, char **argv)
{
  GC_init();

  char* slashed_home_path = concatenate_string((char*)home_path, "/");

  initialize_shen_c_home_path(slashed_home_path);

  #ifdef SHEN_C_MOBILE
  start_repl_server("127.0.0.1", "34957", 1);
  #endif

  initialize();
  load_shen_kl_files();

  #ifdef SHEN_C_MOBILE
  load_kl_file("/src/kl/mobile/init.kl");
  #endif

  //load_development_kl_file();
  //run_kl_repl();
  run_shen_repl(argc, argv);
}

#endif
