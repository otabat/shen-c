#include "dictionary.h"

extern khash_t(StringPairTable)* get_dictionary_table (Dictionary* dictionary);
extern void set_dictionary_table (Dictionary* dictionary,
                                  khash_t(StringPairTable)* table);
extern Dictionary* create_dictionary (void);
extern Dictionary* get_dictionary (KLObject* dictionary_object);
extern void set_dictionary (KLObject* dictionary_object, Dictionary* dictionary);
extern KLObject* create_kl_dictionary (void);
extern khash_t(StringPairTable)* get_kl_dictionary_table
(KLObject* dictionary_object);
extern void set_kl_dictionary_table (KLObject* dictionary_object,
                                     khash_t(StringPairTable)* table);
extern bool is_kl_dictionary (KLObject* object);
extern long get_dictionary_count (Dictionary* dictionary);
extern KLObject* get_kl_dictionary_count (KLObject* dictionary_object);
extern KLObject* get_dictionary_keys (Dictionary* dictionary);
extern KLObject* get_kl_dictionary_keys (KLObject* dictionary_object);
extern KLObject* get_dictionary_values (Dictionary* dictionary);
extern KLObject* get_kl_dictionary_values (KLObject* dictionary_object);
