#include "Prim.h"

int main() {
	ALGraph *ptr_g = (ALGraph*)malloc(sizeof(ALGraph));
	GraphInit(ptr_g, NODE_SIZE);

	AddEdge(ptr_g, 0, 1, 4);
	AddEdge(ptr_g, 0, 7, 8);
	AddEdge(ptr_g, 1, 2, 8);
	AddEdge(ptr_g, 1, 7, 7);
	AddEdge(ptr_g, 2, 3, 7);
	AddEdge(ptr_g, 2, 8, 2);
	AddEdge(ptr_g, 2, 5, 4);
	AddEdge(ptr_g, 3, 5, 14);
	AddEdge(ptr_g, 3, 4, 9);
	AddEdge(ptr_g, 4, 5, 10);
	AddEdge(ptr_g, 5, 6, 2);
	AddEdge(ptr_g, 6, 8, 6);
	AddEdge(ptr_g, 6, 7, 1);
	AddEdge(ptr_g, 7, 8, 7);

	ShowGraphEdgeInfo(ptr_g);

	prim(ptr_g);
	GraphDestroy(ptr_g);
}