#include <stdio.h>
#include <malloc.h>
#include "ALGraph.h"

void GraphInit(ALGraph *pg, int nv) {
	pg->numV = nv;
	pg->numE = 0;

	pg->adjList = (List*)malloc(sizeof(List)*nv);
	for (int i = 0; i < nv; i++) {
		ListInit(&(pg->adjList[i]));
	}
	return;
}

void GraphDestroy(ALGraph *pg) {
	if (pg->adjList == NULL)
		free(pg->adjList);
}

void AddEdge(ALGraph *pg, int fromV, int toV, int value) {
	pg->numE++;
	LInsert(&(pg->adjList[fromV]), toV, value);
	LInsert(&(pg->adjList[toV]), fromV, value);
}

void ShowGraphEdgeInfo(ALGraph *pg) {
	int vx;
	int value;
	for (int i = 0; i < pg->numV; i++) {
		printf("%c와 연결된 정점: \n", i + 'A');

		if (LFirst(&(pg->adjList[i]), &vx, &value)) {
			printf("%c(%d) ", vx + 'A', value);
			
			while (LNext(&(pg->adjList[i]), &vx, &value))
				printf("%c(%d) ", vx + 'A', value);
		}
		printf("\n");
	}
}
