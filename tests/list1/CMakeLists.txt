add_executable(list1_ut list1_ut.c)
add_executable(gt_list1_ut gt_list1_ut.c)
add_executable(iqueue_ut iqueue_ut.c)
add_executable(istack_ut istack_ut.c)

foreach (p list1_ut gt_list1_ut iqueue_ut istack_ut)
  target_link_libraries(${p} bkc)
endforeach()