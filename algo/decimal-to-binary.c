#include <stdio.h>

static void binary(int n)
{
        if (n == 1 || n == 0) {
                printf("%d", n);
                return;
        }

        binary(n/2);
        printf("%d", n % 2);
}

void to_binary(int n)
{
        if (n < 0) {
                n = n * -1;
                printf("-");
        }

        binary(n);
}

int main(int argc, char **argv)
{
        if (argc != 2) {
                fprintf(stderr, "%s <number>\n", argv[0]);
                return -1;
        }

        int num = atoi(argv[1]);

        to_binary(num);

        printf("\n");

        return 0;
}
