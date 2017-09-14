CC=cc
CFLAGS= -g -Wall -lpthread

all: counter

counter: counter.c counter.h
	$(CC) $(CFLAGS) counter.c -o counter

clean:
	rm -f counter *.o

.PHONY: clean

check-syntax:
	$(CC) $(CFLAGS) -Wextra -pedantic -fsyntax-only $(CHK_SOURCES)

