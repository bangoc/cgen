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

foreach (p vec_create_ut vec_traverse_ut vec_stack_ut
           queue_basic_ut slist_basic_ut slist_stack_ut
           slist_queue_ut dlist_basic_ut
           tm_insert_traverse_failover_ut
           tm_rand_insert_delete_ut)
  target_link_libraries(${p} bkcgen)
endforeach()