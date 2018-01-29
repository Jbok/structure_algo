/*
Algorithm for countCells (x, y)
if the pixel (x, y) is outside the grid
	the result is 0;
else if pixel (x, y) is not an image pixel or already counted
	the result is 0;
else
	set the colour of the pixel (x, y) to a VISITED colour;
	the result is 1 plus the number of cells in each piece of the blob that includes a nearest neightbour;
*/


#include "blob.h"
#define VISITED -1
#define BLUE 1

int arr[8][8] = {
	{1,0,0,0,0,0,0,1},
	{0,1,1,0,0,1,0,0},
	{1,1,0,0,1,0,1,0},
	{0,0,0,0,0,1,0,0},
	{0,1,0,1,0,1,0,0},
	{0,1,0,1,0,1,0,0},
	{1,0,0,0,1,0,0,1},
	{0,1,1,0,0,1,1,1}
};

int counting_cells(int x, int y) {
	int result;
	if (x < 0 || x > 7 || y < 0 || y > 7) {
		return 0;
	}
	else if (arr[x][y] != BLUE) {
		return 0;
	}
	else {
		result= 1;
		arr[x][y] = VISITED;
	
		return 1 + counting_cells(x - 1, y) + counting_cells(x - 1, y - 1) 
			+ counting_cells(x + 1, y) + counting_cells(x - 1, y - 1) 
			+ counting_cells(x, y - 1) + counting_cells(x, y + 1) 
			+ counting_cells(x - 1, y + 1) + counting_cells(x + 1, y + 1);
	}
}