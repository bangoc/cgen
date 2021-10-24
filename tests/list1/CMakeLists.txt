add_executable(list1_ut list1_ut.c)

foreach (p list1_ut)
  target_link_libraries(${p} bkc)
endforeach()