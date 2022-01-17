add_executable(rbs_demo rbs_demo.c)
foreach (p rbs_demo)
  target_link_libraries(${p} bkc)
endforeach()