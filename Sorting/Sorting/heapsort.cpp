#include "heapsort.h"
#include <stdio.h>
void max_heapify(int arr[],int root, int length) {
	if (2 * root > length) {
		return;
	}
	
	int left = arr[2 * root];
	int big_index;
	if (2 * root + 1 > length) {
		big_index = 2 * root;
	}
	else {
		int right = arr[2 * root + 1];
		if (left > right) {
			big_index = 2 * root;
		}
		else {
			big_index = 2 * root + 1;
		}
	}

	if (arr[root] >= arr[big_index]) {
		return;
	}
	else {
		int temp = arr[root];
		arr[root] = arr[big_index];
		arr[big_index] = temp;
		max_heapify(arr, big_index, length);
	} 
	return;
}

void make_heap(int arr[], int length) {
	for (int i = length / 2; i > 0; i--) {
		max_heapify(arr, i, length);
	}
}

void heap_sort(int arr[], int length) {
	make_heap(arr, length);

	for (int i = length; i > 0; i--) {
		int temp = arr[i];
		arr[i] = arr[1];
		arr[1] = temp;
		max_heapify(arr, 1, i-1);
	}
}

