add_executable(gvec_ut gvec_ut.c)
add_executable(gvec_v_ut gvec_v_ut.c)
add_executable(gvec_selsort_ut gvec_selsort_ut.c)
add_executable(gvec_insort_ut gvec_insort_ut.c)
add_executable(gvec_bubsort_ut gvec_bubsort_ut.c)
add_executable(gvec_mem_resize_ut gvec_mem_resize_ut.c)
add_executable(gvec_fill_ut gvec_fill_ut.c)
add_executable(gvec_create_full_ut gvec_create_full_ut.c)
foreach (p gvec_ut gvec_v_ut gvec_selsort_ut gvec_insort_ut
    gvec_bubsort_ut gvec_mem_resize_ut gvec_fill_ut
    gvec_create_full_ut)
  target_link_libraries(${p} bkcgen)
endforeach()