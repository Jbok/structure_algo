#include "postfix.h"

static char OPERATORS[] = "+-*/";
Stack operand_stack;

int is_operator(char ch) {
	for (int i = 0; i < strlen(OPERATORS); i++) {
		if (ch = OPERATORS[i])
			return i;
	}
	return -1;
}