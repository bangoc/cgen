add_executable(dll_generic_ut dll_generic_ut.c)
add_executable(dll_int_ut dll_int_ut.c)
add_executable(dll_gtype_ut dll_gtype_ut.c)

foreach (p dll_generic_ut dll_int_ut dll_gtype_ut)
  target_link_libraries(${p} bkcgen)
endforeach()