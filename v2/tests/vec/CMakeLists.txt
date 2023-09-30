add_executable(gvec_create_ut gvec_create_ut.c)

foreach (p gvec_create_ut)
  target_link_libraries(${p} bkcgen)
endforeach()