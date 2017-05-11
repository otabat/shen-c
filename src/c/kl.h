#ifndef SHEN_C_KL_H
#define SHEN_C_KL_H

#include <stdbool.h>
#include <stdint.h>
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
typedef struct Symbol Symbol;
typedef struct Number Number;
typedef struct Function Function;
typedef struct Stream Stream;
typedef struct Exception Exception;
typedef struct Pair Pair;
typedef struct Vector Vector;
typedef struct Environment Environment;
typedef struct LoopFramePair LoopFramePair;

typedef void (FunctionDeclaration) (void);
typedef KLObject* (NativeFunction) (KLObject* function_object, Vector* arguments,
                                    Environment* function_environment,
                                    Environment* variable_environment);

struct KLObject {
  KLType type;
  union {
    Symbol* symbol;
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

KHASH_MAP_INIT_STR(SymbolNameTable, KLObject*)

#if UINTPTR_MAX == 0xffffffff
// 32bit
KHASH_MAP_INIT_INT(SymbolObjectTable, KLObject*)

#elif UINTPTR_MAX == 0xffffffffffffffff
// 64bit
KHASH_MAP_INIT_INT64(SymbolObjectTable, KLObject*)

#else
#error Could not determine pointer size

#endif

struct Symbol {
  char* name;
  KLObject* function;
  KLObject* variable_value;
};

struct Number {
  KLNumberType number_type;
  union {
    long number_l;
    double number_d;
  } value;
};

typedef struct PrimitiveFunction {
  long parameter_size;
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
  long size;
};

struct Environment {
  khash_t(SymbolObjectTable)* symbol_object_table;
  Environment* parent;
};

typedef struct Stack {
  KLObject* top;
  long size;
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
  long size;
} LoopFrameStack;

extern KLObject* empty_list_object;

inline KLType get_kl_object_type (KLObject* object)
{
  return object->type;
}

inline void set_kl_object_type (KLObject* object, KLType type)
{
  object->type = type;
}

inline KLObject* create_kl_object (KLType type)
{
  KLObject* object = malloc(sizeof(KLObject));

  set_kl_object_type(object, type);

  return object;
}

inline bool is_null (void* object)
{
  return object == NULL;
}

inline bool is_not_null (void* object)
{
  return object != NULL;
}

inline KLObject* get_pair_car (Pair* pair)
{
  return pair->car;
}

inline void set_pair_car (Pair* pair, KLObject* object)
{
  pair->car = object;
}

inline KLObject* get_pair_cdr (Pair* pair)
{
  return pair->cdr;
}

inline void set_pair_cdr (Pair* pair, KLObject* object)
{
  pair->cdr = object;
}

inline Pair* create_pair (KLObject* car_object, KLObject* cdr_object)
{
  Pair* pair = malloc(sizeof(Pair));

  set_pair_car(pair, car_object);
  set_pair_cdr(pair, cdr_object);

  return pair;
}

inline void initialize_empty_kl_list (void)
{
  KLObject* list_object = create_kl_object(KL_TYPE_LIST);

  list_object->value.pair = create_pair(list_object, list_object);
  empty_list_object = list_object;
}

inline KLObject* get_empty_kl_list (void)
{
  return empty_list_object;
}

inline bool is_empty_kl_list (KLObject* object)
{
  return object == get_empty_kl_list();
}

#define EL get_empty_kl_list()

#endif
