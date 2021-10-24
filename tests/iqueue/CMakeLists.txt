add_executable(iqueue_ut iqueue_ut.c)

foreach (p iqueue_ut)
  target_link_libraries(${p} bkc)
endforeach()