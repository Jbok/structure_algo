#pragma once
#ifndef __AL_GRAPH_H__
#define __AL_GRAPH_H__

#include "DLinkedList.h"

enum { A, B, C, D, E, F, G, H, I, J };

typedef struct _ual {
	int numV;		//정점의 수
	int numE;		//간선의 수
	List *adjList;	//간선의 정보
} ALGraph;

void GraphInit(ALGraph *pg, int nv);

void GraphDestroy(ALGraph *pg);

void AddEdge(ALGraph *pg, int fromV, int toV, int value);

void ShowGraphEdgeInfo(ALGraph *pg);

#endif