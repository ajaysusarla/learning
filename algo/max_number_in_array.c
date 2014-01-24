/*
 * Program the finds and returns the maximum of n given numbers(array).
 */
#include <stdio.h>

void print_array(int *arr, int size)
{
	int i;
	for (i=0; i<size; i++)
		printf("%d ", arr[i]);

	printf("\n");
}

int max_in_array(int *arr, int size)
{
	int max = arr[0];
	int i;

	for (i=1; i<size; i++) {
		if (arr[i] > max)
			max = arr[i];
	}

	return max;
}

int main(int argc, char **argv)
{
	int array[] = {10, 2, 3, 8, 5, 550, 15, 100};
	int size = sizeof(array)/sizeof(array[0]);

	printf("Array Elemets(%d):\n", size);
	print_array(array, size);

	printf("%d is the largest number\n", max_in_array(array, size));

	return 0;
}
