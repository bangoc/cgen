#ifndef OOSLL_H_
#define OOSLL_H_

#include "core.h"

#include "sll.h"

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

void SllPushBack(Sll list, SllNode nn);
void SllPushFront(Sll list, SllNode nn);
void SllPopFront(Sll list);
SllNode SllFront(Sll list);
int SllIsEmpty(Sll list);
long SllLength(Sll list);
void SllPPrintNode(SllNode node);
void SllPPrint(Sll list);

#define MEMBER(obj, Class, Method) obj->Method = Class ## Method

#include "gtype.h"

typedef struct {
  SllNodeS base;
  gtype value;
} SllNodeGS, *SllNodeG;

typedef struct {
  SllS base;
  void (*PushBack)();
  void (*PushFront)();
  gtype (*PopFront)();
  gtype (*Front)();
  void (*PPrint)();
} SllGS, *SllG;

SllNodeG SllNodeG_create(gtype value);
SllG SllG_create();

void SllGPushBack(SllG list, gtype value);
void SllGPushFront(SllG list, gtype value);
gtype SllGPopFront(SllG list);
gtype SllGFront(SllG list);
void SllGPPrint(SllG list);

#endif  // OOSLL_H_