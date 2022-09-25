set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")

# for gprof
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pg")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
add_executable(b123 bench_123.c)
add_executable(b++123 bench_123.cc)

target_link_libraries(b123 bkcgen)

# Người dùng tự bổ xung thư mục libfdr để biên dịch nếu quan tâm
#   có thể tài về ở địa chỉ https://github.com/bangoc/libfdr
#   hoặc chạy lệnh: git clone https://github.com/bangoc/libfdr.git
#   với đường dẫn hiện hành là thư mục chứa tệp này
# add_subdirectory(libfdr)
# add_executable(jrb123 bench_jrb_123.c)
# target_link_libraries(jrb123 fdr)