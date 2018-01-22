#pragma once
#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include "stackADT.h"
#include <string.h>

int is_operator(char ch);
int eval(char *expr);
#endif
