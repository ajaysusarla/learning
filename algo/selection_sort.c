/*
 * A basic implementation of selection sort.
 * Get the user to input the data(numbers) that need to be sorted.
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

void selection_sort(int *array, int size)
{
	int temp, min, i, j;

	for (i = 0; i < size; i++) {
		min = i;
		for (j = i; j < size; j++) {
			if(array[j] < array[min])
				min = j;
		}

		if (min != i) {
			temp = array[i];
			array[i] = array[min];
			array[min] = temp;
		}
	}
	return;
}

int main(int argc, char **argv)
{
	int array[MAX_ELEMENTS] = { 0 };
	int last_digit;
	int size, i, j;

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

	selection_sort(array, size);

	print_array(array, size);

	exit(0);
}
