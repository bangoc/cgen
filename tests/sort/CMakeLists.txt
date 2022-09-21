add_executable(q2sort_ut q2sort_ut.c)
add_executable(q3sort_ut q3sort_ut.c)
add_executable(quicksort_ut quicksort_ut.c)
add_executable(sort_all_identical_ut sort_all_identical_ut.c)

foreach (p q2sort_ut q3sort_ut quicksort_ut sort_all_identical_ut)
  target_link_libraries(${p} bkc)
endforeach()