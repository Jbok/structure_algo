#include <stdio.h>
#include "quicksort.h"
#include "mergesort.h"
#include "heapsort.h"
#include "bst.h"

int main() {
	//int arr[10] = { 1000,2,8,6,1,10,15,3,12,11};
	//int length = sizeof(arr) / sizeof(int) - 1;

	//heap_sort(arr, length);
	//quicksort(arr, 0, 9);
	//mergesort(arr, 0, 9);
	//for (int i = 1; i < 10; i++) {
	//	printf("%d ", arr[i]);
	//}
	//printf("\n");
	Item data1;
	data1.value = 13;
	Node head = bst_make_node(NULL, data1);
	Item data2;
	data2.value = 6;
	bst_insert(head, data2);

	Item data3;
	data3.value = 18;
	bst_insert(head, data3);

	Item data4;
	data4.value = 2;
	bst_insert(head, data4);

	Item data5;
	data5.value = 3;
	bst_insert(head, data5);

	Item data6;
	data6.value = 4;
	bst_insert(head, data6);

	Item data7;
	data7.value = 7;
	bst_insert(head, data7);

	Item data8;
	data8.value = 20;
	bst_insert(head, data8);

	Item data9;
	data9.value = 17;
	bst_insert(head, data9);

	Item data10;
	data10.value = 15;
	bst_insert(head, data10);

	Item data11;
	data11.value = 16;
	bst_insert(head, data11);


	bst_print(head);
	printf("\n");
	bst_delete(head);

	bst_print(head);
}