add_executable(gt_treemap_ut gt_treemap_ut.c)

foreach(p gt_treemap_ut)
  target_link_libraries(${p} bkcgen)
endforeach()