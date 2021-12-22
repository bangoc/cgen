add_executable(gvec_demo gvec_demo.c)

foreach (p gvec_demo)
  target_link_libraries(${p} bkc)
endforeach()