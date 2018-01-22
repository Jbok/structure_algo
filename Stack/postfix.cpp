#include "postfix.h"

static char OPERATORS[] = "+-*/";
static int PRECEDENCE[] = { 1,1,2,2 };

Stack operand_stack;
Stack operator_stack;

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

int precedence(char op) {
	return PRECEDENCE[is_operator(op)];
}

char *process_op(char op, char *pos) {
	if (is_empty(operator_stack))
		push(operator_stack, op);
	else {
		char top_op = peek(operator_stack);
		if (precedence(op) > precedence(top_op))
			push(operand_stack, op);
		else {
			while (!is_empty(operator_stack) && (precedence(op) <= precedence(top_op))) {
				pop(operator_stack);
				sprintf(pos, "%c ", top_op);
				pos += (strlen(pos) + 1);
				if (!is_empty(operator_stack))
					top_op = (char)peek(operator_stack);
			}
			push(operator_stack, op);
		}
	}
	return pos;
}

char *convert(char *infix) {
	operator_stack = create();

	char *postfix = (char*)malloc(strlen(infix) + 1);
	char *pos = postfix;

	char *token = strtok(infix, " ");
	while (token != NULL) {
		if (token[0] >= '0'&&token[0] <= '9') {
			sprintf(pos, "%s ", token);
			pos += (strlen(token) + 1);
		}
		else if (is_operator(token[0]) > -1) {
			pos = process_op(token[0], pos);
		}
		else {
			handle_exception("Syntax Error: invalid character encountered.\n");
		}
		token = strtok(NULL, " ");
	}

	while (!is_empty(operator_stack)) {
		char op = (char)pop(operator_stack);
		sprintf(pos, "%c ", op);
		pos += 2;
	}

	*pos = '\0';
	return postfix;
}