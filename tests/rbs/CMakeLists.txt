add_executable(rbs_i_ut rbs_i_ut.c)
add_executable(rbs_str_ut rbs_str_ut.c)

foreach (p rbs_i_ut rbs_str_ut)
  target_link_libraries(${p} bkc)
endforeach()