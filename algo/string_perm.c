/*
 * Generate all permutations of a given string.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(char *x, char *y)
{
	char temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

void gen_perm(char *str, int start, int end)
{
	int i;
	char temp;

	if (start == end)
		printf("%s\n", str);
	else {
		for (i = start; i < end; i++) {
			swap(str+start, str+i);

			gen_perm(str, start+1, end);

			swap(str+start, str+i);
		}
	}
}

int fact(int n)
{
	if (n <= 1)
		return 1;

	return(n * fact(n-1));
}

int main(int argc, char **argv)
{
	char *str;
	int len;

	if (argc != 2) {
		fprintf(stderr, "Usage:%s <string>\n", argv[0]);
		exit(1);
	}

	str = strdup(argv[1]);
	len = strlen(str);

	printf("Total combinatiation for %s is %d\n", str, fact(len));

	gen_perm(str, 0, len);

	exit(0);
}
