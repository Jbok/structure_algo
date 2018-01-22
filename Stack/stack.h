#pragma once
#ifndef __STACK_H__
#define __STACK_H__
#include <stdio.h>
#include <stdlib.h>
void push_a(char ch);
void push_l(char *item);
char pop_a();
char *pop_l(Node *p);
char peek_a();
char *peek_l();
int is_full_a();
int is_empty_a();

#endif