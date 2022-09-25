add_executable(sll_ut sll_ut.c)
add_executable(sll_g_ut sll_g_ut.c)
add_executable(sll_l_queue_ut sll_l_queue_ut.c)
add_executable(sll_l_stack_ut sll_l_stack_ut.c)

foreach (p sll_ut sll_g_ut sll_l_queue_ut sll_l_stack_ut)
  target_link_libraries(${p} bkcgen)
endforeach()