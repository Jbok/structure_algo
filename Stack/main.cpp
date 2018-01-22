#include <stdio.h>
#include <string.h>


char OPEN[] = "({[";
char CLOSE[] = ")}]";

int is_close(char ch);
int is_open(char ch);
int is_balanced(char *expr);

int main() {
	printf("$ ");
	scanf(str);

}

int is_close(char ch) {
	for (int i = 0; i < strlen(CLOSE); i++) {
		if (ch == CLOSE[i])
			return i;
	}
	return -1;
}

int is_open(char ch) {
	for (int i = 0; i < strlen(OPEN); i++) {
		if (ch == OPEN[i])
			return i;
	}
	return -1;
}

int is_balanced(char *expr) {
	int balanced = 1;
	int index = 0;
	while (balanced && index < strlen(expr)) {
		char ch = expr[index];
		if (is_open(ch) > -1)
			push(ch);
		else  if (is_close(ch) > -1) {
			if (is_empty()) { //when stack is empty, using pop makes problem.
				balanced = 0; //wrong
				break;
			}
			char top_ch = pop();
			if (is_open(top_ch) != is_close(ch)) {
				balanced = 0; //wrong
			}
		}
		index++;
	}
	return (balanced == 1 && is_empty() == 1);
}