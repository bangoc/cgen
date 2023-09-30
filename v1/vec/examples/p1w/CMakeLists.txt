add_executable(p1wi_demo p1wi_demo.c)
add_executable(p1wi_root p1wi_root.c)
add_executable(p1wi_clear_demo p1wi_clear_demo.c)

foreach (p p1wi_demo p1wi_root p1wi_clear_demo)
  target_link_libraries(${p} bkcgen)
endforeach()