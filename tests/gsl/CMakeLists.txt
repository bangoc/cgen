add_executable(gsl_inserta_ut gsl_inserta_ut.c)
foreach (p gsl_inserta_ut)
  target_link_libraries(${p} bkcgen)
endforeach()