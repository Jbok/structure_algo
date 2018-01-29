#pragma once
#pragma once
#ifndef __STACKADT_MAZE_H__
#define __STACKADT_MAZE_H__

#include "pos.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // C99 only

typedef Position Item; //for reuse of codes
typedef struct stack_type *Stack;

Stack create();
void destroy(Stack s);
void make_empty(Stack s);
bool is_empty(Stack s);
void push(Stack s, Item i);
Item pop(Stack s);
Item peek(Stack s);

#endif