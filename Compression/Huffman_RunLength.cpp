#include "heapsort.h"
#define SIZE 4


Run *array;
Run *min_heap;
Run root;
int array_count = 0;
int array_size = SIZE;

void doubling_array() {
	array_size = array_count * 2;
	Run *temp = (Run*)malloc(sizeof(Run)*array_size);
	for (int i = 0; i < array_count; i++) {
		temp[i] = array[i];
	}
	free(array);
	array = temp;
	return;
}

int equals(Run run) {
	for (int i = 0; i < array_count; i++) {
		if (array[i]->ch == run->ch && array[i]->runLen == run->runLen) {
			return i;
		}
	}
	return -1; 
}

void read_file(const char *filename) {
	FILE *fp = fopen(filename, "rb");
	if (fp == NULL) {
		fputs("Error: File Open \n", stderr);
		exit(1);
	}

	char prev = NULL; //이전 문자
	char cur; //현재 문자
	int byte_count = 1;

	while ((cur = fgetc(fp)) != EOF) {
		if (cur != prev) { //이전 문자와 같지않으면
			Run temp = (Run)malloc(sizeof(run));
			temp->ch = prev;
			temp->runLen = byte_count;
			temp->left = NULL;
			temp->right = NULL;

			int index = equals(temp);
			if (index == -1) {//new symbol
				temp->freq = 1;
				array[array_count++] = temp;
				if (array_count >= array_size) {
					doubling_array();
				}
			}
			else {//existed symbol
				array[index]->freq++;
			}
			byte_count = 1;
			prev = cur;
		}
		else {//같으면
			byte_count++;
		}
	}
	if (cur == EOF) { //EOF일 경우 마지막 symbol저장.
		Run temp = (Run)malloc(sizeof(run));
		temp->ch = prev;
		temp->runLen = byte_count;
		temp->left = NULL;
		temp->right = NULL;
		int index = equals(temp);
		if (index == -1) {//new symbol
			temp->freq = 1;
			array[array_count++] = temp;
		}
		else {//existed symbol
			array[index]->freq++;
		}
	}
	fclose(fp);
}

void HuffmanCoding() {
	min_heap = (Run*)malloc(sizeof(Run)*array_count);
	for (int i = 1; i < array_count; i++) {
		min_heap[i] = array[i];
	}
	make_heap(min_heap, array_count-1); //store all runs into hte heap.
	int length = array_count-1;
	while (length > 1) {
		Run temp1 = extractMin(min_heap, length--);
		Run temp2 = extractMin(min_heap, length--);
		Run temp_sum = (Run)malloc(sizeof(run));
		temp_sum->freq = temp1->freq + temp2->freq;
		temp_sum->left = temp1;
		temp_sum->right = temp2;
		min_heap[++length] = temp_sum;
		make_heap(min_heap, length);
	}
	root = min_heap[1];
}

void printHuffmanTree(Run node, int depth) {
	for (int i = 0; i < depth; i++)
		printf("%5s", " ");
	if (node == NULL) {
		printf("null\n");
	}
	else {
		printf("%c,%d\n", node->ch, node->freq);
		printHuffmanTree(node->left, depth + 1);
		printHuffmanTree(node->right, depth + 1);
	}
}

int main() {
	array = (Run*)malloc(sizeof(Run)*array_size);
	read_file("sample.txt");
	printf("%20s", "symbol");
	for (int i = 0; i < array_count; i++) {
		printf("%5c", array[i]->ch);
	}
	printf("\n%20s", "run length");
	for (int i = 0; i < array_count; i++) {
		printf("%5d", array[i]->runLen);
	}
	printf("\n%20s", "frequency");
	for (int i = 0; i < array_count; i++) {
		printf("%5d", array[i]->freq);
	}
	printf("\n");


	HuffmanCoding();
	printHuffmanTree(root, 0);
}