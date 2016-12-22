/*
  Generate a k-map, given a number of elements.

  To compile:
  $ cc     truth-table.c   -o truth-table -D PRINT_TRUE_FALSE


  Example:

  $./truth-table 4

    false   false   false   false
    false   false   false    true
    false   false    true   false
    false   false    true    true
    false    true   false   false
    false    true   false    true
    false    true    true   false
    false    true    true    true
     true   false   false   false
     true   false   false    true
     true   false    true   false
     true   false    true    true
     true    true   false   false
     true    true   false    true
     true    true    true   false
     true    true    true    true

 */
#include <stdio.h>
#include <stdlib.h>


#ifdef PRINT_TRUE_FALSE
#define TRUE "true"
#define FALSE "false"
#else
#define TRUE "1"
#define FALSE "0"
#endif

void gen_truth_table(int *arr, int s, int e)
{
        int i;

        if (s == e) {
                for (i = 0; i < e; i++)
                        printf(" %6s ", arr[i] ? TRUE : FALSE);
                printf("\n");
        } else {
                for (i = 0; i < 2; i++) {
                        int t = arr[s];
                        arr[s] = i;
                        gen_truth_table(arr, s+1, e);
                        arr[s] = t;
                }
        }

}

int main(int argc, char **argv)
{
        int i, num;
        int *arr;

        if (argc != 2) {
                fprintf(stderr, "Usage: %s <number of fields>\n", argv[0]);
                exit(EXIT_FAILURE);
        }

        num = atoi(argv[1]);

        arr = malloc(sizeof(int) * num);
        if (!arr) {
                fprintf(stderr, "Memory allocation failure.\n");
                exit(EXIT_FAILURE);
        }

        for (i = 0; i < num; i++) {
                arr[i] = 0;
        }

        gen_truth_table(arr, 0, num);

        free(arr);
        arr = NULL;

        exit(EXIT_SUCCESS);
}
