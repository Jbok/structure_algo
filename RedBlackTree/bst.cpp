#include "bst.h"

Node bst_max(Node root) {
	if (root->right == NULL) {
		return root;
	}
	bst_max(root->right);
}
Node bst_min(Node root) {
	if (root->left== NULL) {
		return root;
	}
	bst_min(root->left);
}
Node bst_successor(Node root) {
	if (root->right != NULL) {
		return bst_min(root->right);
	}
	Node temp = root->p;
	while (temp != NULL && root == temp->right) {
		root = temp;
		temp = temp->p;
	}
	return temp;
}
Node bst_predecessor(Node root) {
	if (root->left != NULL) {
		return bst_max(root->left);
	}
	Node temp = root->p;
	while (temp != NULL && root == temp->left) {
		root = temp;
		temp = temp->p;
	}
	return temp;
}
Node bst_search(Node root, Item data) {
	if (root == NULL) {
		return NULL;
	}
	if (data < root->data) {
		bst_search(root->left, data);
	}
	else if (data > root->data) {
		bst_search(root->right, data);
	}
	else {
		return root;
	}
}

Node bst_make_node(Node p, Item data) {
	Node newnode = (Node)malloc(sizeof(node));
	newnode->data = data;
	newnode->p = p;
	newnode->left = NULL;
	newnode->right = NULL;

	return newnode;
}

void bst_insert(Node root, Item data) {
	Node temp = root->p;
	Node newnode = bst_make_node(temp, data);

	while (1){
		if (data > root->data) {
			temp = root;
			root = root->right;
			if (root == NULL) {
				temp->right = newnode;
				newnode->p = temp;
				return;
			}
		}
		else if (data < root->data) {
			temp = root;
			root = root->left;
			if (root == NULL) {
				temp->left = newnode;
				newnode->p = temp;
				return;
			}
		}
		else {
			printf("Can't add data with the same exists values.\n");
			return;
		}
	}

	
}

Item bst_delete(Node root) {
	Item data = root->data;

	if (root->left == NULL && root->right == NULL) { //leaf node
		if (root->p->left == root) {
			root->p->left = NULL;
		}
		else {
			root->p->right = NULL;
		}
		free(root);
	}
	else if (root->right == NULL) {
		if (root->p->left == root) {
			root->p->left = root->left;
			root->left->p = root->p;
		}
		else {
			root->p->right = root->left;
			root->left->p = root->p;
		}
		free(root);
	}
	else if (root->left == NULL) {
		if (root->p->left == root) {
			root->p->left = root->right;
			root->right->p = root->p;
		}
		else {
			root->p->right = root->right;
			root->right->p = root->p;
		}
		free(root);
	}
	else {
		Node successor = bst_successor(root);
		root->data = successor->data;
		bst_delete(successor );
	}
	return data;
}

void bst_print(Node root) {
	if (root == NULL) {
		return;
	}
	else {
		bst_print(root->left);
		printf("%d ", root->data);
		bst_print(root->right);
	}
}