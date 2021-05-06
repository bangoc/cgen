include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")

add_subdirectory(tests)

include(CTest)
add_test(NAME BNLeftRotate COMMAND bn_left_rotate_t)
add_test(NAME RBInsertDelete COMMAND rb_insert_delete_t)
add_test(NAME BNMost COMMAND bn_most_t)
add_test(NAME BNTransplant COMMAND bn_transplant_t)
add_test(NAME BNSSearch COMMAND bns_search_t)
add_test(NAME BNSSuccessorPredecessor COMMAND bns_suc_pred_t)
add_test(NAME BNForeach COMMAND bn_foreach_t)
add_test(NAME S2I COMMAND s2i_t)
add_test(NAME VVGrow COMMAND vv_size_cap_grow_t)
add_test(NAME VVPushBack COMMAND vv_push_back_t)
add_test(NAME VVSVecPushBack COMMAND vv_svec_push_back_t)