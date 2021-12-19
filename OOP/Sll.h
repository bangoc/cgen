#ifndef OOP_SLL_H_
#define OOP_SLL_H_

/*
  (C) Nguyen Ba Ngoc, 2021
*/

#include "base/core.h"

#include "cgen.h"

typedef struct {
  struct sll_node_s sll_node;
} SllNodeS, *SllNode;

typedef struct {
  struct sll_s sll;
  void (*PushBack)();
  void (*PushFront)();
  void (*PopFront)();
  SllNode (*Front)();
  int (*IsEmpty)();
  long (*Length)();
  void (*PPrintNode)();
  void (*PPrint)();
} SllS, *Sll;

Sll Sll_create();
SllNode SllNode_create();
void Sll_free(Sll list);
void SllNode_free(SllNode node);

#include "gtype.h"

typedef struct {
  SllNodeS base;
  gtype value;
} SllNodeGtS, *SllNodeGt;

typedef struct {
  SllS base;
  void (*PushBack)();
  void (*PushFront)();
  gtype (*PopFront)();
  gtype (*Front)();
  void (*Foreach)();
} SllGtS, *SllGt;

SllNodeGt SllNodeGt_create(gtype value);
SllGt SllGt_create();
void SllGt_free(SllGt list);

#endif  // OOP_SLL_H_