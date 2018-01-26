#include "quicksort.h"

int partition(int arr[], int head, int tail) {
	int i = head-1;
	int pivot = arr[tail];

	for (int k = head; k < tail; k++) {
		if (arr[k] <= pivot) {
			i++;
			int temp = arr[k];
			arr[k] = arr[i];
			arr[i] = temp;
		}
	}
	int temp = arr[tail];
	arr[tail] = arr[i+1];
	arr[i+1] = temp;
	return i + 1;
}

void quicksort(int arr[], int head, int tail) {
	if (head < tail) {
		int middle = partition(arr, head, tail);
		quicksort(arr, head, middle - 1);
		quicksort(arr, middle + 1, tail);
	}
}