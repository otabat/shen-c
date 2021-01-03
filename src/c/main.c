#include <stdlib.h>

#include "init.h"

#ifdef __linux__
#include <unistd.h>
#include <libgen.h>
#include <linux/limits.h>

char exe_path[PATH_MAX];

char *get_home_path() {
  char *path = getenv("SHEN_C_HOME");
  if (path) return path;

  if (readlink("/proc/self/exe", exe_path, PATH_MAX) != -1)
  {
    dirname(exe_path);
    strcat(exe_path, "/../");
    return exe_path;
  }
  return NULL;
}

#else
char *get_home_path() {
  return getenv("SHEN_C_HOME");
}
#endif

int main (int argc, char** argv)
{
  GC_init();

  char* home_path = get_home_path();

  if (is_null(home_path))  {

    fprintf(stderr, "SHEN_C_HOME environment variable is not set.\n"
                    "Set the variable to the Shen-C root directory\n"
                    "For example:\nexport SHEN_C_HOME=/home/user/shen-c\n");
    return EXIT_FAILURE; 
  }

  initialize_and_run_shen_repl(home_path, argc, argv);

  return EXIT_SUCCESS;
}
