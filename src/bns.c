#include "bns.h"

bn_node_t bns_search(bn_node_t root, const void *query,
        bn_compare_t cmp) {
  bn_node_t result;
  bns_search_inline(result, root, query, cmp);
  return result;
}

bn_node_t bns_search_gte(bn_node_t root, const void *query,
        bn_compare_t cmp) {
  bn_node_t out;
  bns_search_gte_inline(out, root, query, cmp);
  return out;
}

bn_node_t bns_search_lte(bn_node_t root, const void *query,
                          bn_compare_t cmp) {
  bn_node_t out;
  bns_search_lte_inline(out, root, query, cmp);
  return out;
}
