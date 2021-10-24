add_executable(sll_ut sll_ut.c)
add_executable(gsl_ut gsl_ut.c)
add_executable(iqueue_ut iqueue_ut.c)
add_executable(istack_ut istack_ut.c)

foreach (p sll_ut gsl_ut iqueue_ut istack_ut)
  target_link_libraries(${p} bkc)
endforeach()