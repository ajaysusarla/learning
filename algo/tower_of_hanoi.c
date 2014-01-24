/*
  Towers of hanoi
 */

#include <stdio.h>
#include <stdlib.h>

void tower_of_hanoi(int disks, char *source, char *dest, char *spare)
{
	if (disks >= 1) {
		tower_of_hanoi(disks-1, source, spare, dest);
		fprintf(stdout, "Move disk %d  from [%s] -> [%s]\n", disks, source, dest);
		tower_of_hanoi(disks-1, spare, dest, source);
	}
}

int main(int argc, char **argv)
{
	int disks;

	if (argc == 1) {
		fprintf(stderr, "Usage: %s <number of disks>\n", argv[0]);
		exit(1);
	}

	disks = atoi(argv[1]);

	tower_of_hanoi(disks, "source", "dest", "spare");

	exit(0);
}
