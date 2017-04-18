#include "kl.h"

static KLObject* empty_list_object = NULL;

KLType get_kl_object_type (KLObject* object)
{
  return object->type;
}

void set_kl_object_type (KLObject* object, KLType type)
{
  object->type = type;
}

KLObject* create_kl_object (KLType type)
{
  KLObject* object = malloc(sizeof(KLObject));

  set_kl_object_type(object, type);

  return object;
}

bool is_null (void* object)
{
  return object == NULL;
}

bool is_not_null (void* object)
{
  return object != NULL;
}

KLObject* get_pair_car (Pair* pair)
{
  return pair->car;
}

void set_pair_car (Pair* pair, KLObject* object)
{
  pair->car = object;
}

KLObject* get_pair_cdr (Pair* pair)
{
  return pair->cdr;
}

void set_pair_cdr (Pair* pair, KLObject* object)
{
  pair->cdr = object;
}

Pair* create_pair (KLObject* car_object, KLObject* cdr_object)
{
  Pair* pair = malloc(sizeof(Pair));

  set_pair_car(pair, car_object);
  set_pair_cdr(pair, cdr_object);

  return pair;
}

void initialize_empty_kl_list (void)
{
  KLObject* list_object = create_kl_object(KL_TYPE_LIST);

  list_object->value.pair = create_pair(list_object, list_object);
  
  empty_list_object = list_object;
}

KLObject* get_empty_kl_list (void)
{
  return empty_list_object;
}

bool is_empty_kl_list (KLObject* object)
{
  return object == get_empty_kl_list();
}
