add_executable(p1wi_demo p1wi_demo.c)

foreach (p p1wi_demo)
  target_link_libraries(${p} bkc)
endforeach()