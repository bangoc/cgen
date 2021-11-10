add_executable(rbs_i_ut rbs_i_ut.c)

foreach (p rbs_i_ut)
  target_link_libraries(${p} bkc)
endforeach()