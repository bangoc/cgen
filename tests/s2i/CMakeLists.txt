add_executable(s2i_ut s2i_ut.c)
add_executable(s2i_ut2 s2i_ut2.c)
add_executable(s2i_insert_dup_ut s2i_insert_dup_ut.c)
add_executable(s2i_set_dup_ut s2i_set_dup_ut.c)

foreach(p s2i_ut s2i_ut2 s2i_insert_dup_ut s2i_set_dup_ut)
  target_link_libraries(${p} bkcgen)
endforeach()