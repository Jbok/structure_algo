#include "ArrayBaseStack.h"
#include <stdlib.h>
#include <stdio.h>

void StackInit(Stack *pstack) {
	pstack->topIndex = -1;
}

int SIsEmpty(Stack *pstack) {
	if (pstack->topIndex == -1)
		return TRUE;
	else
		return FALSE;
}

void SPush(Stack *pstack, Data data) {
	pstack->topIndex++;
	pstack->stackArr[pstack->topIndex] = data;
}

Data SPop(Stack *pstack) {
	if (SIsEmpty(pstack)) {
		printf("Stack Memory Error!\n");
		exit(-1);
	}
	Data data = pstack->stackArr[pstack->topIndex];
	pstack->stackArr[pstack->topIndex--] = NULL;
	return data;
}

Data SPeek(Stack *pstack) {
	if (SIsEmpty(pstack)) {
		printf("Stack Memory Error!\n");
		exit(-1);
	}
	return pstack->stackArr[pstack->topIndex];
}