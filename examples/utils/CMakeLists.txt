add_executable(cgetline_demo cgetline_demo.c)
add_executable(cstrdup_demo cstrdup_demo.c)
add_executable(cgetline_buffsize cgetline_buffsize.c)

foreach (p cgetline_buffsize cgetline_demo cstrdup_demo)
  target_link_libraries(${p} bkcgen)
endforeach()