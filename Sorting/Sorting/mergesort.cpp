#include <stdlib.h>
void merge(int arr[], int front, int middle, int rear) {
	int *temp = (int*)malloc(sizeof(int)*(rear - front + 1));
	int i = front;
	int j = middle + 1;
	int k = front;
	while (i<=middle && j<=rear) {
		if (arr[i] <= arr[j]) {
			temp[k++] = arr[i++];
		}
		else {
			temp[k++] = arr[j++];
		}
	}
	while (i <= middle) {
		temp[k++] = arr[i++];
	}
	while (j <= rear) {
		temp[k++] = arr[j++];
	}
	for (int i = front; i <= rear; i++) {
		arr[i] = temp[i];
	}
	free(temp);
}

/*
MergeSort O(NlogN)
T(n)
	if n ==1 
		T(n) =0;
	else
		T([n/2]) + T([n/2]) + n
*/


void mergesort(int arr[], int front, int rear) {
	if (rear <= front) {
		return;
	}
	else {
		int middle = (front + rear) / 2;
		mergesort(arr, front, middle);
		mergesort(arr, middle + 1, rear);
		merge(arr, front, middle, rear);
	}
}
