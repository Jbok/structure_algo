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
	Node temp = root->parent;
	while (temp != NULL && root == temp->right) {
		root = temp;
		temp = temp->parent;
	}
	return temp;
}
Node bst_predecessor(Node root) {
	if (root->left != NULL) {
		return bst_max(root->left);
	}
	Node temp = root->parent;
	while (temp != NULL && root == temp->left) {
		root = temp;
		temp = temp->parent;
	}
	return temp;
}
Node bst_search(Node root, Item data) {
	if (root == NULL) {
		return NULL;
	}
	if (data.value < root->item.value) {
		bst_search(root->left, data);
	}
	else if (data.value > root->item.value) {
		bst_search(root->right, data);
	}
	else {
		return root;
	}
}

Node bst_make_node(Node parent, Item data) {
	Node newnode = (Node)malloc(sizeof(node));
	newnode->item = data;
	newnode->parent = parent;
	newnode->left = NULL;
	newnode->right = NULL;

	return newnode;
}

void bst_insert(Node root, Item data) {
	Node temp = root->parent;
	Node newnode = bst_make_node(temp, data);

	while (1){
		if (data.value > root->item.value) {
			temp = root;
			root = root->right;
			if (root == NULL) {
				temp->right = newnode;
				newnode->parent = temp;
				return;
			}
		}
		else if (data.value < root->item.value) {
			temp = root;
			root = root->left;
			if (root == NULL) {
				temp->left = newnode;
				newnode->parent = temp;
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
	Item data = root->item;

	if (root->left == NULL && root->right == NULL) { //leaf node
		if (root->parent->left == root) {
			root->parent->left = NULL;
		}
		else {
			root->parent->right = NULL;
		}
		free(root);
	}
	else if (root->right == NULL) {
		if (root->parent->left == root) {
			root->parent->left = root->left;
			root->left->parent = root->parent;
		}
		else {
			root->parent->right = root->left;
			root->left->parent = root->parent;
		}
		free(root);
	}
	else if (root->left == NULL) {
		if (root->parent->left == root) {
			root->parent->left = root->right;
			root->right->parent = root->parent;
		}
		else {
			root->parent->right = root->right;
			root->right->parent = root->parent;
		}
		free(root);
	}
	else {
		Node successor = bst_successor(root);
		root->item = successor->item;
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
		printf("%d ", root->item.value);
		bst_print(root->right);
	}
}