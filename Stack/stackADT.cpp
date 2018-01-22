#include "stackADT.h"

struct node {
	Item data;
	struct node *next;
};

struct stack_type {
	struct node *top;
};
typedef struct node *Node;

static void terminate(const char *message) { //static function can be called only in own's source code.
	printf("%s\n", message);
	exit(EXIT_FAILURE);
}

Stack create() {
	Stack ptr_stack = (Stack)malloc(sizeof(struct stack_type));
	if (ptr_stack == NULL)
		terminate("Error in create: stack could not be created.\n");
	ptr_stack->top = NULL;
	return ptr_stack;
}

void destroy(Stack s) {
	make_empty(s);
	free(s);
}

void make_empty(Stack s) {
	Node ptr_node = s->top;
	while (ptr_node != NULL) {
		pop(s);
	}
}

bool is_empty(Stack s) {
	return s->top == NULL;
}

void push(Stack s, Item i) {
	Node new_node = (Node)malloc(sizeof(struct node));
	if (new_node == NULL)
		terminate("Erro in push: stack is full.\n");
	
	new_node->data = i;
	new_node->next = s->top;
	s->top = new_node;
}

Item pop(Stack s) {
	if (is_empty(s)) {
		terminate("Error in pop: stack is empty.\n");
	}

	Node old_top = s->top;
	Item temp = old_top->data;
	s->top = old_top->next;
	free(old_top);
	return temp;
}

Item peek(Stack s) {
	if (is_empty(s))
		terminate("Error in peek: stack is empty.\n");
	return s->top->data;
}