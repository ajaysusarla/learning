/*
  27. Write a program for an algorithm that converts a numeric scroe to a letter
  grade. The grading scale is the rather typical "absolute scale" in which 90%
  or more is an A, 80% to 90% is a B, 70% to 80% is a C, and 60% to 70% is a D.
  Anything below 60% is an F.
 */

#include <stdio.h>

static inline int my_isspace(char c)
{
        return (c == ' '  ||
                c == '\t' ||
                c == '\n');
}

static inline int my_isnum(char c)
{
        return (c >= '0' && c <= '9');
}

long my_strtol(const char *str)
{
        char *p = (char *) str;
        long res = 0;
        int sign = 0, temp = 0;

        while (my_isspace(*p)) {
                p++;
        }

        if (*p == '-') {
                sign = 1;
                p++;
        } else if (*p == '+') {
                sign = 0;
                p++;
        }

        while (*p) {
                if (my_isnum(*p)) {
                        temp = *p - '0';
                        res = res*10 + temp;
                        p++;
                } else {
                        res = -999999;
                        break;
                }
        }

        if (sign)
                res = -res;

        return res;
}

int main (int argc, char **argv)
{
        long score;

        if (argc != 2) {
                fprintf(stderr, "Usage: %s <score>\n", argv[0]);
                return -1;
        }

        score = my_strtol(argv[1]);

        if (score >= 90)
                fprintf(stdout, "GRADE: A\n");
        else if (score >= 80)
                fprintf(stdout, "GRADE: B\n");
        else if (score >= 70)
                fprintf(stdout, "GRADE: C\n");
        else if (score >= 60)
                fprintf(stdout, "GRADE: D\n");
        else if (score < 60 && score > 0)
                fprintf(stdout, "GRADE: F\n");
        else
                fprintf(stdout, "GRADE: FAIL!!\n");

        return 0;
}
