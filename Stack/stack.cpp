#include "stack.h"
#define MAX_CAPACITY 100

char stack_a[MAX_CAPACITY];
int top_a = -1;

struct node {
	char *data;
	struct node *next;
};
typedef struct node Node;

Node *top_l = NULL;

void push_a(char ch) {
	if (is_full_a()) {
		return;
	}
	top_a++;
	stack_a[top_a] = ch;
}
void push_l(char *item) {
	Node *temp = (Node*)malloc(sizeof(Node));
	temp->data = item;
	temp->next = top_l;
	top_l = temp;
}

char pop_a() {
	char tmp = stack_a[top_a];
	top_a--;
	return tmp;
}
char *pop_l(Node *p) {
	if (is_empty_l())
		return NULL;
	else {
		char *temp = top_l->data;
		top_l = top_l->next;
		free(p);
		return temp;
	}
}

char peek_a() {
	return stack_a[top_a];
}
char *peek_l() {
	if (is_empty_l())
		return NULL;
	return top_l->data;
}

int is_full_a() {
	return top_a == MAX_CAPACITY - 1;
}

int is_empty_a() {
	return top_a == -1;
}
int is_empty_l() {
	return top_l == NULL;
}
