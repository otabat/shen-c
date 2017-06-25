#include <stdlib.h>

#include "init.h"

int main (void)
{
  GC_init();

  char* home_path = getenv("SHEN_C_HOME");

  if (is_null(home_path))
    throw_kl_exception("SHEN_C_HOME environment variable is not set\n"
                       "Set the variable to the Shen-C root directory\n"
                       "ex) export SHEN_C_HOME=/home/user/shen-c");

  initialize_and_run_shen_repl(home_path);

  return 0;
}
