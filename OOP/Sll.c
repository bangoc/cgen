/*
  (C) Nguyen Ba Ngoc, 2021
*/

#include "base/src/sll.c"

#include "OOP/Sll.h"

#include <stdlib.h>

#define MEMBER(obj, Class, Method) obj->Method = Class ## Method

void SllPushBack(Sll list, SllNode nn) {
  sll_push_back((sll_t)list, (sln_t)nn);
}

void SllPushFront(Sll list, SllNode nn) {
  sll_push_front((sll_t)list, (sln_t)nn);
}

void SllPopFront(Sll list) {
  sll_pop_front((sll_t)list);
}

SllNode SllFront(Sll list) {
  return (SllNode)sll_front((sll_t)list);
}

int SllIsEmpty(Sll list) {
  return sll_is_empty((sll_t)list);
}

long SllLength(Sll list) {
  return sll_length((sll_t)list);
}

void SllPPrintNode(SllNode node) {
  sln_pprint((sln_t)node);
}

void SllPPrint(Sll list) {
  sll_pprint((sll_t)list);
}


Sll Sll_create() {
  sll_t sll = sll_create();
  Sll list = realloc(sll, sizeof(SllS));
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
  return (SllNode)sln_create();
}

void Sll_free(Sll list) {
  sll_t sll = realloc(list, sizeof(struct sll_s));
  sll_free(sll);
}

void SllNode_free(SllNode node) {
  sln_free((sln_t)node);
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
  gtype value = gsn_value(node);
  return value;
}

SllNodeGt SllNodeGt_create(gtype value) {
  SllNode tmp = New(SllNode);
  SllNodeGt nn = realloc(tmp, sizeof(SllNodeGtS));
  nn->value = value;
  return nn;
}

void SllGtForeach(SllGt list, int (*op)()) {
  sll_t sll = (sll_t)list;
  sll_traverse(cur, sll) {
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
}

#undef MEMBER