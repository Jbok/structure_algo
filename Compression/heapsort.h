#pragma once
#ifndef __HEAPSORT_H__
#define __HEAPSORT_H__
#include <stdio.h>
#include <stdlib.h>

struct run {
	char ch = NULL;
	int runLen = 0;
	int freq = 0;
	struct run *left=NULL;
	struct run *right=NULL;
	int codeword;		 //부여된 codeword를 32비트 정수로 저장.
	int codewordLen;	 //부여된 codeword의 길이. 즉, codeword의 하위 codewordlen비트가 실제 codeword

};

typedef struct run *Run;

void make_heap(Run arr[], int length);
Run extractMin(Run arr[], int length);
//void heap_sort(run arr[], int length);
#endif