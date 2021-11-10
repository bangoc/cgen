add_executable(rbm_si_demo rbm_si_demo.c)
foreach (p rbm_si_demo)
  target_link_libraries(${p} bkc)
endforeach()