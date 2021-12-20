add_executable(gvec_ut gvec_ut.c)
foreach (p gvec_ut)
  target_link_libraries(${p} bkc)
endforeach()