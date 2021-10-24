add_executable(istack_ut istack_ut.c)

foreach (p istack_ut)
  target_link_libraries(${p} bkc)
endforeach()