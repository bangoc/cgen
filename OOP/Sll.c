#include "src/sll.c"

#include "OOP/Sll.h"

#include <stdlib.h>

Sll Sll_create() {
  sll_t sll = sll_create_list();
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
  return (SllNode)sll_create_node();
}

void Sll_free(Sll list) {
  sll_t sll = realloc(list, sizeof(struct sll_s));
  sll_free_list(sll);
}

void SllNode_free(SllNode node) {
  sll_free_node((sll_node_t)node);
}

void SllPushBack(Sll list, SllNode nn) {
  sll_push_back((sll_t)list, (sll_node_t)nn);
}

void SllPushFront(Sll list, SllNode nn) {
  sll_push_front((sll_t)list, (sll_node_t)nn);
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
  sll_pprint_node((sll_node_t)node);
}

void SllPPrint(Sll list) {
  sll_pprint_list((sll_t)list);
}

/* Giao diện gtype */

SllNodeG SllNodeG_create(gtype value) {
  SllNode tmp = New(SllNode);
  SllNodeG nn = realloc(tmp, sizeof(SllNodeGS));
  nn->value = value;
  return nn;
}

SllG SllG_create() {
  Sll tmp = New(Sll);
  SllG list = realloc(tmp, sizeof(SllGS));
  MEMBER(list, SllG, PushBack);
  MEMBER(list, SllG, PushFront);
  MEMBER(list, SllG, PopFront);
  MEMBER(list, SllG, Front);
}

void SllGPushBack(SllG list, gtype value) {
  SllNodeG nn = New(SllNodeG, value);
  Sll base = (Sll)list;
  base->PushBack(base, nn);
}

void SllGPushFront(SllG list, gtype value) {
  SllNodeG nn = New(SllNodeG, value);
  Sll base = (Sll)list;
  base->PushFront(base, nn);
}

gtype SllGPopFront(SllG list) {
  gtype value = list->Front(list);
  Sll base = (Sll)list;
  base->PopFront(base);
  return value;
}

gtype SllGFront(SllG list) {
  Sll base = (Sll)list;
  SllNode node = base->Front(base);
  gtype value = sll_node_g_value(node);
  return value;
}