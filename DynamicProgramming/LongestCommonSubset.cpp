#include <math.h>
#include <string.h>
#define SIZE 4
int c[SIZE][SIZE];
char *x;
char *y;
int lcs(int m, int n) {
	for (int i = 0; i <= m; i++) //if j == 0 
		c[i][0] = 0;
	for (int j = 0; j <= n; j++) //if i == 0
		c[0][j] = 0;
	for (int i = 0; i <= m; i++) {
		for (int j = 0; j <= n; j++) {
			if (x[i]==y[i])		//xi = yj,
				c[i][j] = c[i - 1][j - 1] + 1;
			else
				c[i][j] = fmax(c[i - 1][j], c[i][j - 1]);
		}
	}
	return c[m][n];
}