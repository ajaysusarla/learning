/*
  Implement a function void reverse(char *str) in C which reverses a
  null-terminated string
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char *str)
{
	char *end = str;
	char tmp;

	if (str) {
		while (*end)
			++end;

		--end;

		while (str < end) {
			tmp = *str;
			*str++ = *end;
			*end-- = tmp;
		}
	}
}

int main(int argc, char **argv)
{
	int ret;
	char *str;

	if (argc != 2) {
		printf("Usage: %s <string>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	str = strdup(argv[1]);

	reverse(str);

	printf("Reversed string: %s\n", str);

	free(str);

	exit(EXIT_SUCCESS);
}
