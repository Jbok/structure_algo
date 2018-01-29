/*
P: some of {[0]~[k-1]}
S: {[k]~[last]}
argument of P, S => int k;
powerSet(P, S)
if S is an empty set
	print P;
else
	let t be the first element of S;
	powerSet(P, S - {t});
	powerSet(Pu{t}, S-{t});
*/
#include "powerset.h"

char data[] = { 'a','b','c','d','e','f' };
int n = sizeof(data) / sizeof(data[0]);
bool include[6] = { false };

void powerSet(int k) {
	if (k == n) { //if leaf node
		for (int i = 0; i < n; i++) {
			if (include[i]) {
				printf("%c ", data[i]);
			}
		}
		printf("\n");
		return;
	}
	//left node (exclude node)
	include[k] = false;
	powerSet(k + 1);
	//right node (include node)
	include[k] = true;
	powerSet(k + 1);
}
