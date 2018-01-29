#include "pos.h"

Position move_to(Position pos, int dir) {
	Position temp;

	switch (dir) // 0:North, 1:East, 2:South, 3:West
	{
		case 0: {
			temp.x = pos.x;
			temp.y = pos.y - 1;
			break;
		}
		case 1: {
			temp.x = pos.x + 1;
			temp.y = pos.y;
			break;
		}
		case 2: {
			temp.x = pos.x;
			temp.y = pos.y + 1;
			break;
		}
		case 3: {
			temp.x = pos.x - 1;
			temp.y = pos.y;
			break;
		}
	}
	return temp;
}