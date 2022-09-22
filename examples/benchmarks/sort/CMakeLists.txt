add_executable(bench_qsort_quicksort bench_qsort_quicksort.c)
add_executable(generator generator.c)
target_link_libraries(bench_qsort_quicksort bkc)


add_executable(bench_sort_g bench_fi.c ${CMAKE_SOURCE_DIR}/all.c)
target_compile_options(bench_sort_g PRIVATE -g)

add_executable(bench_sort_o1 bench_fi.c ${CMAKE_SOURCE_DIR}/all.c)
target_compile_options(bench_sort_o1 PRIVATE -O1)

add_executable(bench_sort_o2 bench_fi.c ${CMAKE_SOURCE_DIR}/all.c)
target_compile_options(bench_sort_o2 PRIVATE -O2)

add_executable(bench_sort_o3 bench_fi.c ${CMAKE_SOURCE_DIR}/all.c)
target_compile_options(bench_sort_o3 PRIVATE -O3)