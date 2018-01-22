#include "postfix.h"

static char OPERATORS[] = "+-*/";
Stack operand_stack;

static void handle_exception(const char*(message)) {
	printf("%s\n", message);
	exit(EXIT_FAILURE);
}

int is_operator(char ch) {
	for (int i = 0; i < strlen(OPERATORS); i++) {
		if (ch = OPERATORS[i])
			return i;
	}
	return -1;
}

int eval(char *expr) {
	operand_stack = create();
	char *token = strtok(expr, " ");
	while (token != NULL) {
		if (token[0]>='0'&&token[0]<='9') {
			int value = atoi(token);
			push(operand_stack, value);
		}
		else if (is_operator(token[0]) != -1) {
			int result = eval_op(operand_stack, token[0]);
			push(operand_stack, result);
		}
		else {
			handle_exception("Syntax Error: invalid character encountered.\n");
		}
		token = strtok(NULL, " ");
	}
	if (is_empty(operand_stack))
		handle_exception("Syntax Error: Stack empty in eval_op.\n");
	int answer = pop(operand_stack);
	if (is_empty(operand_stack))
		return answer;
	else {
		handle_exception("Syntax Error: Stack should be empty.\n");
		return -1;
	}
		
}

int eval_op(Stack stack, char ch) {
	if (is_empty(stack))
		handle_exception("Syntax Error: Stack empty in eval_op.");
	int right = pop(stack);
	if (is_empty(stack))
		handle_exception("Syntax Error: Stack empty in eval_op.");
	int left = pop(stack);

	int result = 0;
	switch (ch)
	{
	case '+':
		result = left + right;
		break;
	case '-':
		result = left - right;
		break;
	case '*':
		result = left * right;
		break;
	case '/':
		result = left / right;
		break;
	}
	return result;
}