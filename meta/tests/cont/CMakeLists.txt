add_executable(vec_int_demo vec_int_demo.c)
add_executable(vec_dbl_demo vec_dbl_demo.c)
add_executable(slist_int_queue_demo slist_int_queue_demo.c)
add_executable(tmap_str_int_demo tmap_str_int_demo.c)
add_executable(vec_str_demo vec_str_demo.c)
foreach(p vec_int_demo vec_dbl_demo slist_int_queue_demo tmap_str_int_demo
    vec_str_demo)
  target_link_libraries(${p} bkcgen)
endforeach()