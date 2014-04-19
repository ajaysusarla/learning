/*
  Binary search tree
  with insertion and deletion
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node Node;
struct node {
	int data;
	Node *left;
	Node *right;
};

static Node *new_node(int data)
{
	Node *node;

	node = (Node *)malloc(sizeof(Node));
	if (node == NULL)
		return NULL;

	node->data = data;
	node->left = NULL;
	node->right = NULL;

	return node;
}

static void free_node(Node *node)
{
	if (node){
		free(node);
		node = NULL;
	}

	return;
}

static void free_tree(Node *node)
{
	if (node) {
		free_tree(node->left);
		free_tree(node->right);
		free_node(node);
		node = NULL;
	}

	return;
}

static int lookup(Node *node, int target)
{
	if (node == NULL)
		return -1;
	else {
		if (node->data == target)
			return 0;
		else {
			if (target < node->data)
				return lookup(node->left, target);
			else
				return lookup(node->right, target);
		}
	}

	return;
}

static Node *insert(Node *node, int data)
{
	if (node == NULL)
		return new_node(data);
	else {
		if (data <= node->data)
			node->left = insert(node->left, data);
		else
			node->right = insert(node->right, data);
		return node;
	}
}

static int delete_node(Node *node, int target)
{
	if (node == NULL) {
		printf("delete_node:node is null\n");
		return -1;
	} else if (node->data == target) {
		printf("delete_node:node->data is target\n");
		if (node->left == NULL)
			node = node->right;
		else if (node->right == NULL)
			node = node->left;
		else {
			Node *temp = node->right;
			while (temp->left != NULL)
				temp = temp->left;
			node = temp;
		}
	} else if (target > node->data) {
		printf("delete_node:node->data is less than target\n");
		delete_node(node->right, target);
	} else if (target < node->data) {
		printf("delete_node:node->data is greater than target\n");
		delete_node(node->left, target);
	}
}

static void print_in_order(Node *node)
{
	if (node == NULL)
		return;

	print_in_order(node->left);
	printf("%d ", node->data);
	print_in_order(node->right);
}

static void print_post_order(Node *node)
{
	if (node == NULL)
		return;

	print_post_order(node->left);
	print_post_order(node->right);

	printf("%d ", node->data);
}

static void print_pre_order(Node *node)
{
	if (node == NULL)
		return;

	printf("%d ", node->data);

	print_pre_order(node->left);
	print_pre_order(node->right);
}

int main(int argc, char **argv)
{
	char ch;
	int data;
	Node *root;

	do {
		printf("\n");
		printf("=== Menu ===\n");
		printf("* (I)nsert node\n");
		printf("* (D)elete node\n");
		printf("* (P)rint tree\n");
		printf("* (E)xit\n");
		printf("Enter a choice of operation:");
		scanf(" %c", &ch);
		switch(ch) {
		case 'I':
		case 'i':
			printf("Enter an element to insert: ");
			scanf("%d", &data);
			root = insert(root, data);
			break;
		case 'D':
		case 'd':
			printf("Enter element to delete: ");
			scanf("%d", &data);
			delete_node(root, data);
			break;
		case 'P':
		case 'p':
			printf("In order: ");
			print_in_order(root);
			printf("\n");
			printf("Pre order: ");
			print_pre_order(root);
			printf("\n");
			printf("Post oder: ");
			print_post_order(root);
			printf("\n");
			break;
		case 'E':
		case 'e':
			printf("Exiting...\n");
			free_tree(root);
			exit(EXIT_SUCCESS);
			break;
		default:
			break;
		}

	} while(1);

	exit(EXIT_SUCCESS);
}
