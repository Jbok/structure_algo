#include "maze.h"

int arr[100][100] = {
{ 1,1,1,1,1,1,1,1,1,1,1 },
{ 1,0,0,0,0,1,1,0,0,0,1 },
{ 1,1,1,1,0,1,1,0,1,0,1 },
{ 1,1,1,1,0,0,0,0,1,0,1 },
{ 1,1,1,1,0,1,1,0,1,0,1 },
{ 1,0,0,0,0,1,1,0,1,0,1 },
{ 1,0,1,1,1,1,0,0,0,0,1 },
{ 1,0,1,1,1,1,1,1,1,1,1 },
{ 1,0,0,0,0,0,0,0,0,3,1 },
{ 1,1,1,1,1,1,1,1,1,1,1 }
};

bool find_maze(int x, int y) {
	if (arr[x][y] == -1 || arr[x][y] == 1) {
		return false;
	}
	else if (arr[x][y] == 3) {
		printf("Find!\n");
		return true;
	}
	arr[x][y] = -1;
	if (find_maze(x + 1, y) || find_maze(x - 1, y) || find_maze(x, y + 1) || find_maze(x, y - 1)) {
		arr[x][y] = -2;
	}
}

void print_solution() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 11; j++) {
			if (arr[i][j] == -2) {
				printf("%2c", '*');
			}
			else {
				printf("%2d", arr[i][j]);
			}
		}
		printf("\n");
	}
}

void play_maze() {
	find_maze(1, 1);
	print_solution();
}