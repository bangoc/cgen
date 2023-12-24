add_executable(gsl_demo gsl_demo.c)

foreach (p gsl_demo)
  target_link_libraries(${p} bkcgen)
endforeach()