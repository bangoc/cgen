add_executable(p1w_ut p1w_ut.c)

foreach (p p1w_ut)
  target_link_libraries(${p} bkcgen)
endforeach()