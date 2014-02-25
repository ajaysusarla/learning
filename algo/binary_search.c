/*
  binary search
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENTS 100
#define BOLDWHITE   "\033[1m\033[37m"
#define RESET   "\033[0m"

void print_array(int *array, int size, int location)
{
	int i;

	for(i=0; i<size; i++) {
		if (i == location)
			printf(BOLDWHITE "%d " RESET, array[i]);
		else
			printf("%d ", array[i]);
	}

	printf("\n");
	return;
}


int binary_search(int *array, int end, int target, int *loc)
{
	int first;
	int mid;
	int last;

	first = 0;
	last = end;

	while (first <= last) {
		mid = (first + last) / 2;

		if (target > array[mid])
			first = mid + 1;
		else if (target < array[mid])
			last = mid - 1;
		else
			break;
	}

	*loc = mid;

	return (target == array[mid]);
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
	selection_sort(array, size);

	printf("Enter a number to search:");
	scanf("%d", &target);

	/* search the array */
	if (binary_search(array, size, target, &location)) {
		printf("Found %d at position %d in the array.\n", target, location+1);
		print_array(array, size, location);
	} else {
		printf("%d not found\n", target);
	}

	exit(EXIT_SUCCESS);
}
