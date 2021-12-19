#ifndef BASE_SLL_H_
#define BASE_SLL_H_

typedef struct sll_node_s {
  struct sll_node_s *next;
} *sll_node_t;

typedef struct sll_s {
  sll_node_t front;
  sll_node_t back;
} *sll_t;

#define to_sll_node(n) ((sll_node_t)n)
#define to_sll_list(list) ((sll_t)list)

sll_node_t sll_create_node();
sll_t sll_create_list();
void sll_free_list(sll_t list);

void sll_push_back(sll_t list, sll_node_t node);
void sll_push_front(sll_t list, sll_node_t node);
void sll_pop_front(sll_t list);
sll_node_t sll_front(sll_t list);
int sll_is_empty(sll_t list);
long sll_length(sll_t list);

void sll_pprint_node(sll_node_t node);
void sll_pprint_list(sll_t list);

#define sll_traverse(cur, list) \
  for (sll_node_t cur = list->front; cur != NULL; cur = cur->next)

#define sll_free_node(n) free(n)
#endif