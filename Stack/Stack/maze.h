#pragma once
#ifndef __MAZE_H__
#define __MAZE_H__

#include "stackADT_maze.h"

#define MAX 100
#define PATH 0 //지나갈 수 있는 위치
#define WALL 1 //지나갈 수 없는 위치
#define VISITED 2 //이미 방문한 위치 
#define BACKTRACKED 3 //방문했다가 되돌아 나온 위치

static int maze[MAX][MAX];

void read_maze();
void print_maze(Stack s);
int movable(Position pos, int dir);
void play_maze();

#endif