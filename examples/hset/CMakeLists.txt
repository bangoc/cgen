add_executable(hset_demo hset_demo.c)

foreach (p hset_demo)
  target_link_libraries(${p} bkc)
endforeach()