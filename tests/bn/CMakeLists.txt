add_executable(bn_most_ut bn_most_ut.c)
add_executable(bn_transplant_ut bn_transplant_ut.c)
add_executable(bn_next_prev_inorder_ut bn_next_prev_inorder_ut.c)
add_executable(bn_foreach_ut bn_foreach_ut.c)
add_executable(bn_similar_tree_ut bn_similar_tree_ut.c)
add_executable(bn_edge_height_ut bn_edge_height_ut.c)
add_executable(bn_insert_ut bn_insert_ut.c)

foreach(p bn_most_ut bn_transplant_ut
          bn_next_prev_inorder_ut
          bn_foreach_ut bn_similar_tree_ut
          bn_edge_height_ut
          bn_insert_ut)
  target_link_libraries(${p} bkcgen)
endforeach()