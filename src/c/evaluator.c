#include "evaluator.h"

static KLObject* eval_if_expression (KLObject* list_object,
                                     Environment* function_environment,
                                     Environment* variable_environment)
{
  check_function_argument_size(get_kl_list_size(list_object) - 1, 3);

  KLObject* cdr_object = get_tail_kl_list(list_object);
  KLObject* test_object = get_head_kl_list(cdr_object);
  KLObject* evaluated_test_object =
    eval_kl_object(test_object, function_environment, variable_environment);

  if (!is_kl_boolean(evaluated_test_object))
    throw_kl_exception("Test should be a boolean value");

  if (get_boolean(evaluated_test_object)) {
    KLObject* then_object = get_head_kl_list(get_tail_kl_list(cdr_object));

    return eval_kl_object(then_object, function_environment,
                          variable_environment);
  }

  KLObject* else_object =
    get_head_kl_list(get_tail_kl_list(get_tail_kl_list(cdr_object)));

  return eval_kl_object(else_object, function_environment, variable_environment);
}

static KLObject* eval_and_expression (KLObject* list_object,
                                      Environment* function_environment,
                                      Environment* variable_environment)
{
  check_function_argument_size(get_kl_list_size(list_object) - 1 , 2);

  KLObject* cdr_object = get_tail_kl_list(list_object);
  KLObject* test_object = get_head_kl_list(cdr_object);
  KLObject* evaluated_test_object =
    eval_kl_object(test_object, function_environment, variable_environment);

  if (!is_kl_boolean(evaluated_test_object))
    throw_kl_exception("Arguments should be boolean values");

  if (!get_boolean(evaluated_test_object))
    return get_false_boolean_object();

  KLObject* else_object = get_head_kl_list(get_tail_kl_list(cdr_object));
  KLObject* evaluated_else_object =
    eval_kl_object(else_object, function_environment, variable_environment);

  if (!is_kl_boolean(evaluated_else_object))
    throw_kl_exception("Arguments should be boolean values");

  return evaluated_else_object;
}

static KLObject* eval_or_expression (KLObject* list_object,
                                     Environment* function_environment,
                                     Environment* variable_environment)
{
  check_function_argument_size(get_kl_list_size(list_object) - 1, 2);

  KLObject* cdr_object = get_tail_kl_list(list_object);
  KLObject* test_object = get_head_kl_list(cdr_object);
  KLObject* evaluated_test_object =
    eval_kl_object(test_object, function_environment, variable_environment);

  if (!is_kl_boolean(evaluated_test_object))
    throw_kl_exception("Arguments should be boolean value");

  if (get_boolean(evaluated_test_object))
    return evaluated_test_object;

  KLObject* else_object = get_head_kl_list(get_tail_kl_list(cdr_object));
  KLObject* evaluated_else_object
    = eval_kl_object(else_object, function_environment, variable_environment);

  if (!is_kl_boolean(evaluated_else_object))
    throw_kl_exception("Arguments should be boolean value");

  return evaluated_else_object;
}

static KLObject* eval_cond_tail_expression (KLObject* list_object,
                                            Environment* function_environment,
                                            Environment* variable_environment)
{
  size_t list_object_size = get_kl_list_size(list_object);

  if (list_object_size == 0)
    throw_kl_exception("No true case found for cond");

  KLObject* case_object = get_head_kl_list(list_object);

  if (!is_kl_list(case_object))
    throw_kl_exception("Cond case should be a list");

  if (get_kl_list_size(case_object) != 2)
    throw_kl_exception("Wrong number of arguments for a case");

  KLObject* case_test_object = get_head_kl_list(case_object);
  KLObject* evaluated_case_test_object =
    eval_kl_object(case_test_object, function_environment, variable_environment);

  if (!is_kl_boolean(evaluated_case_test_object))
    throw_kl_exception("Case test should be a boolean value");

  if (get_boolean(evaluated_case_test_object)) {
    KLObject* case_then_object =
      get_head_kl_list(get_tail_kl_list(case_object));

    return eval_kl_object(case_then_object, function_environment,
                          variable_environment);
  }

  return eval_cond_tail_expression(get_tail_kl_list(list_object),
                                   function_environment,
                                   variable_environment); 
}

static KLObject* eval_cond_expression (KLObject* list_object,
                                       Environment* function_environment,
                                       Environment* variable_environment)
{
  size_t list_object_size = get_kl_list_size(list_object);

  if (list_object_size == 1)
    throw_kl_exception("Wrong number of arguments passed to cond");
  
  return eval_cond_tail_expression(get_tail_kl_list(list_object),
                                   function_environment,
                                   variable_environment);
}

static void analyze_tail_call_helper (KLObject* function_symbol_object,
                                      size_t parameter_size,
                                      KLObject* head_object, long list_level,
                                      bool is_possibly_self_call,
                                      DefunType* defun_type_ref,
                                      size_t* self_call_number_ref)
{
  if (list_level == 0) {
    if (is_non_empty_kl_list(head_object)) {
      KLObject* car_object = get_head_kl_list(head_object);
      
      if (is_kl_symbol(car_object)) {
        if (car_object == function_symbol_object ||
            car_object == get_if_symbol_object() ||
            car_object == get_cond_symbol_object() ||
            car_object == get_let_symbol_object()) {
          analyze_tail_call_helper(function_symbol_object, parameter_size,
                                   head_object, list_level +1,
                                   is_possibly_self_call, defun_type_ref,
                                   self_call_number_ref);

          return;
        }
      }
    }
    
    *defun_type_ref = DEFUN_TYPE_NON_TAIL_CALL;
    
    return;
  }

  if (*defun_type_ref == DEFUN_TYPE_NON_TAIL_CALL)
    return;

  if (is_non_empty_kl_list(head_object)) {
    KLObject* car_object = get_head_kl_list(head_object);
    KLObject* cdr_object = get_tail_kl_list(head_object);
    
    if (is_kl_symbol(car_object)) {
      if (car_object == function_symbol_object) {
        if (!is_possibly_self_call) {
          *defun_type_ref = DEFUN_TYPE_NON_TAIL_CALL;

          return ;
        }

        ++*self_call_number_ref;
          
        if (*self_call_number_ref > 1) {
          *defun_type_ref = DEFUN_TYPE_NON_TAIL_CALL;
          
          return;
        }

        size_t argument_size = get_kl_list_size(cdr_object);

        if (argument_size != parameter_size)
          throw_kl_exception("Wrong number of arguments "
                             "for function application");

        KLObject* list_object = cdr_object;

        while (is_non_empty_kl_list(list_object)) {
          KLObject* object = get_head_kl_list(list_object);

          if (is_non_empty_kl_list(object))
            analyze_tail_call_helper(function_symbol_object, parameter_size,
                                     object, list_level + 1, false,
                                     defun_type_ref, self_call_number_ref);

          list_object = get_tail_kl_list(list_object);
        }
      } else if (car_object == get_if_symbol_object()) {
        size_t argument_size = get_kl_list_size(cdr_object);

        if (argument_size != 3)
          throw_kl_exception("Wrong number of arguments for if expression");

        KLObject* cddr_object = get_tail_kl_list(cdr_object);
        KLObject* cdddr_object = get_tail_kl_list(cddr_object);
        KLObject* test_object = get_head_kl_list(cdr_object);
        KLObject* then_object = get_head_kl_list(cddr_object);
        KLObject* else_object = get_head_kl_list(cdddr_object);

        if (is_non_empty_kl_list(test_object))
          analyze_tail_call_helper(function_symbol_object, parameter_size,
                                   test_object, list_level + 1, false,
                                   defun_type_ref, self_call_number_ref);

        if (is_non_empty_kl_list(then_object) &&
            *defun_type_ref == DEFUN_TYPE_POSSIBLY_TAIL_CALL)
          analyze_tail_call_helper(function_symbol_object, parameter_size,
                                   then_object, list_level + 1,
                                   is_possibly_self_call, defun_type_ref,
                                   self_call_number_ref);

        if (is_non_empty_kl_list(else_object) &&
            *defun_type_ref == DEFUN_TYPE_POSSIBLY_TAIL_CALL)
          analyze_tail_call_helper(function_symbol_object, parameter_size,
                                   else_object, list_level + 1,
                                   is_possibly_self_call, defun_type_ref,
                                   self_call_number_ref);
    } else if (car_object == get_cond_symbol_object()) {
        size_t argument_size = get_kl_list_size(cdr_object);

        if (argument_size == 0)
          throw_kl_exception("No true case found for cond");

        KLObject* list_object = cdr_object;

        while (is_non_empty_kl_list(list_object)) {
          KLObject* case_object = get_head_kl_list(list_object);

          if (!is_kl_list(case_object))
            throw_kl_exception("Cond case should be a list");

          if (get_kl_list_size(case_object) != 2)
            throw_kl_exception("Wrong number of arguments for a case");

          KLObject* case_test_object = get_head_kl_list(case_object);
          KLObject* case_then_object =
            get_head_kl_list(get_tail_kl_list(case_object));

          if (is_non_empty_kl_list(case_test_object) &&
              *defun_type_ref == DEFUN_TYPE_POSSIBLY_TAIL_CALL)
            analyze_tail_call_helper(function_symbol_object, parameter_size,
                                     case_test_object, list_level + 1, false,
                                     defun_type_ref, self_call_number_ref);

          if (is_non_empty_kl_list(case_then_object) &&
              *defun_type_ref == DEFUN_TYPE_POSSIBLY_TAIL_CALL)
            analyze_tail_call_helper(function_symbol_object, parameter_size,
                                     case_then_object, list_level + 1,
                                     is_possibly_self_call, defun_type_ref,
                                     self_call_number_ref);
          
          list_object = get_tail_kl_list(list_object);
        }
      } else if (car_object == get_let_symbol_object()) {
        size_t argument_size = get_kl_list_size(cdr_object);

        if (argument_size != 3)
          throw_kl_exception("Wrong number of arguments for let expression");

        KLObject* cddr_object = get_tail_kl_list(cdr_object);
        KLObject* cdddr_object = get_tail_kl_list(cddr_object);
        KLObject* parameter_object = get_head_kl_list(cdr_object);
        KLObject* argument_object = get_head_kl_list(cddr_object);
        KLObject* body_object = get_head_kl_list(cdddr_object);

        if (!is_kl_symbol(parameter_object))
          throw_kl_exception("Let variable should be a symbol");

        if (is_non_empty_kl_list(argument_object))
          analyze_tail_call_helper(function_symbol_object, parameter_size,
                                   argument_object, list_level + 1, false,
                                   defun_type_ref, self_call_number_ref);

        if (is_non_empty_kl_list(body_object) &&
            *defun_type_ref == DEFUN_TYPE_POSSIBLY_TAIL_CALL)
          analyze_tail_call_helper(function_symbol_object, parameter_size,
                                   body_object, list_level + 1,
                                   is_possibly_self_call, defun_type_ref,
                                   self_call_number_ref);

        return;
      } else {
        KLObject* list_object = cdr_object;

        while (is_non_empty_kl_list(list_object)) {
          KLObject* object = get_head_kl_list(list_object);

          if (is_kl_symbol(object)) {
            if (object == function_symbol_object) {
              ++*self_call_number_ref;

              if (*self_call_number_ref > 1) {
                *defun_type_ref = DEFUN_TYPE_NON_TAIL_CALL;
                
                return;
              }
            }
          } else if (is_non_empty_kl_list(object))
            analyze_tail_call_helper(function_symbol_object, parameter_size,
                                     object, list_level + 1, false,
                                     defun_type_ref, self_call_number_ref);

          list_object = get_tail_kl_list(list_object);
        }
      }
    }
  }
}

static bool analyze_tail_call (KLObject* function_symbol_object,
                               size_t parameter_size,
                               KLObject* body_object)
{
  DefunType defun_type = DEFUN_TYPE_POSSIBLY_TAIL_CALL;
  size_t self_call_number = 0;

  analyze_tail_call_helper(function_symbol_object, parameter_size,
                           body_object, 0, true, &defun_type, &self_call_number);

  if (defun_type == DEFUN_TYPE_POSSIBLY_TAIL_CALL &&
      self_call_number == 1)
    return true;

  return false;
}

static KLObject* tail_call_to_recur_expression (KLObject* function_symbol_object,
                                                KLObject* head_list_object,
                                                bool* is_finished_ref)
{
  KLObject* car_object = get_head_kl_list(head_list_object);
  KLObject* cdr_object = get_tail_kl_list(head_list_object);

  if (is_kl_symbol(car_object)) {
    if (car_object == function_symbol_object) {
      set_head_kl_list(head_list_object, get_recur_symbol_object());
      *is_finished_ref = true;
    } else if (car_object == get_if_symbol_object()) {
      KLObject* cddr_object = get_tail_kl_list(cdr_object);
      KLObject* cdddr_object = get_tail_kl_list(cddr_object);
      KLObject* then_object = get_head_kl_list(cddr_object);
      KLObject* else_object = get_head_kl_list(cdddr_object);

      if (is_non_empty_kl_list(then_object))
        tail_call_to_recur_expression(function_symbol_object, then_object,
                                      is_finished_ref);

      if (is_non_empty_kl_list(else_object) && !*is_finished_ref)
        tail_call_to_recur_expression(function_symbol_object, else_object,
                                      is_finished_ref);
    } else if (car_object == get_cond_symbol_object()) {
      KLObject* list_object = cdr_object;

      while (is_non_empty_kl_list(list_object) && !*is_finished_ref) {
        KLObject* case_object = get_head_kl_list(list_object);
        KLObject* case_then_object =
          get_head_kl_list(get_tail_kl_list(case_object));

        if (is_non_empty_kl_list(case_then_object))
          tail_call_to_recur_expression(function_symbol_object, case_then_object,
                                        is_finished_ref);

        list_object = get_tail_kl_list(list_object);
      }
    } else if (car_object == get_let_symbol_object()) {
      KLObject* cddr_object = get_tail_kl_list(cdr_object);
      KLObject* cdddr_object = get_tail_kl_list(cddr_object);
      KLObject* body_object = get_head_kl_list(cdddr_object);

      if (is_non_empty_kl_list(body_object))
        tail_call_to_recur_expression(function_symbol_object, body_object,
                                      is_finished_ref);
    }
  }

  return head_list_object;
}

static Vector* create_auto_increment_kl_symbols (size_t size)
{
  Vector* vector = create_vector(size);
  KLObject** objects = get_vector_objects(vector);
  
  for (size_t i = 0; i < size; ++i)
    objects[i] = create_auto_increment_kl_symbol();

  return vector;
}

static KLObject* wrap_function_with_loop_expression (Vector** parameters_ref,
                                                     size_t parameter_size,
                                                     KLObject* body_object)
{
  KLObject* loop_binding_list_object = get_empty_kl_list();

  if (parameter_size > 0) {
    Vector* new_function_parameters =
      create_auto_increment_kl_symbols(parameter_size);
    Vector* loop_parameters = *parameters_ref;

    *parameters_ref = new_function_parameters;

    KLObject* head_loop_binding_list_object = loop_binding_list_object;
    KLObject* tail_loop_binding_list_object = head_loop_binding_list_object;
    KLObject** new_function_parameter_objects =
      get_vector_objects(new_function_parameters);
    KLObject** loop_parameter_objects = get_vector_objects(loop_parameters);

    for (size_t i = 0; i < parameter_size; ++i) {
      KLObject* list_object =
        create_kl_list(loop_parameter_objects[i],
                       create_kl_list(new_function_parameter_objects[i],
                                      get_empty_kl_list()));

      if (is_empty_kl_list(head_loop_binding_list_object))
        head_loop_binding_list_object = list_object;

      if (!is_empty_kl_list(tail_loop_binding_list_object))
        set_tail_kl_list(tail_loop_binding_list_object, list_object);

      tail_loop_binding_list_object = get_tail_kl_list(list_object);
    }

    loop_binding_list_object = head_loop_binding_list_object;
  }

  return create_kl_list(get_loop_symbol_object(),
                        create_kl_list(loop_binding_list_object,
                                       create_kl_list(body_object,
                                                      get_empty_kl_list())));
}

static KLObject* remove_tail_recursion (KLObject* function_symbol_object,
                                        Vector** parameters_ref,
                                        size_t parameter_size,
                                        KLObject* body_object)
{
  bool is_finished = false;

  body_object = tail_call_to_recur_expression(function_symbol_object, body_object,
                                              &is_finished);
  body_object = wrap_function_with_loop_expression(parameters_ref, parameter_size,
                                                   body_object);

  return body_object;
}

static KLObject* optimize_tail_call (KLObject* function_symbol_object,
                                     Vector** parameters_ref,
                                     size_t parameter_size,
                                     KLObject* body_object)
{
  bool is_tail_call = analyze_tail_call(function_symbol_object,
                                        parameter_size,
                                        body_object);

  if (is_tail_call)
    return remove_tail_recursion(function_symbol_object, parameters_ref,
                                 parameter_size, body_object);

  return body_object;
}

static KLObject* eval_defun_expression (KLObject* list_object)
{
  size_t list_object_size = get_kl_list_size(list_object);

  if (list_object_size != 4)
    throw_kl_exception("Wrong number of arguments for function definition");

  KLObject* cdr_object = get_tail_kl_list(list_object);
  KLObject* cddr_object = get_tail_kl_list(cdr_object);
  KLObject* cdddr_object = get_tail_kl_list(cddr_object);
  KLObject* function_symbol_object = get_head_kl_list(cdr_object);
  KLObject* parameter_list_object = get_head_kl_list(cddr_object);
  KLObject* body_object = get_head_kl_list(cdddr_object);

  if (!is_kl_symbol(function_symbol_object))
    throw_kl_exception("Function name should be a symbol");

  if (!is_kl_list(parameter_list_object))
    throw_kl_exception("Function parameters should be a list");
  
  Vector* parameters = ((is_empty_kl_list(parameter_list_object)) ?
                        NULL : kl_list_to_vector(parameter_list_object));
  size_t parameter_size =
    (is_null(parameters)) ? 0 : get_vector_size(parameters);

  check_function_user_parameters(parameters);
  body_object = optimize_tail_call(function_symbol_object, &parameters,
                                   parameter_size, body_object);

  KLObject* function_object = create_user_kl_function();
  UserFunction* user_function = get_kl_function_user_function(function_object);

  set_user_function_parameters(user_function, parameters);
  set_user_function_body(user_function, body_object);
  set_kl_symbol_function(function_symbol_object, function_object);

  return function_symbol_object;
}

static KLObject* eval_function_application_arguments
(KLObject* list_object, Environment* function_environment,
 Environment* variable_environment)
{
  KLObject* head_list_object = NULL;
  KLObject* tail_list_object = NULL;
  KLObject* object = list_object;

  while (!is_empty_kl_list(object)) {
    KLObject* evaluated_car_object =  eval_kl_object(get_head_kl_list(object),
                                                     function_environment,
                                                     variable_environment);
    KLObject* new_list_object = create_kl_list(evaluated_car_object,
                                               get_empty_kl_list());
    
    if (is_null(head_list_object))
      head_list_object = new_list_object;
    else
      set_tail_kl_list(tail_list_object, new_list_object);

    tail_list_object = new_list_object;
    object = get_tail_kl_list(object);
  }

  return (is_null(head_list_object)) ? get_empty_kl_list() : head_list_object;
}

static KLObject* eval_recur_expression (KLObject* list_object,
                                        Environment* function_environment,
                                        Environment* variable_environment)
{
  KLObject* evaluated_cdr_object =
    eval_function_application_arguments(get_tail_kl_list(list_object),
                                        function_environment,
                                        variable_environment);
  Vector* arguments = ((is_empty_kl_list(evaluated_cdr_object)) ?
                       NULL : kl_list_to_vector(evaluated_cdr_object));
  size_t argument_size = (is_null(arguments)) ? 0 : get_vector_size(arguments);
  LoopFrame* loop_frame = peek_loop_frame_stack();

  if (is_null(loop_frame))
    throw_kl_exception("Empty loop frame");
  
  Vector* parameters = get_loop_frame_parameters(loop_frame);
  size_t parameter_size = (is_null(parameters)) ? 0 : get_vector_size(parameters);

  if (argument_size != parameter_size)
    throw_kl_exception("Wrong number of arguments for recur");
  
  jmp_buf* jump_buffer = get_loop_frame_jump_buffer(loop_frame); 

  set_loop_frame_arguments(loop_frame, arguments);

  siglongjmp(*jump_buffer, 1);
}

static KLObject* eval_loop_expression (Vector* parameters,
                                       KLObject* body_object,
                                       Environment* function_environment,
                                       Environment* variable_environment)
{
  jmp_buf exception_jump_buffer;
  
  if (sigsetjmp(exception_jump_buffer, 0) == 0) {
    KLObject* exception_object = create_kl_exception();

    set_kl_exception_jump_buffer(exception_object, &exception_jump_buffer);
    push_stack(get_trapped_kl_exception_stack(), exception_object);

    KLObject* object;
    LoopFrame* loop_frame = create_loop_frame();
    LoopFramePair* loop_frame_pair = create_loop_frame_pair(loop_frame, NULL);

    set_loop_frame_parameters(loop_frame, parameters);

    while (true) {
      jmp_buf loop_jump_buffer;
      
      if (sigsetjmp(loop_jump_buffer, 0) == 0) {
        set_loop_frame_jump_buffer(loop_frame, &loop_jump_buffer);
        push_loop_frame_stack_with_frame_pair(loop_frame_pair);
        object = eval_kl_object(body_object, function_environment,
                                variable_environment);

        break;
      } else {
        loop_frame = pop_loop_frame_stack();

        Vector* frame_arguments = get_loop_frame_arguments(loop_frame);
        Vector* frame_parameters = get_loop_frame_parameters(loop_frame);

        if (is_not_null(frame_arguments) && is_not_null(frame_parameters)) {
          KLObject** argument_objects = get_vector_objects(frame_arguments);
          KLObject** parameter_objects = get_vector_objects(frame_parameters);
          size_t argument_size = get_vector_size(frame_arguments);

          for (size_t i = 0; i < argument_size; ++i) 
            extend_environment(parameter_objects[i], argument_objects[i],
                               variable_environment);
        }
      }
    }

    pop_loop_frame_stack();
    pop_stack(get_trapped_kl_exception_stack());

    return object;
  } else {
    KLObject* exception_object = pop_stack(get_trapped_kl_exception_stack());

    pop_loop_frame_stack();

    Exception* exception = get_exception(exception_object);

    throw_kl_exception(get_exception_error_message(exception));
  }

  return NULL;
}

static void eval_loop_arguments_and_parameters
(KLObject* list_object, KLObject** argument_list_object_ref,
 KLObject** parameter_list_object_ref, Environment* function_environment,
 Environment* variable_environment)
{
  if (!is_kl_list(list_object))
    throw_kl_exception("Loop bindings should be a list");

  size_t list_object_size = get_kl_list_size(list_object);

  if (list_object_size % 2 != 0)
    throw_kl_exception("Odd number of loop bindings");
  
  KLObject* head_argument_list_object = *argument_list_object_ref;
  KLObject* tail_argument_list_object = head_argument_list_object;
  KLObject* head_parameter_list_object = *parameter_list_object_ref;
  KLObject* tail_parameter_list_object = head_parameter_list_object;
  
  KLObject* object = list_object;

  while (!is_empty_kl_list(object)) {
    KLObject* parameter_object = get_head_kl_list(object);

    if (!is_kl_symbol(parameter_object))
      throw_kl_exception("Loop parameter should be a symbol");

    KLObject* cdr_object = get_tail_kl_list(object);
    KLObject* argument_object = get_head_kl_list(cdr_object);
    KLObject* evaluated_argument_object =  eval_kl_object(argument_object,
                                                          function_environment,
                                                          variable_environment);
    KLObject* new_argument_list_object = create_kl_list(evaluated_argument_object,
                                                        get_empty_kl_list());
    KLObject* new_parameter_list_object = create_kl_list(parameter_object,
                                                         get_empty_kl_list());
    
    if (is_empty_kl_list(head_argument_list_object))
      head_argument_list_object = new_argument_list_object;
    else
      set_tail_kl_list(tail_argument_list_object, new_argument_list_object);

    if (is_empty_kl_list(head_parameter_list_object))
      head_parameter_list_object = new_parameter_list_object;
    else
      set_tail_kl_list(tail_parameter_list_object, new_parameter_list_object);

    tail_argument_list_object = new_argument_list_object;
    tail_parameter_list_object = new_parameter_list_object;

    object = get_tail_kl_list(cdr_object);
  }

  *argument_list_object_ref = head_argument_list_object;
  *parameter_list_object_ref = head_parameter_list_object;
}

static KLObject* eval_kl_list_loop_expression (KLObject* list_object,
                                               Environment* function_environment,
                                               Environment* variable_environment)
{
  size_t list_object_size = get_kl_list_size(list_object);

  if (list_object_size != 3)
    throw_kl_exception("Wrong number of arguments for looop expression");

  KLObject* cdr_object = get_tail_kl_list(list_object);
  KLObject* cadr_object = get_head_kl_list(cdr_object);
  KLObject* cddr_object = get_tail_kl_list(cdr_object);
  KLObject* argument_list_object = get_empty_kl_list();
  KLObject* parameter_list_object = get_empty_kl_list();

  eval_loop_arguments_and_parameters(cadr_object, &argument_list_object,
                                     &parameter_list_object, function_environment,
                                     variable_environment);

  Vector* arguments = ((is_empty_kl_list(argument_list_object)) ? NULL :
                       kl_list_to_vector(argument_list_object));
  Vector* parameters = ((is_empty_kl_list(parameter_list_object)) ? NULL :
                        kl_list_to_vector(parameter_list_object));
  Environment* loop_function_environment = create_environment();
  Environment* loop_variable_environment = create_environment();

  set_parent_environment(loop_function_environment, function_environment);
  set_parent_environment(loop_variable_environment, variable_environment);

  if (is_not_null(arguments) && is_not_null(parameters)) {
    KLObject** argument_objects = get_vector_objects(arguments);
    KLObject** parameter_objects = get_vector_objects(parameters);
    size_t argument_size = get_vector_size(arguments);

    for (size_t i = 0; i < argument_size; ++i)
      extend_environment(parameter_objects[i], argument_objects[i],
                         loop_variable_environment);
  }

  KLObject* body_object = get_head_kl_list(cddr_object);

  return eval_loop_expression(parameters, body_object, loop_function_environment,
                              loop_variable_environment);
}

static KLObject* eval_lambda_expression (KLObject* parameter_object,
                                         KLObject* body_object,
                                         Environment* function_environment,
                                         Environment* variable_environment)
{
  if (!is_kl_symbol(parameter_object))
    throw_kl_exception("Lambda parameter should be a symbol");
  
  KLObject* function_object = create_closure_kl_function();
  Closure* closure = get_kl_function_closure(function_object);

  set_closure_parent_function_environment(closure, function_environment);
  set_closure_parent_variable_environment(closure, variable_environment);
  set_closure_parameter(closure, parameter_object);
  set_closure_body(closure, body_object);

  return function_object;
}

static KLObject* eval_kl_list_lambda_expression
(KLObject* list_object, Environment* function_environment,
 Environment* variable_environment)
{
  size_t list_object_size = get_kl_list_size(list_object);

  if (list_object_size != 3)
    throw_kl_exception("Wrong number of arguments for function definition");

  KLObject* cdr_object = get_tail_kl_list(list_object);
  KLObject* cddr_object = get_tail_kl_list(cdr_object);
  KLObject* parameter_object = get_head_kl_list(cdr_object);
  KLObject* body_object = get_head_kl_list(cddr_object);

  return eval_lambda_expression(parameter_object, body_object,
                                function_environment, variable_environment);
}

static KLObject* eval_let_expression (KLObject* list_object,
                                      Environment* function_environment,
                                      Environment* variable_environment)
{
  size_t list_object_size = get_kl_list_size(list_object);

  if (list_object_size != 4)
    throw_kl_exception("Wrong number of arguments for let expression");

  KLObject* cdr_object = get_tail_kl_list(list_object);
  KLObject* cddr_object = get_tail_kl_list(cdr_object);
  KLObject* cdddr_object = get_tail_kl_list(cddr_object);
  KLObject* argument_object = eval_kl_object(get_head_kl_list(cddr_object),
                                             function_environment,
                                             variable_environment);
  KLObject* parameter_object = get_head_kl_list(cdr_object);
  KLObject* body_object = get_head_kl_list(cdddr_object);

  if (!is_kl_symbol(parameter_object))
    throw_kl_exception("Let variable should be a symbol");
  
  KLObject* function_object = create_closure_kl_function();
  Closure* closure = get_kl_function_closure(function_object);

  set_closure_parent_function_environment(closure, function_environment);
  set_closure_parent_variable_environment(closure, variable_environment);
  set_closure_parameter(closure, parameter_object);
  set_closure_body(closure, body_object);

  Environment* closure_function_environment = create_environment();
  Environment* closure_variable_environment = create_environment();

  set_parent_environment(closure_function_environment,
                         function_environment);
  set_parent_environment(closure_variable_environment,
                         variable_environment);
  extend_environment(parameter_object, argument_object,
                     closure_variable_environment);

  return eval_kl_object(body_object, closure_function_environment,
                        closure_variable_environment);
}

static KLObject* eval_eval_kl_expression (KLObject* list_object,
                                          Environment* function_environment,
                                          Environment* variable_environment)
{
  size_t list_object_size = get_kl_list_size(list_object);

  if (list_object_size != 2)
    throw_kl_exception("Wrong number of arguments for eval-kl");

  KLObject* cdr_object = get_tail_kl_list(list_object);
  KLObject* argument_object = get_head_kl_list(cdr_object);
  KLObject* evaluated_argument_object = eval_kl_object(argument_object,
                                                       function_environment,
                                                       variable_environment);

  return eval_kl_object(evaluated_argument_object,
                        function_environment,
                        variable_environment);
}

static KLObject* eval_freeze_expression (KLObject* list_object,
                                         Environment* function_environment,
                                         Environment* variable_environment)
{
  size_t list_object_size = get_kl_list_size(list_object);

  if (list_object_size != 2)
    throw_kl_exception("Wrong number of arguments for freeze");

  KLObject* body_object = get_head_kl_list(get_tail_kl_list(list_object));
  KLObject* function_object = create_user_kl_function();
  Closure* closure = get_kl_function_closure(function_object);

  set_closure_parent_function_environment(closure, function_environment);
  set_closure_parent_variable_environment(closure, variable_environment);
  set_closure_parameter(closure, NULL);
  set_closure_body(closure, body_object);

  return function_object;
}

static KLObject* eval_primitive_function_application (KLObject* function_object,
                                                      Vector* arguments)
{
  PrimitiveFunction* primitive_function =
    get_kl_function_primitive_function(function_object);
  NativeFunction* native_function
    = get_primitive_function_native_function(primitive_function);
  
  return native_function(function_object, arguments);
}

static KLObject* eval_user_function_application (KLObject* function_object,
                                                 Vector* arguments)
{
  UserFunction* user_function = get_kl_function_user_function(function_object);
  size_t argument_size = (is_null(arguments)) ? 0 : get_vector_size(arguments);
  Vector* parameters = get_user_function_parameters(user_function);
  KLObject* body_object = get_user_function_body(user_function);
  Environment* user_function_function_environment = create_environment();
  Environment* user_function_variable_environment = create_environment();

  set_parent_environment(user_function_function_environment,
                         get_global_function_environment());
  set_parent_environment(user_function_variable_environment,
                         get_global_variable_environment());
    
  if (is_not_null(arguments) && is_not_null(parameters)) {
    KLObject** argument_objects = get_vector_objects(arguments);
    KLObject** parameter_objects = get_vector_objects(parameters);

    for (size_t i = 0; i < argument_size; ++i)
      extend_environment(parameter_objects[i], argument_objects[i],
                         user_function_variable_environment);
  }

  return eval_kl_object(body_object,
                        user_function_function_environment,
                        user_function_variable_environment);
}

static KLObject* create_kl_list_function_application (KLObject* list_object,
                                                      Vector* arguments,
                                                      long argument_index)
{
  size_t argument_size = get_vector_size(arguments);
  KLObject* head_list_object = list_object;
  KLObject* tail_list_object = list_object;

  while (argument_index < (long)argument_size) {
    KLObject* new_list_object =
      create_kl_list(get_vector_element(arguments, argument_index),
                     get_empty_kl_list());

    set_tail_kl_list(tail_list_object, new_list_object);
    tail_list_object = new_list_object;
    ++argument_index;
  }
  
  return head_list_object;
}

static KLObject* create_kl_list_lambda_expression (KLObject* parameter_object,
                                                   KLObject* body_object)
{
  return create_kl_list(get_lambda_symbol_object(),
                        create_kl_list(parameter_object,
                                       create_kl_list(body_object,
                                                      get_empty_kl_list())));
}

static KLObject* create_curried_kl_list_closure_function
(KLObject* function_symbol_object, KLObject* function_object,
 Vector* closure_parameters, long closure_parameter_index,
 Environment* function_environment, Environment* variable_environment)
{
  KLObject* closure_parameter_object =
    get_vector_element(closure_parameters, closure_parameter_index);
  size_t closure_parameter_size = get_vector_size(closure_parameters);

  KLObject* closure_body_object;

  if (closure_parameter_index >= (long)closure_parameter_size - 1)
    closure_body_object = 
      create_kl_list_function_application(create_kl_list(function_symbol_object,
                                                         get_empty_kl_list()),
                                          closure_parameters,
                                          0);
  else {
    ++closure_parameter_index;
    closure_body_object = 
      create_curried_kl_list_closure_function(function_symbol_object,
                                              function_object,
                                              closure_parameters,
                                              closure_parameter_index,
                                              function_environment,
                                              variable_environment);
  }
  
  return create_kl_list_lambda_expression(closure_parameter_object,
                                          closure_body_object);
}

static KLObject* create_curried_kl_list_primitive_function 
(KLObject* symbol_object, KLObject* function_object,
 Environment* function_environment, Environment* variable_environment)
{
  PrimitiveFunction* primitive_function =
    get_kl_function_primitive_function(function_object);
  size_t parameter_size =
    get_primitive_function_parameter_size(primitive_function);
  Vector* curried_primitive_function_parameters =
    create_auto_increment_kl_symbols(parameter_size);
  KLObject* curried_list_object =
    create_curried_kl_list_closure_function(symbol_object,
                                            function_object,
                                            curried_primitive_function_parameters,
                                            0,
                                            function_environment,
                                            variable_environment);

  return curried_list_object;
}

static KLObject* create_curried_kl_list_user_function 
(KLObject* symbol_object, KLObject* function_object,
 Environment* function_environment, Environment* variable_environment)
{
  UserFunction* user_function = get_kl_function_user_function(function_object);
  Vector* parameters = get_user_function_parameters(user_function); 
  size_t parameter_size = get_vector_size(parameters);
  Vector* curried_user_function_parameters =
    create_auto_increment_kl_symbols(parameter_size);
  KLObject* curried_list_object =
    create_curried_kl_list_closure_function(symbol_object,
                                            function_object,
                                            curried_user_function_parameters,
                                            0,
                                            function_environment,
                                            variable_environment);

  return curried_list_object;
}

static KLObject* create_kl_list_partial_function_application
(KLObject* object, Vector* arguments, long argument_index)
{
  size_t argument_size = get_vector_size(arguments);
  KLObject* argument_object = get_vector_element(arguments, argument_index);
  KLObject* new_object =
    create_kl_list(object, create_kl_list(argument_object, get_empty_kl_list()));

  ++argument_index;

  if ((long)argument_size == argument_index)
    return new_object;

  return create_kl_list_partial_function_application(new_object, arguments,
                                                     argument_index);
}

static KLObject* eval_kl_list_primitive_function_application
(KLObject* list_object, KLObject* function_object,
 Environment* function_environment, Environment* variable_environment)
{
  KLObject* evaluated_cdr_object =
    eval_function_application_arguments(get_tail_kl_list(list_object),
                                        function_environment,
                                        variable_environment);
  Vector* arguments = ((is_empty_kl_list(evaluated_cdr_object)) ?
                       NULL : kl_list_to_vector(evaluated_cdr_object));
  PrimitiveFunction* primitive_function =
    get_kl_function_primitive_function(function_object);
  size_t argument_size = (is_null(arguments)) ? 0 : get_vector_size(arguments);
  size_t parameter_size =
    get_primitive_function_parameter_size(primitive_function);

  if (argument_size != parameter_size) {
    if (parameter_size > 0) {
      KLObject* symbol_object = get_head_kl_list(list_object);
      KLObject* curried_list_object =
        create_curried_kl_list_primitive_function(symbol_object,
                                                  function_object,
                                                  function_environment,
                                                  variable_environment);
      KLObject* partial_function_object =
        eval_kl_list_lambda_expression(curried_list_object,
                                       function_environment,
                                       variable_environment);

      if (argument_size == 0)
        return partial_function_object;

      KLObject* partial_function_application_list_object =
        create_kl_list_partial_function_application(partial_function_object,
                                                    arguments,
                                                    0);

      return eval_kl_object(partial_function_application_list_object,
                            function_environment, variable_environment);
    }

    KLObject* function_symbol_object = get_head_kl_list(list_object);
    KLObject* function_appliation_list_object =
      create_kl_list(function_symbol_object, get_empty_kl_list());
    KLObject* partial_function_application_list_object
      = create_kl_list_partial_function_application(function_appliation_list_object,
                                                    arguments,
                                                    0);

    return eval_kl_object(partial_function_application_list_object,
                          function_environment, variable_environment);
  }

  return eval_primitive_function_application(function_object, arguments);
}

static KLObject* eval_kl_list_user_function_application
(KLObject* list_object, KLObject* function_object,
 Environment* function_environment, Environment* variable_environment)
{
  KLObject* evaluated_cdr_object =
    eval_function_application_arguments(get_tail_kl_list(list_object),
                                        function_environment,
                                        variable_environment);
  Vector* arguments = ((is_empty_kl_list(evaluated_cdr_object)) ?
                       NULL : kl_list_to_vector(evaluated_cdr_object));
  UserFunction* user_function = get_kl_function_user_function(function_object);
  Vector* parameters = get_user_function_parameters(user_function);
  size_t argument_size = (is_null(arguments)) ? 0 : get_vector_size(arguments);
  size_t parameter_size = (is_null(parameters)) ? 0 : get_vector_size(parameters);

  if (argument_size != parameter_size) {
    if (parameter_size > 0) {
      KLObject* symbol_object = get_head_kl_list(list_object);
      KLObject* curried_list_object =
        create_curried_kl_list_user_function(symbol_object,
                                             function_object,
                                             function_environment,
                                             variable_environment);
      KLObject* partial_function_object =
        eval_kl_list_lambda_expression(curried_list_object,
                                       function_environment,
                                       variable_environment);

      if (argument_size == 0)
        return partial_function_object;

      KLObject* partial_function_application_list_object =
        create_kl_list_partial_function_application(partial_function_object,
                                                    arguments,
                                                    0);

      return eval_kl_object(partial_function_application_list_object,
                            function_environment, variable_environment);
    }

    KLObject* function_symbol_object = get_head_kl_list(list_object);
    KLObject* function_appliation_list_object =
      create_kl_list(function_symbol_object, get_empty_kl_list());
    KLObject* partial_function_application_list_object
      = create_kl_list_partial_function_application(function_appliation_list_object,
                                                    arguments,
                                                    0);

    return eval_kl_object(partial_function_application_list_object,
                          function_environment, variable_environment);
  }

  return eval_user_function_application(function_object, arguments);
}

static KLObject* eval_symbol_function_application
(KLObject* list_object, KLObject* function_symbol_object,
 Environment* function_environment, Environment* variable_environment)
{
  KLObject* function_object = get_kl_symbol_function(function_symbol_object);

  if (is_null(function_object)) {
    char* function_symbol_name = get_kl_symbol_name(function_symbol_object);
    char* error_message =
      concatenate_string("Function ",
                         concatenate_string(function_symbol_name,
                                            " is undefined"));
    
    throw_kl_exception(error_message);
  }

  if (is_primitive_kl_function(function_object))
    return eval_kl_list_primitive_function_application(list_object,
                                                       function_object,
                                                       function_environment,
                                                       variable_environment);

  return eval_kl_list_user_function_application(list_object,
                                                function_object,
                                                function_environment,
                                                variable_environment);

  return NULL;
} 

static KLObject* eval_closure_function_application (KLObject* function_object,
                                                    KLObject* argument_object)
{
  Closure* closure = get_kl_function_closure(function_object);
  KLObject* parameter_object = get_closure_parameter(closure);
  size_t argument_size = (is_null(argument_object)) ? 0 : 1;
  size_t parameter_size = (is_null(parameter_object)) ? 0 : 1;

  check_function_argument_size(argument_size, parameter_size);

  KLObject* body_object = get_closure_body(closure);
  Environment* closure_function_environment = create_environment();
  Environment* closure_variable_environment = create_environment();

  set_parent_environment(closure_function_environment,
                         get_closure_parent_function_environment(closure));
  set_parent_environment(closure_variable_environment,
                         get_closure_parent_variable_environment(closure));

  if (parameter_size > 0)
    extend_environment(parameter_object, argument_object,
                       closure_variable_environment);

  return eval_kl_object(body_object,
                        closure_function_environment,
                        closure_variable_environment);
}

static KLObject* eval_kl_list_closure_function_application
(KLObject* list_object, KLObject* function_object,
 Environment* function_environment, Environment* variable_environment)
{
  KLObject* evaluated_cdr_object =
    eval_function_application_arguments(get_tail_kl_list(list_object),
                                        function_environment,
                                        variable_environment);
  Vector* arguments = ((is_empty_kl_list(evaluated_cdr_object)) ?
                       NULL : kl_list_to_vector(evaluated_cdr_object));
  size_t argument_size = (is_null(arguments)) ? 0 : get_vector_size(arguments);

  if (argument_size > 1) {
    KLObject* partial_function_application_list_object =
      create_kl_list_partial_function_application(function_object,
                                                  arguments,
                                                  0);

    return eval_kl_object(partial_function_application_list_object,
                          function_environment,
                          variable_environment);
  } 

  KLObject* argument_object =
    (is_empty_kl_list(evaluated_cdr_object)) ?
    NULL : get_head_kl_list(evaluated_cdr_object);
  
  return eval_closure_function_application(function_object, argument_object);
}

static KLObject* eval_trap_error_expression (KLObject* list_object,
                                             Environment* function_environment,
                                             Environment* variable_environment)
{
  size_t list_object_size = get_kl_list_size(list_object);

  if (list_object_size != 3)
    throw_kl_exception("Wrong number of arguments for trap-error");
  
  KLObject* cdr_object = get_tail_kl_list(list_object);
  jmp_buf jump_buffer;
  
  if (sigsetjmp(jump_buffer, 0) == 0) {
    KLObject* body_object = get_head_kl_list(cdr_object);
    KLObject* exception_object = create_kl_exception();

    set_kl_exception_jump_buffer(exception_object, &jump_buffer);
    push_stack(get_trapped_kl_exception_stack(), exception_object);

    KLObject* object = eval_kl_object(body_object, function_environment,
                                      variable_environment);

    pop_stack(get_trapped_kl_exception_stack());

    return object;
  } else {
    KLObject* cddr_object = get_tail_kl_list(cdr_object);
    KLObject* handler_object = get_head_kl_list(cddr_object);
    KLObject* exception_object = pop_stack(get_trapped_kl_exception_stack());
    KLObject* function_object =
      eval_kl_object(handler_object, function_environment, variable_environment);

    return eval_closure_function_application(function_object,
                                             exception_object);
  }
}

static KLObject* eval_kl_list (KLObject* list_object,
                               Environment* function_environment,
                               Environment* variable_environment)
{
  KLObject* car_object = get_head_kl_list(list_object);
  KLObject* evaluated_car_object =
    eval_kl_object(car_object, function_environment, variable_environment);

  if (is_kl_symbol(evaluated_car_object)) {
    if (evaluated_car_object == get_if_symbol_object())
      return eval_if_expression(list_object, function_environment,
                                variable_environment);
    if (evaluated_car_object == get_and_symbol_object())
      return eval_and_expression(list_object, function_environment,
                                 variable_environment);
    if (evaluated_car_object == get_or_symbol_object())
      return eval_or_expression(list_object, function_environment,
                                variable_environment);
    if (evaluated_car_object == get_cond_symbol_object())
      return eval_cond_expression(list_object, function_environment,
                                  variable_environment);
    if (evaluated_car_object == get_trap_error_symbol_object())
      return eval_trap_error_expression(list_object, function_environment,
                                        variable_environment);
    if (evaluated_car_object == get_defun_symbol_object())
      return eval_defun_expression(list_object);
    if (evaluated_car_object == get_lambda_symbol_object())
      return eval_kl_list_lambda_expression(list_object, function_environment,
                                            variable_environment);
    if (evaluated_car_object == get_let_symbol_object())
      return eval_let_expression(list_object, function_environment,
                                 variable_environment);
    if (evaluated_car_object == get_freeze_symbol_object())
      return eval_freeze_expression(list_object, function_environment,
                                    variable_environment);
    if (evaluated_car_object == get_loop_symbol_object())
      return eval_kl_list_loop_expression(list_object, function_environment,
                                          variable_environment);
    if (evaluated_car_object == get_recur_symbol_object())
      return eval_recur_expression(list_object, function_environment,
                                   variable_environment);
    if (evaluated_car_object == get_eval_kl_symbol_object())
      return eval_eval_kl_expression(list_object, function_environment,
                                     variable_environment);

    return eval_symbol_function_application(list_object,
                                            evaluated_car_object,
                                            function_environment,
                                            variable_environment);
  }

  if (is_kl_function(evaluated_car_object))
    return eval_kl_list_closure_function_application(list_object,
                                                     evaluated_car_object,
                                                     function_environment,
                                                     variable_environment);
  
  throw_kl_exception("Should be a function object");

  return NULL;
}

KLObject* eval_kl_object (KLObject* object,
                          Environment* function_environment,
                          Environment* variable_environment)
{
  if (is_non_empty_kl_list(object))
    return eval_kl_list(object, function_environment, variable_environment);
  else if (is_kl_symbol(object)) {
    if (variable_environment == get_global_variable_environment())
      return object;

    KLObject* variable_value_object =
      lookup_environment(object, variable_environment);
    
    if (is_null(variable_value_object))
      return object;

    return variable_value_object;
  }

  return object;
}
