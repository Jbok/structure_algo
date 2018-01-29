#ifndef __LINKEDLIST_FUNC_H__
#define __LINKEDLIST_FUNC_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node {
	char *data;
	node *next;
};

typedef struct node Node;

void add_head(char *name, Node **head);
int add_after(char *item, Node *prev);
Node *remove_head(Node **ptr_head);
Node *remove_after(Node *prev);
Node *find(char *item, Node *head);
int find_index(char *item, Node *head);
Node *get_node(int index, Node *head);
int add(int index, char *item, Node *head);
Node *remove(int index, Node *head);
Node *remove(char *item, Node *head);
int read_line(FILE *fp, char *str, int max_length);

#endif