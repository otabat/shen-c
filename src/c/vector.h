#ifndef SHEN_C_VECTOR_H
#define SHEN_C_VECTOR_H

#include "exception.h"
#include "kl.h"
#include "list.h"
#include "number.h"
#include "string.h"
#include "symbol.h"

KLObject** get_vector_objects (Vector* vector);
void set_vector_objects (Vector* vector, KLObject** objects);
size_t get_vector_size (Vector* vector);
void set_vector_size (Vector* vector, size_t size);
Vector* create_vector (size_t size);
Vector* get_empty_vector (void);
void initialize_empty_vector (void);
bool is_empty_vector (Vector* vector); 
KLObject* get_vector_element (Vector* vector, long index);
void set_vector_element (Vector* vector, long index, KLObject* object);

Vector* get_vector(KLObject* vector_object);
void set_vector (KLObject* vector_object, Vector* vector);
KLObject* create_kl_vector (size_t size);
KLObject** get_kl_vector_objects (KLObject* vector_object);
void set_kl_vector_objects (KLObject* vector_object, KLObject** objects);
size_t get_kl_vector_size (KLObject* vector_object);
void set_kl_vector_size (KLObject* vector_object, size_t size);
KLObject* get_kl_vector_element (KLObject* vector_object, KLObject* index);
KLObject* set_kl_vector_element (KLObject* vector_object, KLObject* index,
                                 KLObject* object);
bool is_kl_vector (KLObject* object);

#endif
