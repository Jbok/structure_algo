#include "ALGraph.h"
#include <stdio.h>
#include <malloc.h>
#define SIZE 4
#define EDGE 6
struct edge {
	int v1;
	int v2;
	int value;
};

typedef struct edge Edge;

int p[SIZE];
Edge temp[EDGE * 2];
Edge edge[EDGE];

void SaveEdge(ALGraph *pg) {
	int vx;
	int value;
	int index = 0;
	for (int i = 0; i < pg->numV; i++) {
		if (LFirst(&(pg->adjList[i]), &vx, &value)) {
			temp[index].v1 = i;
			temp[index].v2 = vx;
			temp[index].value = value;
			index++;
			while (LNext(&(pg->adjList[i]), &vx, &value)) {
				temp[index].v1 = i;
				temp[index].v2 = vx;
				temp[index].value = value;
				index++;
			}
		}
	}
}

int partition(int left, int right) {
	int pivot, low, high;
	low = left;
	high = right + 1;
	pivot = temp[left].value;
	do {
		do
			low++;
		while (temp[low].value < pivot);
		do
			high--;
		while (temp[high].value > pivot);
		if (low < high) {
			Edge t = temp[low];
			temp[low] = temp[high];
			temp[high] = t;
		}
	} while (low < high);

	Edge t = temp[left];
	temp[left] = temp[high];
	temp[high] = t;
	return high;
}

void QuickSortEdge(int left, int right) {
	if (left < right) {
		int pivot = partition(left, right);
		QuickSortEdge(left, pivot - 1);
		QuickSortEdge(pivot + 1, right);
	}
	for (int i = 0; i < 2 * EDGE; i += 2) {
		edge[i / 2] = temp[i];
	}
}

int find_set(int x) {
	if (x != p[x]) {
		p[x] = find_set(p[x]);
	}
	return p[x];
}

void union_set(int u, int v) {
	int x = find_set(u);
	int y = find_set(v);
	p[x] = y;
}

void kruskal(ALGraph *ptr_g) {
	for (int i = 0; i < SIZE; i++) {
		p[i] = i;
	}
	SaveEdge(ptr_g);
	QuickSortEdge(0, 2 * EDGE - 1);

	for (int i = 0; i < EDGE; i++) {
		if (find_set(edge[i].v1) != find_set(edge[i].v2))
			printf("(%d,%d) w:%d\n", edge[i].v1, edge[i].v2, edge[i].value);
			union_set(edge[i].v1, edge[i].v2);
	}

}




int main() {
	ALGraph *ptr_g = (ALGraph*)malloc(sizeof(ALGraph));
	GraphInit(ptr_g, SIZE);

	AddEdge(ptr_g, 0, 1, 554);
	AddEdge(ptr_g, 0, 2, 553);
	AddEdge(ptr_g, 0, 3, 55);
	AddEdge(ptr_g, 1, 2, 11);
	AddEdge(ptr_g, 1, 3, 7);
	AddEdge(ptr_g, 2, 3, 3);


	ShowGraphEdgeInfo(ptr_g);

	kruskal(ptr_g);
	GraphDestroy(ptr_g);
}