cmake_minimum_required(VERSION 2.8)
project(learning)

# ON by default, use -DNOWARN=ON/OFF in Cmake command to turn ON/OFF
option(NOWARN "ON-No warnings, OFF-Tend to show all warnings" ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")

if (NOWARN)
  MESSAGE(STATUS "cgen no warnings")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -w")
else(NOWARN)
  MESSAGE(STATUS "cgen all warnings")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
endif()

add_subdirectory(vec)

include(CTest)
add_test(NAME BaiTap01ReadLong COMMAND b01_read_long_ut ${CMAKE_CURRENT_SOURCE_DIR}/vec/read_long.txt)
add_test(NAME BaiTap01ReadDouble COMMAND b01_read_double_ut ${CMAKE_CURRENT_SOURCE_DIR}/vec/read_double.txt)
add_test(NAME BaiTap01ReadLines COMMAND b01_read_lines_ut ${CMAKE_CURRENT_SOURCE_DIR}/vec/read_lines.txt)
add_test(NAME BaiTap02MinL COMMAND b02_min_l_ut)
add_test(NAME BaiTap02MaxD COMMAND b02_max_d_ut)
add_test(NAME BaiTap02Revert COMMAND b02_revert_ut)