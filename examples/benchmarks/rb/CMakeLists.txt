set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")

# for gprof
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pg")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
add_executable(b123 bench_123.c)
add_executable(b++123 bench_123.cc)