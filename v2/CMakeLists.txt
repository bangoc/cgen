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

add_library(bkcgen STATIC all.c)

include(CTest)
add_test(NAME VecCreate COMMAND vec_create_ut)
add_test(NAME VecTraverse COMMAND vec_traverse_ut)
add_test(NAME VecStackUt COMMAND vec_stack_ut)
add_test(NAME QueueBasicUt COMMAND queue_basic_ut)
add_test(NAME SListBasicUt COMMAND slist_basic_ut)
add_test(NAME SListStackUt COMMAND slist_stack_ut)
add_test(NAME SListQueueUt COMMAND slist_queue_ut)
add_test(NAME DListBasicUT COMMAND dlist_basic_ut)
add_test(NAME TMInsertTraverseFailOverUT 
         COMMAND tm_insert_traverse_failover_ut)
add_test(NAME TMRandInsertDeleteUT 
         COMMAND tm_rand_insert_delete_ut 10000 1000)
add_test(NAME VecAppendInsertUT COMMAND vec_append_insert_ut)
add_test(NAME VecStrFailoverUT COMMAND vec_str_failover_ut)
add_test(NAME VecOfVecsUT COMMAND vec_of_vecs_ut)
add_test(NAME PermFailOverUT COMMAND perm_failover_ut)
add_test(NAME VecAppendLongUT COMMAND vec_append_long_ut)
add_test(NAME VecTupleUT COMMAND vec_tuple_ut)
add_test(NAME ArrIntDemoUT COMMAND arr_int_demo_ut)

if (${CMAKE_BUILD_TYPE} STREQUAL Release AND
    ${CMAKE_PROJECT_NAME} STREQUAL cgen)
  set(cgen_include_dest "include")
  set(cgen_lib_dest "lib")
  set(MERGE_CMD ${CMAKE_CURRENT_BINARY_DIR}/mega/merge)
  MESSAGE(STATUS "MERGE CMD: " ${MERGE_CMD})
  execute_process(COMMAND ${MERGE_CMD}
                    ${CMAKE_CURRENT_SOURCE_DIR} all.h bkcgen.h
                  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
  execute_process(COMMAND ${MERGE_CMD}
                    ${CMAKE_CURRENT_SOURCE_DIR} all.c bkcgen.c
                  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/bkcgen.h DESTINATION "${cgen_include_dest}")
  install(TARGETS bkcgen DESTINATION "${cgen_lib_dest}")

  set(CPACK_PACKAGE_INSTALL_DIRECTORY "/usr")
  set(CPACK_GENERATOR "DEB")
  set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Nguyễn Bá Ngọc")
  set(CPACK_DEBIAN_PACKAGE_DESCRIPTION
                "Thư viện cấu trúc dữ liệu và giải thuật khái quát.")
  set(CMAKE_PROJECT_HOMEPAGE_URL "https://github.com/bangoc/cgen")
  set(CPACK_DEBIAN_PACKAGE_PRIORITY "standard")
  set(CPACK_DEBIAN_PACKAGE_SECTION "devel")

  file (READ ${CMAKE_CURRENT_SOURCE_DIR}/VERSION CGEN_VERSION)

  # Set a Package Version
  set(CPACK_PACKAGE_VERSION "${CGEN_VERSION}")
  include(CPack)

  # To build a debian package
  # cmake .. -DCMAKE_BUILD_TYPE=Release
  # make -j 2
  # make package
  #
  # To install the debian package
  # sudo dpkg -i package.deb
endif()
