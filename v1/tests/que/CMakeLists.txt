add_executable(que_simple_ut que_simple_ut.c)
foreach (p que_simple_ut)
  target_link_libraries(${p} bkcgen)
endforeach()