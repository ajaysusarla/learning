/*
 * Given a word, this program will print the possible combinations of a word.
 *
 * Needs aspell. Currently uses 'en_US', change  _ASPELL_DICT_LANG to the dict
 * you need.
 *
 * To compile:
 *  gcc -laspell solve_jumble.c -o solve_jumble
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <aspell.h>

#define _ASPELL_DICT_LANG "en_US"

AspellConfig * spell_config;
AspellSpeller * spell_checker = 0;
AspellCanHaveError * possible_err;

void swap(char *x, char *y)
{
	char temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

void solve_jumble(char *str, int start, int end)
{
	int i;
	char temp;

	if (start == end) {
		int correct = aspell_speller_check(spell_checker,
						   (const char *)str,
						   strlen(str));
		if (correct)
			printf("%s\n", str);
	} else {
		for (i = start; i < end; i++) {
			swap(str+start, str+i);
			solve_jumble(str, start+1, end);
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

	spell_config = new_aspell_config();
	aspell_config_replace(spell_config, "lang", _ASPELL_DICT_LANG);
	possible_err = new_aspell_speller(spell_config);
	if (aspell_error_number(possible_err) != 0) {
		fprintf(stderr, "%s\n", aspell_error_message(possible_err));
		goto end;
	} else
		spell_checker = to_aspell_speller(possible_err);

	str = strdup(argv[1]);
	len = strlen(str);

	solve_jumble(str, 0, len);

	delete_aspell_speller(spell_checker);
end:
	delete_aspell_config(spell_config);

	exit(0);
}
