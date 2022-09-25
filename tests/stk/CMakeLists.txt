add_executable(stk_simple_ut stk_simple_ut.c)
foreach (p stk_simple_ut)
  target_link_libraries(${p} bkcgen)
endforeach()