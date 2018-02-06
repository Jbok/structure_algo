#include "DLinkedList.h"
#include <stdlib.h>

void ListInit(List *plist) {
	plist->head = (Node)malloc(sizeof(node));
	plist->head->next = NULL;
	plist->comp = NULL;
	plist->numOfData = 0;
}

void FInsert(List *plist, LData data, LData value) {
	Node newnode = (Node)malloc(sizeof(node));
	newnode->data = data;
	newnode->value = value;
	newnode->next = plist->head->next;
	plist->head->next = newnode;

	(plist->numOfData)++;
}

void SInsert(List *plist, LData data, LData value) {

}

void LInsert(List* plist, LData data, LData value) {
	if (plist->comp == NULL) {
		FInsert(plist, data, value);
	}
	else {
		SInsert(plist, data, value);
	}
}

int LFirst(List *plist, LData * pdata, LData *pvalue) {
	if (plist->head->next == NULL) {
		return FALSE;
	}

	plist->before = plist->head;
	plist->cur = plist->head->next;

	*pdata = plist->cur->data;
	*pvalue = plist->cur->value;
	return TRUE;
}
int LNext(List *plist, LData * pdata, LData *pvalue) {
	if (plist->cur->next == NULL)
		return FALSE;
	plist->before = plist->cur;
	plist->cur = plist->cur->next;

	*pdata = plist->cur->data;
	*pvalue = plist->cur->value;
	return TRUE;
}

LData LRemove(List * plist) {
	Node rpos = plist->cur;
	LData rdata = rpos->data;

	plist->before->next = plist->cur->next;
	plist->cur = plist->before;

	free(rpos);
	(plist->numOfData)--;
	return rdata;
}

int LCount(List *plist) {
	return plist->numOfData;
}

void SetSortRule(List *plist, int(*comp)(LData d1, LData d2)) {

}

