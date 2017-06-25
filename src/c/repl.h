#ifndef SHEN_C_REPL_H
#define SHEN_C_REPL_H

#include <stdio.h>
#include <setjmp.h>

#include "evaluator.h"
#include "exception.h"
#include "kl.h"
#include "list.h"
#include "object.h"
#include "overwrite.h"
#include "reader.h"
#include "stream.h"
#include "symbol.h"

void load_kl_file (char* file_path);
void load_shen_kl_files (void);
void load_development_kl_file (void);
void run_kl_repl (void);
void run_shen_repl (void);

#endif
