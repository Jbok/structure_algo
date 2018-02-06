#pragma once
#include "ALGraph.h"
#include <malloc.h>
#define NODE_SIZE 9
#define INFINITY 9999

int find_min();

void prim(ALGraph *ptr_g);

void print_prim();