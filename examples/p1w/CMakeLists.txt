add_executable(p1wi_demo p1wi_demo.c)
add_executable(p1wi_root p1wi_root.c)

foreach (p p1wi_demo p1wi_root)
  target_link_libraries(${p} bkc)
endforeach()