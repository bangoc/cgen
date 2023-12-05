add_executable(gtype_cons_ut gtype_cons_ut.c)
foreach(p gtype_cons_ut)
  target_link_libraries(${p} bkcgen)
endforeach()