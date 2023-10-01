add_executable(system_gvec_demo system_gvec_demo.c)
foreach (p system_gvec_demo)
  target_link_libraries(${p} bkcgen)
endforeach()