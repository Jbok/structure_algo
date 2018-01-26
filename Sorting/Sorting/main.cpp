#include <stdio.h>
#include "quicksort.h"
#include "mergesort.h"
#include "heapsort.h"
int main() {
	int arr[10] = { 1000,2,8,6,1,10,15,3,12,11};
	int length = sizeof(arr) / sizeof(int) - 1;

	heap_sort(arr, length);
	//quicksort(arr, 0, 9);
	//mergesort(arr, 0, 9);
	for (int i = 1; i < 10; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}