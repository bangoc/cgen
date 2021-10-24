add_executable(gt_list1_ut gt_list1_ut.c)

foreach (p gt_list1_ut)
  target_link_libraries(${p} bkc)
endforeach()