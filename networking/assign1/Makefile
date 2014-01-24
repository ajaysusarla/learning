
all: server client

server: server.c server.h
	gcc -o server server.c -lpthread -lm

client: client.c client.h
	gcc -o client client.c -lpthread -lm

clean:
	rm -f server client *.o
