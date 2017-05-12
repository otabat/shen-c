#ifndef SHEN_C_DICTIONARY_H
#define SHEN_C_DICTIONARY_H

#include <stdbool.h>

#include "khash.h"

#include "kl.h"
#include "list.h"
#include "number.h"

inline khash_t(StringPairTable)* get_dictionary_table (Dictionary* dictionary)
{
  return dictionary->table;
}

inline void set_dictionary_table (Dictionary* dictionary,
                                  khash_t(StringPairTable)* table)
{
  dictionary->table = table;
}

inline Dictionary* create_dictionary (void)
{
  Dictionary* dictionary = malloc(sizeof(Dictionary));

  set_dictionary_table(dictionary, kh_init(StringPairTable));

  return dictionary;
}

inline Dictionary* get_dictionary (KLObject* dictionary_object)
{
  return dictionary_object->value.dictionary;
}

inline void set_dictionary (KLObject* dictionary_object, Dictionary* dictionary)
{
  dictionary_object->value.dictionary = dictionary;
}

inline KLObject* create_kl_dictionary (void)
{
  KLObject* dictionary_object = create_kl_object(KL_TYPE_DICTIONARY);
  Dictionary* dictionary = create_dictionary();

  set_dictionary(dictionary_object, dictionary);

  return dictionary_object;
}

inline khash_t(StringPairTable)* get_kl_dictionary_table
(KLObject* dictionary_object)
{
  return get_dictionary_table(get_dictionary(dictionary_object));
}

inline void set_kl_dictionary_table (KLObject* dictionary_object,
                                     khash_t(StringPairTable)* table)
{
  set_dictionary_table(get_dictionary(dictionary_object), table);
}

inline bool is_kl_dictionary (KLObject* object)
{
  return get_kl_object_type(object) == KL_TYPE_DICTIONARY;
}

inline long get_dictionary_count (Dictionary* dictionary)
{
  khash_t(StringPairTable)* table = get_dictionary_table(dictionary);

  return kh_size(table);
}

inline KLObject* get_kl_dictionary_count (KLObject* dictionary_object)
{
  return create_kl_number_l(get_dictionary_count(get_dictionary(dictionary_object)));
}

inline KLObject* get_dictionary_keys (Dictionary* dictionary)
{
  khash_t(StringPairTable)* table = get_dictionary_table(dictionary);
  KLObject* head_list_object = get_empty_kl_list();
  KLObject* tail_list_object = head_list_object;

  for (khiter_t i = kh_begin(table); i != kh_end(table); ++i)
    if (kh_exist(table, i)) {
      KLObject* object = get_pair_car(kh_value(table, i));
      KLObject* list_object = create_kl_list(object, get_empty_kl_list());

      if (is_empty_kl_list(head_list_object))
        head_list_object = list_object;
      else
        set_tail_kl_list(tail_list_object, list_object);

      tail_list_object = list_object;
    }

  return head_list_object;
}

inline KLObject* get_kl_dictionary_keys (KLObject* dictionary_object)
{
  return get_dictionary_keys(get_dictionary(dictionary_object));
}

inline KLObject* get_dictionary_values (Dictionary* dictionary)
{
  khash_t(StringPairTable)* table = get_dictionary_table(dictionary);
  KLObject* head_list_object = get_empty_kl_list();
  KLObject* tail_list_object = head_list_object;

  for (khiter_t i = kh_begin(table); i != kh_end(table); ++i)
    if (kh_exist(table, i)) {
      KLObject* object = get_pair_cdr(kh_value(table, i));
      KLObject* list_object = create_kl_list(object, get_empty_kl_list());

      if (is_empty_kl_list(head_list_object))
        head_list_object = list_object;
      else
        set_tail_kl_list(tail_list_object, list_object);

      tail_list_object = list_object;
    }

  return head_list_object;
}

inline KLObject* get_kl_dictionary_values (KLObject* dictionary_object)
{
  return get_dictionary_values(get_dictionary(dictionary_object));
}

#endif
