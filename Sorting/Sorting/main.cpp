#include <stdio.h>
#include "quicksort.h"
#include "mergesort.h"

int main() {
	int arr[10] = { 2,8,7,22,5,38,13,2,77,7 };
	quicksort(arr, 0, 9);
	//mergesort(arr, 0, 9);
	for (int i = 0; i < 10; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}