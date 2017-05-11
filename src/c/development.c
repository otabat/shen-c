#include "development.h"

static KLObject* symbol_counter_names_symbol_object;
static KLObject* output_symbol_count_symbol_object;
static KLObject* symbol_counter_name_list_object;

static inline KLObject* get_symbol_counter_name_list_object (void)
{
  return symbol_counter_name_list_object;
}

static inline void set_symbol_counter_name_list_object (KLObject* list_object)
{
  symbol_counter_name_list_object = list_object;
}

static inline void initialize_symbol_counter_name_list_object (void)
{
  set_symbol_counter_name_list_object(get_empty_kl_list());
}

static inline KLObject* get_symbol_counter_names_symbol_object (void)
{
  return symbol_counter_names_symbol_object;
}

static inline void register_symbol_counter_names_symbol_object (void)
{
  char* symbol_name = "symbol-counter-names";

  symbol_counter_names_symbol_object = create_kl_symbol(symbol_name);
  extend_symbol_name_table(symbol_name, symbol_counter_names_symbol_object);
}

KLObject* inject_symbol_counter (KLObject* symbol_object, KLObject* object)
{
  char* symbol_counter_symbol_name = concatenate_string(get_kl_symbol_name(symbol_object),
                                                        "-counter");
  KLObject* symbol_counter_symbol_object = create_kl_symbol(symbol_counter_symbol_name);

  extend_symbol_name_table(symbol_counter_symbol_name, symbol_counter_symbol_object);
  eval_kl_object(CONS(get_set_symbol_object(),
                      CONS(symbol_counter_symbol_object,
                           CONS(create_kl_number_l(0), get_empty_kl_list()))),
                 get_global_function_environment(),
                 get_global_variable_environment());

  KLObject* new_object =
    CONS(get_let_symbol_object(),
         CONS(create_kl_symbol("_"),
              CONS(CONS(get_set_symbol_object(),
                        CONS(symbol_counter_symbol_object,
                             CONS(CONS(get_add_symbol_object(),
                                       CONS(create_kl_number_l(1),
                                            CONS(CONS(get_value_symbol_object(),
                                                      CONS(symbol_counter_symbol_object,
                                                           get_empty_kl_list())),
                                                 get_empty_kl_list()))),
                                  get_empty_kl_list()))),
                   CONS(object, get_empty_kl_list()))));
  KLObject* list_object = CONS(symbol_counter_symbol_object, get_symbol_counter_name_list_object());

  set_symbol_counter_name_list_object(list_object);
  set_kl_symbol_variable_value(get_symbol_counter_names_symbol_object(),
                               get_symbol_counter_name_list_object());

  return new_object;
}

static inline KLObject* get_output_symbol_count_symbol_object (void) 
{
  return output_symbol_count_symbol_object;
}

static inline void register_output_symbol_count_symbol_object (void)
{
  char* symbol_name = "output-symbol-count";
  
  output_symbol_count_symbol_object = create_kl_symbol(symbol_name);
  extend_symbol_name_table(symbol_name, get_output_symbol_count_symbol_object());
}

static inline KLObject* primitive_function_output_symbol_count
(KLObject* function_object, Vector* arguments, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject* head_list_object = NULL;
  KLObject* tail_list_object = head_list_object;
  KLObject* list_object = get_symbol_counter_name_list_object();

  while (!is_empty_kl_list(list_object)) {
    KLObject* symbol_object = get_head_kl_list(list_object);
    KLObject* number_object = get_kl_symbol_variable_value(symbol_object);
    KLObject* pair_object = CONS(symbol_object, number_object);
    KLObject* new_list_object = CONS(pair_object, get_empty_kl_list());

    if (is_null(head_list_object))
      head_list_object = new_list_object;
    else
      set_tail_kl_list(tail_list_object, new_list_object);

    tail_list_object = new_list_object;
    list_object = get_tail_kl_list(list_object);
  }
  
  Vector* vector = kl_list_to_vector(head_list_object);
  KLObject** objects = get_vector_objects(vector);
  long vector_size = (long)get_vector_size(vector);

  for (long i = 0; i < vector_size; ++i)
    for (long j = i + 1; j < vector_size; ++j) {
      long i_count = get_kl_number_number_l(get_tail_kl_list(objects[i]));
      long j_count = get_kl_number_number_l(get_tail_kl_list(objects[j]));
        
      if (i_count < j_count) {
        KLObject* object = objects[i];

        objects[i] = objects[j];
        objects[j] = object;
      }
    }
   
  FILE* file = fopen("symbol_count.txt", "w");

  if (is_null(file))
    throw_kl_exception("Failed to open symbol_count.txt");

  
  for (long i = 0; i < vector_size; ++i) {
    KLObject* object = get_vector_element(vector, i);
    KLObject* symbol_object = get_head_kl_list(object);
    KLObject* number_object = get_tail_kl_list(object);
    char* symbol_name = get_kl_symbol_name(symbol_object);
    size_t symbol_name_length = strlen(symbol_name);
    long symbol_count = get_kl_number_number_l(number_object);

    symbol_name[symbol_name_length - 8] = '\0';

    fprintf(file, "%8ld %s\n", symbol_count, symbol_name);
  }

  fclose(file);

  return get_empty_kl_list();
}

static inline void register_primitive_kl_function_output_symbol_count (void)
{
  KLObject* function_object =
    create_primitive_kl_function(0, &primitive_function_output_symbol_count);

  set_kl_symbol_function(get_output_symbol_count_symbol_object(),
                         function_object);
}

void initialize_symbol_counter (void)
{
  initialize_symbol_counter_name_list_object();
  register_symbol_counter_names_symbol_object();
  register_output_symbol_count_symbol_object();
  register_primitive_kl_function_output_symbol_count();
}
