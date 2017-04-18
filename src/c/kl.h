#ifndef SHEN_C_KL_H
#define SHEN_C_KL_H

#include <stdbool.h>
#include <stdio.h>
#include <setjmp.h>

#include "gc.h"
#include "khash.h"

#define malloc(n) GC_malloc(n)
#define realloc(n) GC_realloc(n)
#define calloc(m,n) GC_malloc((m)*(n))
#define free(m) GC_free(m)

typedef enum KLType {
  KL_TYPE_SYMBOL, KL_TYPE_STRING, KL_TYPE_NUMBER, KL_TYPE_BOOLEAN,
  KL_TYPE_FUNCTION, KL_TYPE_STREAM, KL_TYPE_EXCEPTION,
  KL_TYPE_LIST, KL_TYPE_VECTOR
} KLType;

typedef enum KLNumberType {
  KL_NUMBER_TYPE_LONG, KL_NUMBER_TYPE_DOUBLE
} KLNumberType;

typedef enum KLFunctionType {
  KL_FUNCTION_TYPE_PRIMITIVE_FUNCTION, KL_FUNCTION_TYPE_USER_FUNCTION,
  KL_FUNCTION_TYPE_CLOSURE
} KLFunctionType;

typedef enum KLStreamType {
  KL_STREAM_TYPE_IN, KL_STREAM_TYPE_OUT
} KLStreamType;

typedef enum DefunType {
  DEFUN_TYPE_NON_TAIL_CALL, DEFUN_TYPE_POSSIBLY_TAIL_CALL,
  DEFUN_TYPE_TAIL_CALL
} DefunType;

typedef struct KLObject KLObject;
typedef struct Number Number;
typedef struct Function Function;
typedef struct Stream Stream;
typedef struct Exception Exception;
typedef struct Pair Pair;
typedef struct Vector Vector;
typedef struct Environment Environment;
typedef struct LoopFramePair LoopFramePair;

typedef void (FunctionDeclaration) (void);
typedef KLObject* (NativeFunction) (KLObject* function_object, Vector* arguments);

struct KLObject {
  KLType type;
  union {
    char* symbol;
    char* string;
    Number* number;
    bool boolean;
    Function* function;
    Stream* stream;
    Exception* exception;
    Pair* pair;
    Vector* vector;
  } value;
};

struct Number {
  KLNumberType number_type;
  union {
    long number_l;
    double number_d;
  } value;
};

typedef struct PrimitiveFunction {
  size_t parameter_size;
  NativeFunction* native_function;
} PrimitiveFunction;

typedef struct UserFunction {
  Vector* parameters;
  KLObject* body;
} UserFunction;

typedef struct Closure {
  KLObject* parameter;
  KLObject* body;
  Environment* parent_function_environment;
  Environment* parent_variable_environment;
} Closure;

struct Function {
  KLFunctionType function_type;
  union {
    PrimitiveFunction* primitive_function;
    UserFunction* user_function;
    Closure* closure;
  } value ;
};

struct Stream {
  FILE* file;
  KLStreamType stream_type;
};

struct Exception {
  char* error_message;
  jmp_buf* jump_buffer;
};

struct Pair {
  KLObject* car;
  KLObject* cdr;
};

struct Vector {
  KLObject** objects;
  size_t size;
};

KHASH_MAP_INIT_STR(SymbolTable, KLObject*)

struct Environment {
  khash_t(SymbolTable)* symbol_table;
  Environment* parent;
};

typedef struct Stack {
  KLObject* top;
  size_t size;
} Stack;

typedef struct LoopFrame {
  Vector* arguments;
  Vector* parameters;
  jmp_buf* jump_buffer;
} LoopFrame;

struct LoopFramePair {
  LoopFrame* car;
  LoopFramePair* cdr;
};

typedef struct LoopFrameStack {
  LoopFramePair* top;
  size_t size;
} LoopFrameStack;

KLType get_kl_object_type (KLObject* object);
void set_kl_object_type (KLObject* object, KLType type);
KLObject* create_kl_object (KLType type);
bool is_null (void* object);
bool is_not_null (void* object);

KLObject* get_pair_car (Pair* pair);
void set_pair_car (Pair* pair, KLObject* object);
KLObject* get_pair_cdr (Pair* pair);
void set_pair_cdr (Pair* pair, KLObject* object);
Pair* create_pair (KLObject* car_object, KLObject* cdr_object);

void initialize_empty_kl_list (void);
KLObject* get_empty_kl_list (void);
bool is_empty_kl_list (KLObject* object);

#endif
