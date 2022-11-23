add_executable(ddemo bs_demo_with_type_double.c)
foreach (p ddemo)
  target_link_libraries(${p} bkcgen)
endforeach()