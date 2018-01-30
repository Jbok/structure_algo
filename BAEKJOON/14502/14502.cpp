#include <stdio.h>
#define VIRUS 2
#define PATH 0
#define BLOCK 1

int arr[8][8];
int count(int arr[8][8], int n, int m) {
	int count = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (arr[i][j] == 0)
				count++;
		}
	}
	return count;
}
void spread(int arr[8][8], int x, int y, int n, int m) {
	if (arr[x][y] == VIRUS) {
		if (x - 1 >= 0) {
			if (arr[x - 1][y] == PATH) {
				arr[x - 1][y] = VIRUS;
				spread(arr, x - 1, y, n, m);
			}

		}
		if (x + 1 < n) {
			if (arr[x + 1][y] == PATH) {
				arr[x + 1][y] = VIRUS;
				spread(arr, x + 1, y, n, m);
			}

		}
		if (y - 1 >= 0) {
			if (arr[x][y - 1] == PATH) {
				arr[x][y - 1] = VIRUS;
				spread(arr, x, y - 1, n, m);
			}

		}
		if (y + 1 < m) {
			if (arr[x][y + 1] == PATH) {
				arr[x][y + 1] = VIRUS;
				spread(arr, x, y + 1, n, m);
			}

		}
	}
	else {
		return;
	}
}
int main() {
	int n, m;
	int max_count = 0;

	scanf("%d %d\n", &n, &m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", &arr[i][j]);
		}
	}

	for (int i = 0; i < n*m - 2; i++) {
		for (int j = 1 + i; j < n*m - 1; j++) {
			for (int k = 1 + j; k < n*m; k++) {
				if (arr[i / m][i%m] == 0 && arr[j / m][j%m] == 0 && arr[k / m][k%m] == 0) {
					int temp[8][8] = { 0, };
					for (int l = 0; l < n; l++) {
						for (int q = 0; q < m; q++) {
							temp[l][q] = arr[l][q];
						}
					}
					temp[i / m][i%m] = 1;
					temp[j / m][j%m] = 1;
					temp[k / m][k%m] = 1;
					for (int l = 0; l < n; l++) {
						for (int q = 0; q < m; q++) {
							if (temp[l][q] == 2)
								spread(temp, l, q, n, m);
						}
					}
					if (count(temp, n, m) > max_count) {
						max_count = count(temp, n, m);
					}

				}
			}
		}
	}
	printf("%d", max_count);
	
}