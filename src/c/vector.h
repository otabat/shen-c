#ifndef SHEN_C_VECTOR_H
#define SHEN_C_VECTOR_H

#include "exception.h"
#include "kl.h"
#include "list.h"
#include "number.h"
#include "string.h"
#include "symbol.h"

extern Vector* empty_vector;

inline KLObject** get_vector_objects (Vector* vector)
{
  return vector->objects;
}

inline void set_vector_objects (Vector* vector, KLObject** objects)
{
  vector->objects = objects;
}

inline long get_vector_size (Vector* vector)
{
  return vector->size;
}

inline void set_vector_size (Vector* vector, long size)
{
  vector->size = size;
}

inline Vector* create_vector (long size)
{
  Vector* vector = malloc(sizeof(Vector));
  KLObject** objects = malloc(sizeof(KLObject*) * (size_t)size);

  set_vector_objects(vector, objects);
  set_vector_size(vector, size);

  return vector;
}

inline void initialize_empty_vector (void)
{
  Vector* vector = malloc(sizeof(Vector));

  set_vector_objects(vector, NULL);
  set_vector_size(vector, 0);
  empty_vector = vector;
}

inline Vector* get_empty_vector (void)
{
  return empty_vector;
}

inline bool is_empty_vector (Vector* vector)
{
  return get_empty_vector() == vector;
}

inline KLObject* get_vector_element (Vector* vector, long index)
{
  KLObject** objects = get_vector_objects(vector);

  return objects[index];
}

inline void set_vector_element (Vector* vector, long index, KLObject* object)
{
  KLObject** objects = get_vector_objects(vector);

  objects[index] = object;
}

inline Vector* get_vector(KLObject* vector_object)
{
  return vector_object->value.vector;
}

inline void set_vector (KLObject* vector_object, Vector* vector)
{
  vector_object->value.vector = vector;
}

inline KLObject* create_kl_vector (long size)
{
  if (size <= 0)
    throw_kl_exception("Vector size should be greater than 0");

  KLObject* vector_object = create_kl_object(KL_TYPE_VECTOR);
  Vector* vector = create_vector(size);

  set_vector(vector_object, vector);

  return vector_object;
}

inline bool is_kl_vector (KLObject* object)
{
  return get_kl_object_type(object) == KL_TYPE_VECTOR;
}

inline KLObject** get_kl_vector_objects (KLObject* vector_object)
{
  return get_vector_objects(get_vector(vector_object));
}

inline void set_kl_vector_objects (KLObject* vector_object, KLObject** objects)
{
  set_vector_objects(get_vector(vector_object), objects);
}

inline long get_kl_vector_size (KLObject* vector_object)
{
  return get_vector_size(get_vector(vector_object));
}

inline void set_kl_vector_size (KLObject* vector_object, long size)
{
  set_vector_size(get_vector(vector_object), size);
}

inline KLObject* get_kl_vector_element (KLObject* vector_object,
                                        KLObject* number_object)
{
  return get_vector_element(get_vector(vector_object),
                            get_kl_number_number_l(number_object));
}

inline KLObject* set_kl_vector_element (KLObject* vector_object,
                                        KLObject* number_object,
                                        KLObject* object)
{
  set_vector_element(get_vector(vector_object),
                     get_kl_number_number_l(number_object),
                     object);

  return vector_object;
}

#endif
