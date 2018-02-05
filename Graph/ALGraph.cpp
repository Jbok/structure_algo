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

void AddEdge(ALGraph *pg, int fromV, int toV) {
	pg->numE++;
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
