/*
"행렬의 경로 문제"
	정수들이 저장된 n*n 행렬의 좌상단에서 우하단 까지 이동한다.
	단 오른쪽이나 아래쪽 방향으로만 이동할 수 있다.
	방문한 칸에 있는 정수들의 합니 최소화되도록 하라.
*/
#include <stdio.h>
#define SIZE 4

int arr[4][4] = {
	{6,7,12,5},
{5,3,11,18},
{7,17,3,3},
{8,10,14,9}
};



/*Recursive Algorithm*/
int mat_recursive(int i, int j) {
	if (i == 0 && j == 0)
		return arr[i][j];
	else if (i == 0)
		return mat_recursive(i, j - 1) + arr[i][j];
	else if (j == 0)
		return mat_recursive(i - 1, j) + arr[i][j];
	else {
		int left = mat_recursive(i - 1, j);
		int up = mat_recursive(i, j - 1);
		if (left < up)
			return left + arr[i][j];
		else
			return up + arr[i][j];
	}
}


/*Memoization*/
int Memo_arr[4][4];

void init_memoization() {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			Memo_arr[i][j] = -1;
		}
	}
}
int mat_memoization(int i, int j) {

	if (Memo_arr[i][j] != -1)
		return Memo_arr[i][j];


	if (i == 0 && j == 0)
		Memo_arr[i][j] = arr[i][j];
	else if (i == 0)
		Memo_arr[i][j] = mat_memoization(i, j - 1) + arr[i][j];
	else if (j == 0)
		Memo_arr[i][j] = mat_memoization(i - 1, j) + arr[i][j];
	else {
		int left = mat_memoization(i - 1, j);
		int up = mat_memoization(i, j - 1);
		if (left < up)
			Memo_arr[i][j] = left + arr[i][j];
		else
			Memo_arr[i][j] = up + arr[i][j];
	}
	return Memo_arr[i][j];

}

/*Bottom-Up*/
int BU_arr[4][4] = { 0, };
int mat_bottomup() {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (j == 0 && i == 0)
				BU_arr[i][j] = arr[i][j];
			else if (i == 0)
				BU_arr[i][j] = BU_arr[i][j - 1] + arr[i][j];
			else if (j == 0)
				BU_arr[i][j] = BU_arr[i - 1][j] + arr[i][j];
			else {
				int left = BU_arr[i][j - 1];
				int up = BU_arr[i - 1][j];
				if (left < up)
					BU_arr[i][j] = left;
				else
					BU_arr[i][j] = up;
			}
		}
	}
	return BU_arr[SIZE - 1][SIZE - 1];
}

/*
경로 구하기는 경로의 가중치를 구하는 위의 함수들에서 
오른쪽이나 아래로 갈때 또 다른 2차원 배열에다가 방향을 추가하는 방법으로 구현하면 된다.
*/


/*
int main() {
mat_recursive(SIZE - 1, SIZE - 1);

init_memoization();
mat_memoization(SIZE - 1, SIZE - 1);
for (int i = 0; i < 4; i++) {
for (int j = 0; j < 4; j++) {
printf("%d ", Memo_arr[i][j]);
}
printf("\n");
}
}
*/