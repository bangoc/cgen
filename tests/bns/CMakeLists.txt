add_executable(bns_search_ut bns_search_ut.c)
add_executable(bns_search_gte_ut bns_search_gte_ut.c)
add_executable(bns_search_lte_ut bns_search_lte_ut.c)
add_executable(bns_search_lte_gte_1k_ut bns_search_lte_gte_1k_ut.c)

foreach (p bns_search_ut bns_search_lte_ut bns_search_gte_ut
           bns_search_lte_gte_1k_ut)
  target_link_libraries(${p} bkc)
endforeach()