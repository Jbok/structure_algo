#include <stdio.h>
#include <stdlib.h>
#define SIZE 256

struct run {
	char ch=NULL;
	int runLen=0;
	int freq=0;
};

typedef struct run Run;

Run array[SIZE];
int array_count = 0;

int equals(Run run) {
	for (int i = 0; i < array_count; i++) {
		if (array[i].ch == run.ch && array[i].runLen == run.runLen) {
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

	char prev = NULL; //���� ����
	char cur; //���� ����
	int byte_count = 1;

	while ((cur = fgetc(fp)) != EOF) {
		if (cur != prev) { //���� ���ڿ� ����������
			Run temp;
			temp.ch = prev;
			temp.runLen = byte_count;

			int index = equals(temp);
			if (index == -1) {//new symbol
				temp.freq = 1;
				array[array_count++] = temp;
			}
			else {//existed symbol
				array[index].freq++;
			}
			byte_count = 1;
			prev = cur;
		}
		else {//������
			byte_count++;
		}
	}
	if (cur == EOF) { //EOF�� ��� ������ symbol����.
		Run temp;
		temp.ch = prev;
		temp.runLen = byte_count;

		int index = equals(temp);
		if (index == -1) {//new symbol
			temp.freq = 1;
			array[array_count++] = temp;
		}
		else {//existed symbol
			array[index].freq++;
		}
	}
	fclose(fp);
}

int main() {
	read_file("sample.txt");
	printf("%20s", "symbol");
	for (int i = 0; i < array_count; i++) {
		printf("%5c", array[i].ch);
	}
	printf("\n%20s", "run length");
	for (int i = 0; i < array_count; i++) {
		printf("%5d", array[i].runLen);
	}
	printf("\n%20s", "frequency");
	for (int i = 0; i < array_count; i++) {
		printf("%5d", array[i].freq);
	}
	printf("\n");

	
}