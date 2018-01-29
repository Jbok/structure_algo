/*
return-type queens( arghuments)
{
	if non-promising
		report failure and return;
	else if success
		report answer and return;
	else
		visit children recursively;
}
*/
#include "n_queens.h"

int arr[SIZE+1];

bool processing(int level) {
	for (int i = 1; i < level; i++) {
		if (arr[i] == arr[level]) {
			return false;
		}
		if (level - i == abs(arr[i] - arr[level])) {
			return false;
		}	
	}
	return true;
}

bool queen(int level) {
	if (!processing(level)) {
		return false;
	}
	else if (level==SIZE) {
		for (int pos = 1; pos < SIZE + 1; pos++) {
			printf("(%d,%d)\n", pos, arr[pos]);
		}
		printf("===============\n");
		return true;
	}
	else {
		for (int pos = 1; pos < SIZE + 1; pos++) {
			arr[level+1] = pos;
			if (queen(level + 1)) {
				return true;
			}
		}
	}
	return false;
}