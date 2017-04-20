#include "vector.h"

Vector* empty_vector = NULL;

extern KLObject** get_vector_objects (Vector* vector);
extern void set_vector_objects (Vector* vector, KLObject** objects);
extern size_t get_vector_size (Vector* vector);
extern void set_vector_size (Vector* vector, size_t size);
extern Vector* create_vector (size_t size);
extern void initialize_empty_vector (void);
extern Vector* get_empty_vector (void);
extern bool is_empty_vector (Vector* vector);
extern KLObject* get_vector_element (Vector* vector, long index);
extern void set_vector_element (Vector* vector, long index, KLObject* object);

extern Vector* get_vector(KLObject* vector_object);
extern void set_vector (KLObject* vector_object, Vector* vector);
extern KLObject* create_kl_vector (size_t size);
extern bool is_kl_vector (KLObject* object);
extern KLObject** get_kl_vector_objects (KLObject* vector_object);
extern void set_kl_vector_objects (KLObject* vector_object, KLObject** objects);
extern size_t get_kl_vector_size (KLObject* vector_object);
extern void set_kl_vector_size (KLObject* vector_object, size_t size);
extern KLObject* get_kl_vector_element (KLObject* vector_object, KLObject* index);
extern KLObject* set_kl_vector_element (KLObject* vector_object, KLObject* index,
                                        KLObject* object);
