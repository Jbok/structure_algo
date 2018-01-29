#include "maze.h"
#define MAP_SIZE 100
#define START_POSITION 1
#define END_POSITION 13
#define SOLUTION_PATH 11

int maze[MAP_SIZE][MAP_SIZE];

void read_mapfile(const char *mapfile){
	FILE *fp = fopen(mapfile, "r");
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			char temp = fgetc(fp);
			while (temp == '\n') {
				temp = fgetc(fp);
			}
			maze[j][i] = temp - '0';
		}
	}
}

bool movable(Position cur, int dir) {
	bool result = false;

	switch (dir)
	{
	case 0: {
		if (maze[cur.x][cur.y - 1] == 0) {
			result = true;
		}
		break;		 
	}
	case 1:
		if (maze[cur.x+1][cur.y] == 0) {
			result = true;
		}
		break;
	case 2:
		if (maze[cur.x][cur.y+1] == 0) {
			result = true;
		}
		break;
	case 3:
		if (maze[cur.x-1][cur.y] == 0) {
			result = true;
		}
		break;
	}
	return result;
}

Position move_to(Position cur, int dir) {
	Position p;
	p.x = 0;
	p.y = 0;
	switch (dir)
	{
	case 0: {
		if (maze[cur.x][cur.y - 1] == 0) {
			p.x = cur.x;
			p.y = cur.y - 1;
		}
		break;
	}
	case 1:
		if (maze[cur.x + 1][cur.y] == 0) {
			p.x = cur.x + 1;
			p.y = cur.y;
		}
		break;
	case 2:
		if (maze[cur.x][cur.y + 1] == 0) {
			p.x = cur.x;
			p.y = cur.y + 1;
		}
		break;
	case 3:
		if (maze[cur.x - 1][cur.y] == 0) {
			p.x = cur.x - 1;
			p.y = cur.y;
		}
		break;
	}
	return p;
}

Position find_maze_value(Position cur, int dir) {
	Position target = { 0,0 };

	switch (dir)
	{
	case 0: {
		target = { cur.x, cur.y - 1 };
		break;
	}
	case 1:
		target = { cur.x + 1, cur.y };
		break;
	case 2:
		target = { cur.x, cur.y + 1 };
		break;
	case 3:
		target = { cur.x - 1, cur.y };
		break;
	}
	return target;
}

Position find_next(Position cur) {
	int min = maze[cur.x][cur.y];
	Position next = { 0,0 };
	for (int dir = 0; dir < 4; dir++) {
		Position temp = find_maze_value(cur, dir);
		if (maze[temp.x][temp.y] > min && maze[temp.x][temp.y]<1) {
			min = maze[temp.x][temp.y];
			next = temp;
		}
	}
	maze[cur.x][cur.y] = SOLUTION_PATH;
	return next;
}

void print_solution(){
	Position cur;
	cur.x = END_POSITION;
	cur.y = END_POSITION;


	//path distance
	/*
	for (int i = 0; i < END_POSITION + 2; i++) {
	for (int j = 0; j < END_POSITION + 2; j++) {
	printf("%3d", maze[j][i]);
	}
	printf("\n");
	}
	*/

	while (!(cur.x == START_POSITION && cur.y == START_POSITION)) {
		cur = find_next(cur);
	}
	maze[START_POSITION][START_POSITION] = SOLUTION_PATH;

	for (int i = 0; i < END_POSITION + 2; i++) {
		for (int j = 0; j < END_POSITION + 2; j++) {
			if (maze[j][i] == SOLUTION_PATH) {
				printf("%1c", ' ');
			}
			else if (maze[j][i]<0) {
				printf("%1c", '*');
			}
			else {
				printf("%1c", '0');
			}
		}
		printf("\n");
	}
}

void play_maze() {
	read_mapfile("maze_map.txt");

	Queue queue = create();
	Position cur;
	cur.x = 1;
	cur.y = 1;

	enqueue(queue, cur);
	maze[cur.x][cur.y] = -1;
	bool found = false;

	while (!is_empty(queue)) {
		cur = dequeue(queue);
		for (int dir = 0; dir < 4; dir++) {
			if (movable(cur, dir)) {
				Position p = move_to(cur, dir);
				maze[p.x][p.y] = maze[cur.x][cur.y] - 1;
				if (p.x == END_POSITION && p.y == END_POSITION) {
					printf("Found the path.\n");
					found = true;
					break;
				}
				enqueue(queue, p);
			}
		}
	}

	if (found) {
		print_solution();
	}
}