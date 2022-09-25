add_executable(bs_search_ut bs_search_ut.c)
add_executable(bs_search_gte_ut bs_search_gte_ut.c)
add_executable(bs_search_lte_ut bs_search_lte_ut.c)
add_executable(bs_search_lte_gte_1k_ut bs_search_lte_gte_1k_ut.c)
add_executable(bs_gtype_i_ut bs_gtype_i_ut.c)
add_executable(bs_search_lte_gte_g_ut bs_search_lte_gte_g_ut.c)

foreach (p bs_search_ut bs_search_lte_ut bs_search_gte_ut
           bs_search_lte_gte_1k_ut bs_gtype_i_ut
           bs_search_lte_gte_g_ut)
  target_link_libraries(${p} bkcgen)
endforeach()