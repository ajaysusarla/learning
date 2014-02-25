/*
  insertion sort.

  efficiency - O(n^2)
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENTS 100

void print_array(int *array, int size)
{
	int i;

	for(i=0; i<size; i++)
		printf("%d ", array[i]);

	printf("\n");
	return;
}

void insertion_sort(int *array, int size)
{
	int i, j;
	int temp;

	for (i = 0; i <size; i++) {
		temp = array[i];

		for (j = i -1; j >=0 && temp < array[j];) {
			array[j + 1] = array[j];
			j--;
		}

		array[j+1] = temp;
	}

	return;
}

int main(int argc, char **argv)
{
	int array[MAX_ELEMENTS] = { 0 };
	int last_digit;
	int target;
	int size, i, j;
	int location;

	if (argc > MAX_ELEMENTS) {
		fprintf(stderr, "Can only process a maximum of %d elements\n", MAX_ELEMENTS);
		exit(1);
	}

	last_digit = atoi(argv[argc-1]);
	if (last_digit != -1) {
		fprintf(stderr, "Invalid input, please end the input with a -1\n");
		fprintf(stderr, "Usage: %s n1 n2 n3 ..... nn -1\n", argv[0]);
		exit(1);
	}

	for(i=1, j=0; i<argc-1; i++, j++) {
		array[j] = atoi(argv[i]);
	}

	size = j;

	/* sort the array */
	insertion_sort(array, size);

	print_array(array, size);

	exit(EXIT_SUCCESS);
}
