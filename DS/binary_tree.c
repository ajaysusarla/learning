/*
 * Binary tree implemetation.
 *
 * Efficiency : O(log n)
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
	if (!node)
		return NULL;

	node->data = data;
	node->left = NULL;
	node->right = NULL;

	return node;
}

static void free_node(Node *node)
{
	if (node) {
		free(node);
		node = NULL;
	}
}

static void free_tree(Node *node)
{
	if (node) {
		free_tree(node->left);
		free_tree(node->right);
		free_node(node);
		node = NULL;
	}
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
	int last_digit;
	int i;
	Node *root = NULL;

	last_digit = atoi(argv[argc-1]);
	if (last_digit != -1) {
		fprintf(stderr, "Invalid input, please end the input with a -1\n");
		fprintf(stderr, "Usage: %s n1 n2 n3 ..... nn -1\n", argv[0]);
		exit(1);
	}

	for(i=1; i<argc-1; i++) {
		root = insert(root, atoi(argv[i]));
	}

	printf("In order: ");
	print_in_order(root);
	printf("\n");
	printf("Pre order: ");
	print_pre_order(root);
	printf("\n");
	printf("Post oder: ");
	print_post_order(root);
	printf("\n");

	free_tree(root);

	exit(EXIT_SUCCESS);
}
