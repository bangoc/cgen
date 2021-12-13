add_executable(hmap_demo hmap_demo.c)
foreach (p hmap_demo)
  target_link_libraries(${p} bkc)
endforeach()