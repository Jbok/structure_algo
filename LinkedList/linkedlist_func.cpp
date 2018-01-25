#include "linkedlist_func.h"

void add_head(char *item, Node **ptr_head) {
	Node *temp = (Node*)malloc(sizeof(Node));
	temp->data = item;
	temp->next = *ptr_head;
	*ptr_head = temp;
}

int add_after(char *item, Node *prev) {
	if (prev == NULL) {
		return 0;
	}

	Node *temp = (Node*)malloc(sizeof(Node));
	temp->data = item;
	temp->next = prev->next;
	prev->next = temp;

	return 1;
}

Node *remove_head(Node **ptr_head) {
	if (*ptr_head == NULL) {
		return NULL;
	}
	else {
		Node *temp = (*ptr_head)->next;
		return *ptr_head; //return head node
	}
}

Node *remove_after(Node *prev) {
	Node *temp = prev->next;
	if (temp == NULL) {
		return NULL;
	}
	else {
		prev->next = temp->next;
		return temp; //return removed node.
	}
}

Node *find(char *item, Node *head) {
	Node *temp = head;
	while (temp != NULL) {
		if (strcmp(temp->data, item) == 0) {
			return temp;
		}
		temp = temp->next;
	}
	return temp;
}

int find_index(char *item, Node *head) {
	Node *temp = head;
	int index = 0;
	while (temp != NULL) {
		if (strcmp(temp->data, item) == 0) {
			return index;
		}
		temp = temp->next;
		index++;
	}
	return -1;
}

Node *get_node(int index, Node *head) {
	if (index < 0) {
		return NULL;
	}
	Node *temp = head;
	for (int i = 0; i < index && temp != NULL; i++) {
		temp = temp->next;
	}
	return temp;
}

int add(int index, char *item, Node *head) {
	if (index < 0) {
		return 0;
	}
	else if (index == 0) {
		add_head(item, &head);
		return 1;
	}
	else {
		Node *prev = get_node(index - 1, head);
		if (prev == NULL) {
			return 0;
		}
		else {
			add_after(item, prev);
			return 1;
		}

	}

}

Node *remove(int index, Node *head) {
	if (index < 0) {
		return NULL;
	}
	else if (index == 0) {
		return remove_head(&head);
	}
	else {
		Node *prev = get_node(index - 1, head);
		if (prev == NULL) {
			return NULL;
		}
		else {
			return remove_after(prev);
		}
	}
}

Node *remove(char *item, Node *head) {
	int index = find_index(item, head);
	return remove(index, head);
}

void add_to_ordered_list(char *item, Node *head) {
	Node *q = NULL;
	Node *p = head;

	while (p != NULL && strcmp(p->data, item) <= 0) {
		q = p;
		p = p->next;
	}
	if (q == NULL) {
		add_head(item, &head);
	}
	else {
		add_after(item, q);
	}
}

int read_line(FILE *fp, char *str, int max_length) {
	char ch;
	int length = 0;
	while ((ch = fgetc(fp)) == ' ');
	while (ch != '\n') {
		if (length + 1 >= max_length) {
			break;
		}
		str[length++] = ch;
		ch = fgetc(fp);
	}
	str[length] = '\0';

	return length;
}