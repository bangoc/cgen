add_executable(vec_create_ut vec_create_ut.c)
add_executable(vec_traverse_ut vec_traverse_ut.c)
add_executable(vec_stack_ut vec_stack_ut.c)
add_executable(queue_basic_ut queue_basic_ut.c)
add_executable(slist_basic_ut slist_basic_ut.c)
add_executable(slist_stack_ut slist_stack_ut.c)
add_executable(slist_queue_ut slist_queue_ut.c)
add_executable(dlist_basic_ut dlist_basic_ut.c)
add_executable(tm_insert_traverse_failover_ut 
               tm_insert_traverse_failover_ut.c)
add_executable(tm_rand_insert_delete_ut 
               tm_rand_insert_delete_ut)
add_executable(vec_append_insert_ut vec_append_insert_ut.c)
add_executable(vec_str_failover_ut vec_str_failover_ut.c)
add_executable(vec_of_vecs_ut vec_of_vecs_ut.c)
add_executable(vec_append_long_ut vec_append_long_ut.c)
add_executable(vec_tuple_ut vec_tuple_ut.c)
add_executable(arr_int_demo_ut arr_int_demo_ut.c)
add_executable(arr_int_stack_demo arr_int_stack_demo.c)

foreach (p vec_create_ut vec_traverse_ut vec_stack_ut
           queue_basic_ut slist_basic_ut slist_stack_ut
           slist_queue_ut dlist_basic_ut
           tm_insert_traverse_failover_ut
           tm_rand_insert_delete_ut vec_append_insert_ut
           vec_str_failover_ut vec_of_vecs_ut vec_append_long_ut
           vec_tuple_ut arr_int_demo_ut arr_int_stack_demo)
  target_link_libraries(${p} bkcgen)
endforeach()