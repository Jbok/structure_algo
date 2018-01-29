#ifndef __STRING_TOOLS_H__
#define __STRING_TOOLS_H__

#include <stdio.h>
#include <Windows.h>

int read_line(FILE *fp, char *str, int size);
LPWSTR char_to_LPWSTR(char *str);
#endif
