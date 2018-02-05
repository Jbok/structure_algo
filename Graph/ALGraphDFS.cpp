#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include "ArrayBaseStack.h"
#include "ALGraphDFS.h"

int VisitedVertex(ALGraph *pg, int visitV) {
	if (pg->visitInfo[visitV] == 0) {
		pg->visitInfo[visitV] = 1;
		printf("%c ", visitV + 'A');
		return TRUE;
	}
	return FALSE;
}

void DFShowGraphVertex(ALGraph *pg, int startV) {
	Stack* stack= (Stack*)malloc(sizeof(Stack));
	StackInit(stack);
	int visitV = startV;
	int nextV;

	VisitedVertex(pg, visitV);
	SPush(stack, visitV);

	while (LFirst(&(pg->adjList[visitV]), &nextV) == TRUE) {
		int visitFlag = FALSE;

		if (VisitedVertex(pg, nextV) == TRUE) {
			SPush(stack, visitV);
			visitV = nextV;
			visitFlag = TRUE;
		}
		else {
			while (LNext(&(pg->adjList[visitV]), &nextV) == TRUE) {
				if (VisitedVertex(pg, nextV) == TRUE) {
					SPush(stack, visitV);
					visitV = nextV;
					visitFlag = TRUE;
					break;
				}
			}
		}

		if (visitFlag == FALSE) {
			if (SIsEmpty(stack) == TRUE)
				break;
			else
				visitV = SPop(stack);
		}
	}
}

void GraphInit(ALGraph *pg, int nv) {
	pg->numV = nv;
	pg->numE = 0;
	pg->adjList = (List*)malloc(sizeof(List)*nv);
	pg->visitInfo = (int *)malloc(sizeof(int)*pg->numV);
	memset(pg->visitInfo, 0, sizeof(int)*pg->numV);

	for (int i = 0; i < nv; i++) {
		ListInit(&(pg->adjList[i]));
	}
	return;
}

void GraphDestory(ALGraph *pg) {
	if (pg->adjList != NULL) {
		free(pg->adjList);
	}

	if (pg->visitInfo != NULL) {
		free(pg->visitInfo);
	}
}

void AddEdge(ALGraph *pg, int fromV, int toV) {
	pg->numE++;
	LInsert(&(pg->adjList[toV]), fromV);
	LInsert(&(pg->adjList[fromV]), toV);
}

void ShowGraphEdgeInfo(ALGraph *pg) {
	int vx;

	for (int i = 0; i < pg->numV; i++) {
		printf("%c와 연결된 정점: \n", i + 'A');

		if (LFirst(&(pg->adjList[i]), &vx)) {
			printf("%c ", vx + 'A');

			while (LNext(&(pg->adjList[i]), &vx))
				printf("%c ", vx + 'A');
		}
		printf("\n");
	}
}
