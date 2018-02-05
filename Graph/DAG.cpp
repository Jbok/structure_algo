#include "DLinkedList.h"
#include "ALGraph.h"
#include <stdio.h>
int visited[6];
int k = 0;
int arr[6];

void DFS_DAG(ALGraph g, int node) {
	visited[node] = 1;
	Node cur = g.adjList[node].head->next;
	while (cur != NULL) {
		if (visited[cur->data] == 0) {
			DFS_DAG(g, cur->data);
		}
		cur = cur->next;
	}
	arr[k++] = node;
}

void topologicalSort2(ALGraph g) {
	for (int i = 0; i < 6; i++) {
		visited[i] = 0;
	}

	for (int i = 0; i < 6; i++) {
		if (visited[i] == 0) {
			DFS_DAG(g, i);
		}
	}
}


int main() {
	ALGraph g;
	GraphInit(&g, 6);

	AddEdge(&g, 0, 1);
	AddEdge(&g, 1, 2);
	AddEdge(&g, 3, 1);
	AddEdge(&g, 4, 3);
	AddEdge(&g, 1, 5);


	ShowGraphEdgeInfo(&g);
	topologicalSort2(g);

}