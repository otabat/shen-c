#include "vector.h"

static Vector* empty_vector = NULL; 

KLObject** get_vector_objects (Vector* vector)
{
  return vector->objects;
}

void set_vector_objects (Vector* vector, KLObject** objects)
{
  vector->objects = objects;
}

size_t get_vector_size (Vector* vector)
{
  return vector->size;
}

void set_vector_size (Vector* vector, size_t size)
{
  vector->size = size;
}

Vector* create_vector (size_t size)
{
  Vector* vector = malloc(sizeof(Vector));
  KLObject** objects = malloc(sizeof(KLObject) * size);

  for (size_t i = 0; i < size; ++i) {
    objects[i] = create_kl_number_l(0);
  }

  set_vector_objects(vector, objects);
  set_vector_size(vector, size);

  return vector;
}

Vector* get_empty_vector (void)
{
  return empty_vector;
}

void initialize_empty_vector (void)
{
  Vector* vector = malloc(sizeof(Vector));

  set_vector_objects(vector, NULL);
  set_vector_size(vector, 0);
  empty_vector = vector;
}

bool is_empty_vector (Vector* vector)
{
  return get_empty_vector() == vector;
}

KLObject* get_vector_element (Vector* vector, long index)
{
  size_t size = get_vector_size(vector);

  if (index >= (long)size || index < 0)
    throw_kl_exception("Vector index is out of bound");

  KLObject** objects = get_vector_objects(vector);

  return objects[index];
}

void set_vector_element (Vector* vector, long index, KLObject* object)
{
  size_t size = get_vector_size(vector);

  if (index >= (long)size || index < 0)
    throw_kl_exception("Vector index is out of bound");

  KLObject** objects = get_vector_objects(vector);

  objects[index] = object;
}

Vector* get_vector(KLObject* vector_object)
{
  return vector_object->value.vector;
}

void set_vector (KLObject* vector_object, Vector* vector)
{
  vector_object->value.vector = vector;
}

KLObject* create_kl_vector (size_t size)
{
  if (size <= 0)
    throw_kl_exception("Vector size should be greater than 0");
  
  KLObject* vector_object = create_kl_object(KL_TYPE_VECTOR);
  Vector* vector = create_vector(size);

  set_vector(vector_object, vector);

  return vector_object;
}

KLObject** get_kl_vector_objects (KLObject* vector_object)
{
  return get_vector_objects(get_vector(vector_object));
}

void set_kl_vector_objects (KLObject* vector_object, KLObject** objects)
{
  set_vector_objects(get_vector(vector_object), objects);
}

size_t get_kl_vector_size (KLObject* vector_object)
{
  return get_vector_size(get_vector(vector_object)); 
}

void set_kl_vector_size (KLObject* vector_object, size_t size)
{
  set_vector_size(get_vector(vector_object), size);
}

KLObject* get_kl_vector_element (KLObject* vector_object, KLObject* index)
{
  if (!is_kl_vector(vector_object))
    throw_kl_exception("Failed to get an element from a non-vector object");

  return get_vector_element(get_vector(vector_object),
                            get_kl_number_number_l(index));
}

KLObject* set_kl_vector_element (KLObject* vector_object, KLObject* index,
                                 KLObject* object)
{
  if (!is_kl_vector(vector_object))
    throw_kl_exception("Failed to set an element to a non-vector object");

  set_vector_element(get_vector(vector_object), get_kl_number_number_l(index),
                     object);

  return vector_object;
}

bool is_kl_vector (KLObject* object)
{
  return get_kl_object_type(object) == KL_TYPE_VECTOR;
}
