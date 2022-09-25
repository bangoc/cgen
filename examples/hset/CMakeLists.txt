add_executable(hset_demo hset_demo.c)
add_executable(hset_clear_demo hset_clear_demo.c)

foreach (p hset_demo hset_clear_demo)
  target_link_libraries(${p} bkcgen)
endforeach()