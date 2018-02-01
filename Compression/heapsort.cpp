#include "heapsort.h"
#include <stdio.h>

Run extractMin(Run arr[], int length) {
	Run temp = arr[1];
	arr[1] = arr[length];
	arr[length] = NULL;
	make_heap(arr, length - 1);
	return temp;
}

void min_heapify(Run arr[],int root, int length) {
	if (2 * root > length) {
		return;
	}
	
	Run left = arr[2 * root];
	int small_index;
	if (2 * root + 1 > length) {
		small_index = 2 * root;
	}
	else {
		Run right = arr[2 * root + 1];
		if (left->freq < right->freq) {
			small_index = 2 * root;
		}
		else {
			small_index = 2 * root + 1;
		}
	}

	if (arr[root]->freq <= arr[small_index]->freq) {
		return;
	}
	else {
		Run temp = arr[root];
		arr[root] = arr[small_index];
		arr[small_index] = temp;
		min_heapify(arr, small_index, length);
	} 
	return;
}

void make_heap(Run arr[], int length) {
	for (int i = length / 2; i > 0; i--) {
		min_heapify(arr, i, length);
	}
}

/*
void heap_sort(int arr[], int length) {
make_heap(arr, length);

for (int i = length; i > 0; i--) {
int temp = arr[i];
arr[i] = arr[1];
arr[1] = temp;
min_heapify(arr, 1, i-1);
}
}
*/