#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#define DEFAULT_PORT "8888"

#define CONN_BACKLOG 10 /* Maximum number of backlog connections */

void sigchld_handler(int s)
{
	while(waitpid(-1, NULL, WNOHANG) > 0);
}

void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(int argc, char *argv[], char *env[])
{
	int sockfd, newfd;
	struct addrinfo hints, *server_info, *p;
	struct sockaddr_storage client_addr;
	socklen_t sin_size;
	struct sigaction sa;
	int yes=1;
	char s[INET6_ADDRSTRLEN];
	int ret;
	char *port;

	if (argc > 2) {
		fprintf(stderr, "Usage: %s <port>\n", *argv);
		fprintf(stderr, "   If no port is specified, the server will listen\n");
		fprintf(stderr, "   at the default port %s\n", DEFAULT_PORT);
		exit(EXIT_FAILURE);
	}

	if (argc == 2) {
		int port_num;
		port_num = atoi(argv[1]);
		if (port <= 0) {
			fprintf(stderr, "Invalid Port number %s.\n", argv[1]);
			exit(EXIT_FAILURE);
		}
		port = argv[1];
	} else
		port = DEFAULT_PORT;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	ret = getaddrinfo(NULL, DEFAULT_PORT, &hints, &server_info);
	if (ret != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(ret));
		exit(EXIT_FAILURE);
	}

	/*
	  getaddrinfo() returns a list of address structures.
	   Try each address until we successfully bind(2).
	   If socket(2) (or bind(2)) fails, we (close the socket
	   and) try the next address.
	*/

	for (p = server_info; p != NULL; p = p->ai_next) {
		fprintf(stdout, "name: %s\n", p->ai_canonname);
		sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (sockfd == -1) {
			perror("server: socket");
			continue;
		}

		if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,
				&yes, sizeof(int)) == -1) {
			perror("server: setsockopt");
			exit(EXIT_FAILURE);
		}

		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd);
			perror("server: bind");
			continue;
		}

		break;
	}

	if (p == NULL) {
		fprintf(stderr, "server: failed to bind\n");
		exit(2);
	}

	freeaddrinfo(server_info);

	if (listen(sockfd, CONN_BACKLOG) == -1) {
		perror("server: listen");
		exit(EXIT_FAILURE);
	}

	sa.sa_handler = sigchld_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGCHLD, &sa, NULL) == -1) {
		perror("server: sigaction");
		exit(EXIT_FAILURE);
	}

	fprintf(stdout, "server: waiting for connections on port %s...\n\n", port);

	while(1) {
		sin_size = sizeof(client_addr);
		newfd = accept(sockfd, (struct sockaddr *)&client_addr, &sin_size);
		if (newfd == -1) {
			perror("server: accept");
			continue;
		}
		inet_ntop(client_addr.ss_family,
			  get_in_addr((struct sockaddr *)&client_addr),
			  s, sizeof(s));
		printf("server: got connection from %s\n", s);

		if (!fork()) {
			fprintf(stdout, "child..\n");
			close(sockfd);
			if (send(newfd, "Hello, world!\n", 13, 0) == -1)
				perror("child: send");
			close(newfd);
			fprintf(stdout, "exiting child..\n");
			exit(EXIT_SUCCESS);
		}

		close(newfd);
	}

	exit(EXIT_SUCCESS);
}
