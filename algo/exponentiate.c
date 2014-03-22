/*
  computation of x^n
 */
#include <stdio.h>
#include <stdlib.h>

int exponentiate(int x, int n)
{
	int m, z, power;

	if (n < 0) {
		printf("negetive power\n");
		return -1;
	}

	m = n;
	power = 1;
	z = x;

	while (m > 0) {
		while ((m % 2) == 0) {
			m = m/2;
			z *= z;
		}
		m = m -1;
		power *= z;
	}

	return power;
}

int main(int argc, char **argv)
{
	if (argc != 3) {
		printf("Usage:%s <base> <power>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	printf("%s ^ %s = %d\n", argv[1], argv[2],
	       exponentiate(atoi(argv[1]), atoi(argv[2])));
	exit(EXIT_SUCCESS);
}
