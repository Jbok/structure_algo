#pragma once
#ifndef __D_LINKED_LIST_H__
#define __D_LINKED_LIST_H__
#define TRUE 1
#define FALSE 0

typedef int LData;

struct node {
	LData data;
	LData value;
	struct node *next;
};
typedef struct node *Node;

struct linkedlist {
	Node head;
	Node cur;
	Node before;
	int numOfData;
	int(*comp)(LData d1, LData d2);
};
typedef struct linkedlist List;

void ListInit(List *plist);
void LInsert(List* plist, LData data, LData value);

int LFirst(List *plist, LData * pdata, LData *pvalue);
int LNext(List *plist, LData * pdata, LData *pvalue);

LData LRemove(List * plist);
int LCount(List *plist);

void SetSortRule(List *plist, int(*comp)(LData d1, LData d2));
#endif