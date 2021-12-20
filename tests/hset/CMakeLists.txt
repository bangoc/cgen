add_executable(hset_ut hset_ut.c)
foreach(p hset_ut)
  target_link_libraries(${p} bkc)
endforeach()