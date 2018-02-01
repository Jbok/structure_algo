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
};

typedef struct run *Run;

void make_heap(Run arr[], int length);
Run extractMin(Run arr[], int length);
//void heap_sort(run arr[], int length);
#endif