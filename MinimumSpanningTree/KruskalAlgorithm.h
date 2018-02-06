#pragma once
#include <stdio.h>
#include <malloc.h>
#include "ALGraph.h"
#define SIZE 4
#define EDGE 6

void SaveEdge(ALGraph *pg);

int partition(int left, int right);
void QuickSortEdge(int left, int right);

int find_set(int x);

void union_set(int u, int v);
void kruskal(ALGraph *ptr_g);