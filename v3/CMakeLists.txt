cmake_minimum_required(VERSION 3.0)
project(cgen VERSION 3.0.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_C_STANDARD 17)

add_subdirectory(tests)
include (CTest)
add_test(NAME ivec_demo_ut COMMAND ivec_ut)
add_test(NAME heap_sort_ut COMMAND heap_sort_ut)
add_test(NAME q2insort_ut COMMAND q2insort_ut)
add_test(NAME binsearch_ut COMMAND binsearch_ut)
add_test(NAME hmap_demo_ut COMMAND hmap_demo_ut)
add_test(NAME ivec_sort_ut COMMAND ivec_sort_ut)
add_test(NAME ivec_put_rem_demo_ut COMMAND ivec_put_rem_demo_ut)