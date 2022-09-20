add_executable(gvec_ut gvec_ut.c)
add_executable(gvec_v_ut gvec_v_ut.c)
add_executable(gvec_selsort_ut gvec_selsort_ut.c)
add_executable(gvec_insort_ut gvec_insort_ut.c)
add_executable(gvec_bubsort_ut gvec_bubsort_ut.c)
foreach (p gvec_ut gvec_v_ut gvec_selsort_ut gvec_insort_ut
    gvec_bubsort_ut)
  target_link_libraries(${p} bkc)
endforeach()