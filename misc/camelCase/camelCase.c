/*
  Alice wrote a sequence of words in CamelCase as a string of letters,
  having the following properties:
    It is a concatenation of one or more words consisting of English letters.
    All letters in the first word are lowercase.
    For each of the subsequent words, the first letter is uppercase and rest
    of the letters are lowercase.

Given s, print the number of words in on a new line.

Input Format

A single line containing string .

Constraints

Output Format

Print the number of words in string .

Sample Input

saveChangesInTheEditor

Sample Output

5

Explanation

String contains five words:

    save
    Changes
    In
    The
    Editor

Thus, we print 5 on a new line.
*/

/*
 * compile with: gcc -ggdb -Wall camelCase.c -o camelCase
 */
#include <stdio.h>
#include <stdlib.h>

enum {
        Alpha = 1,
        UAlpha = 2,
        LAlpha = 4,
        Digit = 8,
};

static const long charset[257] = {
        ['0' + 1 ... '9' + 1] = Digit,
        ['A' + 1 ... 'Z' + 1] = Alpha | UAlpha,
        ['a' + 1 ... 'z' + 1] = Alpha | LAlpha,
};

size_t my_strlen(const char *str)
{
        const char *s;

        for (s = str; *s; s++);

        return s-str;
}

int main(int argc, char **argv)
{
        size_t len = 0, i;
        int wordcount = 0;

        if (argc != 2) {
                fprintf(stderr, "Usage:%s <string>\n", argv[0]);
                exit(1);
        }

        len = my_strlen(argv[1]);

        if (len)
                wordcount++;

        for (i = 0; i <len; i++) {
                if (charset[argv[1][i] + 1] & UAlpha)
                        wordcount++;
        }

        printf("%d\n", wordcount);

        return 0;
}
