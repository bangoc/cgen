add_executable(s2w_ut s2w_ut.c)
foreach (p s2w_ut)
  target_link_libraries(${p} bkcgen)
endforeach()