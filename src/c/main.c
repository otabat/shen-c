#include "environment.h"
#include "extension.h"
#include "kl.h"
#include "loop.h"
#include "number.h"
#include "object.h"
#include "primitive.h"
#include "repl.h"
#include "stream.h"
#include "string.h"
#include "symbol.h"
#include "variable.h"
#include "vector.h"

static inline void initialize_global_variables (void)
{
  extend_environment(create_kl_symbol("*language*"), create_kl_symbol("C"),
                     get_global_variable_environment());
  extend_environment(create_kl_symbol("*implementation*"), create_kl_symbol("C"),
                     get_global_variable_environment());
  extend_environment(create_kl_symbol("*release*"), create_kl_number_d(0.1),
                     get_global_variable_environment());
  extend_environment(create_kl_symbol("*port*"), create_kl_number_d(0.1),
                     get_global_variable_environment());
  extend_environment(create_kl_symbol("*porters*"),
                     create_kl_string("Tatsuya Tsuda"),
                     get_global_variable_environment());
  extend_environment(create_kl_symbol("*stinput*"),
                     get_std_input_stream_object(),
                     get_global_variable_environment());
  extend_environment(create_kl_symbol("*stoutput*"),
                     get_std_output_stream_object(),
                     get_global_variable_environment());
  extend_environment(create_kl_symbol("*sterror*"),
                     get_std_error_stream_object(),
                     get_global_variable_environment());
}

static inline void initialize (void)
{
  initialize_empty_kl_list();
  initialize_empty_vector();
  initialize_empty_loop_frame_pair();
  initialize_start_clock();
  initialize_global_function_environment();
  initialize_global_variable_environment();
  initialize_trapped_kl_exception_stack();
  initialize_loop_frame_stack();
  register_primitive_kl_functions();
  register_extension_primitive_kl_functions();
  initialize_read_buffer();
  initialize_std_stream_objects();
  initialize_global_variables();
}

int main (void)
{
  GC_init();
  initialize();
  load_shen_kl_files();
  run_shen_repl();

  return 0;
}
