#ifndef SHEN_C_REPL_H
#define SHEN_C_REPL_H

#include <stdio.h>
#include <setjmp.h>

#include "evaluator.h"
#include "kl.h"
#include "list.h"
#include "object.h"
#include "reader.h"
#include "stream.h"

void load_kl_file (char* file_path);
void load_shen_kl_files (void);
void run_kl_repl (void);
void run_shen_repl (void);

#endif
