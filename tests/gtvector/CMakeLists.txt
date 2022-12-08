add_executable(gtv_size_cap_grow_ut size_cap_grow_ut.c)
add_executable(gtv_push_back_ut push_back_ut.c)
add_executable(svec_push_back_ut svec_push_back_ut.c)
add_executable(ivec_push_back_ut ivec_push_back_ut.c)

foreach (p gtv_size_cap_grow_ut gtv_push_back_ut
    svec_push_back_ut ivec_push_back_ut)
  target_link_libraries(${p} bkcgen)
endforeach()