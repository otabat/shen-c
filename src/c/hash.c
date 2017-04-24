#include "hash.h"

extern size_t djb2_hash (unsigned char *str);
extern long bounded_hash (char* string, long divisor);
extern KLObject* kl_object_bounded_hash (KLObject* object,
                                         KLObject* number_object);
