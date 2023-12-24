cmake_minimum_required(VERSION 2.8)
project(cgen)

# ON by default, use -DNOWARN=ON/OFF in Cmake command to turn ON/OFF
option(BENCH_OP "Optimization (O1, O2, O3) benchmark" OFF)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_C_STANDARD 11)

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif (NOT CMAKE_BUILD_TYPE)

if (${CMAKE_BUILD_TYPE} STREQUAL Debug)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DCGEN_DEBUG")
endif()

if (${CMAKE_BUILD_TYPE} STREQUAL Release)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -w")
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-function")

add_subdirectory(tests)
include(CTest)
add_test(NAME VecIntDemo COMMAND echo 1 3 9 5 8 6 10 | vec_int_demo)
add_test(NAME VecDblDemo COMMAND echo 1.12 2.9 1.15 5.3 3.5 | vec_dbl_demo)
add_test(NAME SListIntQueueDemo COMMAND slist_int_queue_demo)
add_test(NAME TMapStrIntDemo COMMAND tmap_str_int_demo)
add_test(NAME VecStrDemo COMMAND vec_str_demo)
add_test(NAME SiDemo COMMAND echo aaa bbb ccc ddd aaa ddd eee | si_demo)
add_test(NAME SiDemo2 COMMAND echo aaa bbb ccc ddd aaa ddd eee | si_demo2)
add_test(NAME SiDemoFull COMMAND echo aaa bbb ccc ddd aaa ddd eee | si_demo_full)
add_test(NAME ListStackQueueDemo COMMAND list_stack_queue_demo)
add_test(NAME VecStackDemo COMMAND vec_stack_demo)
add_test(NAME BsearchDemo COMMAND bsearch_demo 30 28 16 3 5 7 9 11 22)
add_test(NAME CombDemo COMMAND comb_demo)
add_test(NAME PermDemo COMMAND perm_demo)
add_test(NAME QsortDemo COMMAND qsort_demo)
add_test(NAME MaxHeapIntDemo COMMAND max_heap_int_demo 10)
add_test(NAME TMapKVDemo COMMAND tmap_kv_demo)