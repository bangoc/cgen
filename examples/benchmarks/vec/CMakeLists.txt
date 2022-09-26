add_executable(bench_gvec_append bench_gvec_append.c)
foreach (p bench_gvec_append)
  target_link_libraries(${p} bkcgen)
endforeach()