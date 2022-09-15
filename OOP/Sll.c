/* (C) Nguyen Ba Ngoc, 2021 */

#include "all.h"

#include "OOP/Sll.h"

#include <stdlib.h>

#define MEMBER(obj, Class, Method) obj->Method = Class ## Method

void SllPushBack(Sll list, SllNode nn) {
  sll_push_back((struct sllist *)list, (struct slnode *)nn);
}

void SllPushFront(Sll list, SllNode nn) {
  sll_push_front((struct sllist *)list, (struct slnode *)nn);
}

void SllPopFront(Sll list) {
  sll_pop_front((struct sllist *)list);
}

SllNode SllFront(Sll list) {
  return (SllNode)sll_front((struct sllist *)list);
}

int SllIsEmpty(Sll list) {
  return sll_is_empty((struct sllist *)list);
}

long SllLength(Sll list) {
  return sll_length((struct sllist *)list);
}

void SllPPrintNode(SllNode node) {
  sll_node_print_address((struct slnode *)node);
}

void SllPPrint(Sll list) {
  sll_pprint((struct sllist *)list, sll_node_print_address);
}


Sll Sll_create() {
  struct sllist *base = sll_create_list();
  Sll list = realloc(base, sizeof(SllS));
  MEMBER(list, Sll, PushBack);
  MEMBER(list, Sll, PushFront);
  MEMBER(list, Sll, PopFront);
  MEMBER(list, Sll, Front);
  MEMBER(list, Sll, IsEmpty);
  MEMBER(list, Sll, Length);
  MEMBER(list, Sll, PPrintNode);
  MEMBER(list, Sll, PPrint);
  return list;
}

SllNode SllNode_create() {
  return (SllNode)sll_create_node();
}

void Sll_free(Sll list) {
  struct sllist *base = realloc(list, sizeof(struct sllist));
  sll_free(base);
}

void SllNode_free(SllNode node) {
  free((struct slnode *)node);
}

/* Giao diện gtype */

void SllGt_free(SllGt list) {
  Sll tmp = realloc(list, sizeof(SllS));
  Delete(Sll, tmp);
}

void SllGtPushBack(SllGt list, gtype value) {
  SllNodeGt nn = New(SllNodeGt, value);
  Sll base = (Sll)list;
  base->PushBack(base, nn);
}

void SllGtPushFront(SllGt list, gtype value) {
  SllNodeGt nn = New(SllNodeGt, value);
  Sll base = (Sll)list;
  base->PushFront(base, nn);
}

gtype SllGtPopFront(SllGt list) {
  gtype value = list->Front(list);
  Sll base = (Sll)list;
  base->PopFront(base);
  return value;
}

gtype SllGtFront(SllGt list) {
  Sll base = (Sll)list;
  SllNode node = base->Front(base);
  gtype value = ((SllNodeGt)node)->value;
  return value;
}

SllNodeGt SllNodeGt_create(gtype value) {
  SllNode tmp = New(SllNode);
  SllNodeGt nn = realloc(tmp, sizeof(SllNodeGtS));
  nn->value = value;
  return nn;
}

void SllGtForeach(SllGt list, int (*op)()) {
  struct sllist *base = (struct sllist *)list;
  sll_traverse(cur, base) {
    SllNodeGt gn = (SllNodeGt)cur;
    if (op(gn->value)) {
      break;
    }
  }
}

SllGt SllGt_create() {
  Sll tmp = New(Sll);
  SllGt list = realloc(tmp, sizeof(SllGtS));
  MEMBER(list, SllGt, PushBack);
  MEMBER(list, SllGt, PushFront);
  MEMBER(list, SllGt, PopFront);
  MEMBER(list, SllGt, Front);
  MEMBER(list, SllGt, Foreach);
  return list;
}

#undef MEMBER