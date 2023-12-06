add_executable(vec_int_demo vec_int_demo.c)
foreach(p vec_int_demo)
  target_link_libraries(${p} bkcgen)
endforeach()