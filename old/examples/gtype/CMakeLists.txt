add_executable(gtype_demo gtype_demo.c)
foreach (p gtype_demo)
  target_link_libraries(${p} bkcgen)
endforeach()