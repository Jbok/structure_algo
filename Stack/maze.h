#pragma once
#ifndef __MAZE_H__
#define __MAZE_H__

#include "stackADT_maze.h"

#define MAX 100
#define PATH 0 //������ �� �ִ� ��ġ
#define WALL 1 //������ �� ���� ��ġ
#define VISITED 2 //�̹� �湮�� ��ġ 
#define BACKTRACKED 3 //�湮�ߴٰ� �ǵ��� ���� ��ġ

static int maze[MAX][MAX];

void read_maze();
void print_maze(Stack s);
int movable(Position pos, int dir);
void play_maze();

#endif