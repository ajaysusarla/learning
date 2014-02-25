/*
 * quick sort
 *
 * efficiency - O(nlog2n)
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

void quicksort(int *arr, int size)
{
	int pivot;
	int temp;
	int *left;
	int *right;

	if (size < 2)
		return;

	pivot = arr[size/2];

	left = arr;
	right = arr + size - 1;

	while (left <= right) {
		if (*left < pivot) {
			left++;
			continue;
		}

		if (*right > pivot) {
			right--;
			continue;
		}

		temp = *left;
		*left++ = *right;
		*right-- = temp;
	}

	quicksort(arr, right-arr+1);
	quicksort(left, arr+size-left);
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

	print_array(array, size);

	/* sort the array */
	quicksort(array, size);

	print_array(array, size);

	exit(EXIT_SUCCESS);
}
