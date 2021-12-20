#ifndef BASE_SLL_H_
#define BASE_SLL_H_

typedef struct sln_s {
  struct sln_s *next;
} *sln_t;

typedef struct sll_s {
  sln_t front;
  sln_t back;
} *sll_t;

#define to_sln(n) ((sln_t)(n))
#define sln_free(n) free(n)

#define to_sll(list) ((sll_t)(list))
#define sll_front(list) (to_sll(list)->front)
#define sll_back(list) (to_sll(list)->back)

sln_t sln_create();
sll_t sll_create();
void sll_free(sll_t list);

void sll_push_back(sll_t list, sln_t node);
void sll_push_front(sll_t list, sln_t node);
void sll_pop_front(sll_t list);
int sll_is_empty(sll_t list);
long sll_length(sll_t list);

void sln_pprint(sln_t node);
void sll_pprint(sll_t list);

#define sll_traverse(cur, list) \
  for (sln_t cur = list->front; cur != NULL; cur = cur->next)

#endif