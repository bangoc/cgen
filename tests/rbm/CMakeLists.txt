add_executable(rbm_rand_i_ut rbm_rand_i_ut.c)
add_executable(rbm_gvec_ut rbm_gvec_ut.c)
add_executable(rbm_hmap_ut rbm_hmap_ut.c)

foreach (p rbm_rand_i_ut rbm_gvec_ut rbm_hmap_ut)
  target_link_libraries(${p} bkc)
endforeach()