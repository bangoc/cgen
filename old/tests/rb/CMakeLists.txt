add_executable(bn_left_rotate_ut bn_left_rotate_ut.c)
add_executable(rb_insert_delete_ut rb_insert_delete_ut.c)
add_executable(rb_build_ut rb_build_ut.c)
add_executable(rb_delete_ut rb_delete_ut.c)
add_executable(rb_delete_similar_ut rb_delete_similar_ut.c)
add_executable(rb_is_valid_ut rb_is_valid_ut.c)
add_executable(rb_insert_delete_1k_ut rb_insert_delete_1k_ut.c)
add_executable(rb_rand_insert_delete_ut rb_rand_insert_delete_ut.c)
add_executable(rb_insert_delete_duplicates_ut
                          rb_insert_delete_duplicates_ut.c)

foreach (p bn_left_rotate_ut rb_insert_delete_ut rb_build_ut
          rb_delete_ut rb_delete_similar_ut rb_is_valid_ut
          rb_insert_delete_1k_ut rb_rand_insert_delete_ut
          rb_insert_delete_duplicates_ut)
  target_link_libraries(${p} bkcgen)
endforeach()