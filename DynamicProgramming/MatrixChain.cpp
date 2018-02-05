#include <stdio.h>
#define SIZE 5

int m[SIZE][SIZE];
int p[SIZE];

/*Bottom-Up*/
int matrixChain(int n) {
	for (int i = 1; i <= n; i++) {
		m[i][i] = 0;
	}
	for (int r = 1; r = n - 1; r++) {
		for (int i = 1; i <= n - r; i++) {  //각 대각선의 값의 개수
			int j = i + r;
			m[i][j] = m[i + 1][j] + p[i - 1] * p[i] * p[j];
			for (int k = i + 1; k <= j - 1; k++) {
				if (m[i][j] > m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j])
					m[i][j] = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
			}
		}
	}

	return m[1][n];
}


/*
int main() {
	printf("Hello Worl d\n");
}
*/