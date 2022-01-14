add_executable(rbm_rand_i_ut rbm_rand_i_ut.c)

foreach (p rbm_rand_i_ut)
  target_link_libraries(${p} bkc)
endforeach()