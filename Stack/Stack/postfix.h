#pragma once
#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include "stackADT.h"
#include <string.h>

int is_operator(char ch);
int eval(char *expr);
int eval_op(Stack stack, char ch);
int precedence(char op);
char *process_op(char op, char *pos);
char *convert(char *infix);
#endif
