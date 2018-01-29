#pragma once
#ifndef __BST_H__
#define __BST_H__

#include <stdio.h>
#include <stdlib.h>

/*BST
struct item {
	int value;
};
typedef struct item Item;

struct node {
	struct node *left;
	struct node *right;
	struct node *parent;
	Item item;
};
typedef struct node *Node;
*/

typedef int Item;

struct node {
	struct node *left;
	struct node *right;
	struct node *p;
	Item data;
	int color;
};
typedef struct node *Node;

Node bst_max(Node root);
Node bst_min(Node root);
Node bst_successor(Node root);
Node bst_predecessor(Node root);
Node bst_search(Node root, Item data);

Node bst_make_node(Node parent, Item data);

void bst_insert(Node root, Item data);

Item bst_delete(Node root);

void bst_print(Node root);
#endif