#pragma once
#ifndef __POS_H__
#define __POS_H__


struct position {
	int x, y;
};

typedef struct position Position;

Position move_to(Position pos, int dir);

#endif