PKGCONFIG = pkg-config
LIBGTK = $(shell $(PKGCONFIG) --libs gtk+-3.0 glib-2.0)
GTKCFLAGS = $(shell $(PKGCONFIG) --cflags gtk+-3.0 glib-2.0)
CC = gcc
NULL =
CFLAGS = -Wall -Wno-pointer-sign -ggdb $(LIBGTK) $(GTKCFLAGS)
LDFLAGS= $(LIBGTK)

all: tree_view.o
	$(CC) $(CFLAGS) -o tree-view tree-view.o $(LDFLAGS)

tree_view.o: tree-view.c tree-view.h
	$(CC) $(CFLAGS) -c -o tree-view.o tree-view.c

clean:
	rm -f *.o tree-view
