#include "postfix.h"
#include <stdio.h>
#include <string.h>
#define MAX_LENGTH 100

void read_line(FILE *fp, char *str, int length);

int main() {
	char infix[MAX_LENGTH];
	printf("$ ");
	read_line(stdin, infix, MAX_LENGTH);

	printf("%s => ", infix);
	char *postfix = convert(infix);
	printf(" %s ", postfix);
	printf(" =value: %d \n", eval(postfix));
}

void read_line(FILE *fp, char *str, int length) {
	int i = 0;
	char ch;
	while ((ch = fgetc(fp)) == ' ');
	while (ch != '\n') {
		str[i++] = ch;
		if (i > length - 1)
			break;
		ch = fgetc(fp);
	}
	str[i] = '\0';
}