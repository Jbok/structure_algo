#include "Prim.h"
#include <stdio.h>

int key[NODE_SIZE];
int pre[NODE_SIZE];
int set[NODE_SIZE] = {1,};
int find_min() {
	int min = INFINITY;
	int min_index;
	for (int i = 0; i < NODE_SIZE; i++) {
		if (set[i] == 0) {
			if (key[i] < min) {
				min = key[i];
				min_index = i;
			}
		}
	}
	set[min_index] = 1;
	return min_index;
}

void prim(ALGraph *ptr_g) {
	for (int i = 0; i < NODE_SIZE; i++) {
		key[i] = INFINITY;
	}

	int temp;
	int value;
	int index = 0;
	int count = 1;

	while (count < NODE_SIZE) {
		if (LFirst(&(ptr_g->adjList[index]), &temp, &value)) {
			if (value < key[temp]) {
				key[temp] = value;
				pre[temp] = index;
			}
			while (LNext(&(ptr_g->adjList[index]), &temp, &value)) {
				if (value < key[temp]) {
					key[temp] = value;
					pre[temp] = index;
				}
			}
		}
		index = find_min();
		printf("(%c,%c) w:%d\n", index + 'A', pre[index] + 'A', key[index]);
		key[index]=
		count++;
	}
}
