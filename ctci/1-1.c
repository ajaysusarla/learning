/*
  Implement an alogrithm to determine if a string has all unique characters.
  What if you cannot use additional data structures?
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* method 1*/
int has_unique_chars_m1(char *str, int len)
{
	char letters[256] = {0};
	int i;

	if (len > 256)
		return -1;

	for (i = 0; i < len; i++) {
		int val = str[i];

		if (letters[val])
			return -1;

		letters[val] = 1;
	}

	return 0;
}

/*method 2*/
int has_unique_chars_m2(char *str, int len)
{
	long checker = 0;
	int i;

	for (i = 0; i < len; i++) {
		int val = str[i] - 'A';

		printf("%ld\n", checker & (1 << val));

		if ((checker & (1 << val)) > 0)
			return -1;

		checker |= (1 << val);
	}

	return 0;
}


int main(int argc, char **argv)
{
	int ret;

	if (argc != 2) {
		printf("Usage: %s <string>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if (has_unique_chars_m1(argv[1], strlen(argv[1])) == 0) {
		printf("has unique characters.\n");
		ret = EXIT_SUCCESS;
	} else {
		printf("has characters that repeat.\n");
		ret = EXIT_FAILURE;
	}

	exit(EXIT_SUCCESS);
}
