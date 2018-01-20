#include "string_tools.h"

int read_line(FILE *fp, char *str, int size) {
	int ch, i = 0;
	while ((ch = fgetc(fp)) == ' ');
	while ( ch != '\n' && ch != EOF) {
		if (i < size - 1) {
			str[i++] = ch;
		}
		ch = fgetc(fp);
	}
	str[i] = '\0';
	return i;
}