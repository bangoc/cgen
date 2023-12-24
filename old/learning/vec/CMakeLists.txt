set(bkc_src ../../all.c)
add_executable(b01_read_long_ut
  b01_read_long_ut.c b01_solve.c ${bkc_src})
add_executable(b01_read_double_ut
  b01_read_double_ut.c b01_solve.c ${bkc_src})
add_executable(b01_read_lines_ut
  b01_read_lines_ut.c b01_solve.c ${bkc_src})
add_executable(b02_min_l_ut
  b02_min_l_ut.c b02_solve.c ${bkc_src})
add_executable(b02_max_d_ut
  b02_max_d_ut.c b02_solve.c ${bkc_src})
add_executable(b02_revert_ut
  b02_revert_ut.c b02_solve.c ${bkc_src})