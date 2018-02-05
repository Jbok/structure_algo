#include <stdio.h>
#include <math.h>

#define WEIGHT 12
#define NUM 6
int weight[WEIGHT] = { 0,1,2,5,6,7 };
int price[NUM] = { 0,1,6,18,22,28 };
int m[NUM][WEIGHT];

/*Bottom-up*/
void init_knapsack() {
	for (int i = 0; i < WEIGHT; i++) {
		m[0][i] = 0;
	}
}
int knapsack() {
	for (int n = 1; n < NUM; n++) {
		for (int w = 1; w < WEIGHT; w++) {
			if (weight[n] > w)
				m[n][w] = m[n - 1][w];
			else {
				m[n][w] = fmax(m[n - 1][w], m[n - 1][w - weight[n]] + price[n]);
			}
		}
	}

	return m[NUM - 1][WEIGHT - 1];
}

int main() {
	init_knapsack();
	printf("%d\n", knapsack());

}
