#include "linkedlist_func.h"

int main() {
	Node *head = NULL;
	char buf1[10] = "Hello";
	add_head(buf1, &head);
	printf("%s", head->data);
}

