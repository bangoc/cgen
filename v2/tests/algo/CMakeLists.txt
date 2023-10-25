add_executable(perm_failover_ut perm_failover_ut.c)

foreach (p perm_failover_ut)
  target_link_libraries(${p} bkcgen)
endforeach()