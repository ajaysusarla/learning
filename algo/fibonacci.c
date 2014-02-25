/*
  prints the fibonacci numbers.
 */

#include <stdio.h>
#include <stdlib.h>

static int max;

int fibonacci(int num)
{
	long long arr[num+1];
	int i;

	arr[0] = 0;
	arr[1] = 1;

	for (i = 2; i < num; i++) {
		arr[i] = arr[i-1] + arr[i-2];
	}

	for (i = 0; i < num; i++)
		printf("%d ", arr[i]);

	return 0;
}

int main(int argc, char **argv)
{
	int max;

	if (argc != 2) {
		printf("Usage: %s <max>\n", argv[0]);
		printf("       <max> is the maximum number of fibanocci numbers to generate\n");
		exit(EXIT_FAILURE);
	}

	max = atoi(argv[1]);

	fibonacci(max);

	printf("\n");

	exit(EXIT_SUCCESS);
}
