#include "maze.h"
void play_maze() {
	read_maze();
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			printf("%d", maze[j][i]);
		}
		printf("\n");
	}
	Stack s = create();
	Position cur;
	cur.x = 1;
	cur.y = 1;
	
	Position exit;
	exit.x = 13;
	exit.y = 13;

	while (1) {
		maze[cur.x][cur.y] = VISITED;
		if (cur.x == exit.x && cur.y == exit.y) {
			printf("Found the path.\n");
			break;
		}

		bool forwarded = false;
		for (int dir = 0; dir < 4; dir++) {
			if (movable(cur, dir)) {
				push(s, cur);
				cur = move_to(cur, dir);
				forwarded = true;
				break;
			}
		}
		if (!forwarded) {
			maze[cur.x][cur.y] = BACKTRACKED;
			if (is_empty(s)) {
				printf("No path exists.\n");
				break;
			}
			cur = pop(s);
		}
	}
	print_maze(s);
}

int movable(Position pos, int dir) {
	int movable = 1;
	switch (dir)
	{
	case 0: 
		movable = maze[pos.x][pos.y - 1];
		break;
	case 1:
		movable = maze[pos.x + 1][pos.y];
		break;
	case 2:
		movable = maze[pos.x][pos.y + 1];
		break;
	case 3:
		movable = maze[pos.x - 1][pos.y];
		break;
	}
	if (movable == 0)
		return 1;
	else
		return 0;
}

void print_maze(Stack s) {
	while (!is_empty(s)) {
		Position temp = pop(s);
		maze[temp.x][temp.y] = 78;
	}
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			printf("%c", maze[j][i]+'0');
		}
		printf("\n");
	}
}

void read_maze() {
	FILE *fp = fopen("maze_map.txt", "r");
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			char temp = fgetc(fp);
			while (temp == '\n') {
				temp = fgetc(fp);
			}
			maze[j][i]=temp-'0';
		}
	}
}