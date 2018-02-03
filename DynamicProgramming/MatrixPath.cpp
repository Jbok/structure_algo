/*
"����� ��� ����"
	�������� ����� n*n ����� �»�ܿ��� ���ϴ� ���� �̵��Ѵ�.
	�� �������̳� �Ʒ��� �������θ� �̵��� �� �ִ�.
	�湮�� ĭ�� �ִ� �������� �մ� �ּ�ȭ�ǵ��� �϶�.
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
��� ���ϱ�� ����� ����ġ�� ���ϴ� ���� �Լ��鿡�� 
�������̳� �Ʒ��� ���� �� �ٸ� 2���� �迭���ٰ� ������ �߰��ϴ� ������� �����ϸ� �ȴ�.
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