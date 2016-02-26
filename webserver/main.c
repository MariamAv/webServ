#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "socket.h"

int main ()
{
  
	/* Arnold Robbins in the LJ of February ’95 , describing RCS */
	/*if (argc > 1 && strcmp(argv[1], "-advice") == 0) {
		printf("Don’t Panic !\n");
		return 42;
	}
		printf("Need an advice ?\n");
		return 0;*/



int socket_server;
int create_server();
int create_client() {

	int socket_client;
	socket_client = accept(socket_server, NULL, NULL);
	if (socket_client == -1) {
		perror("accept");
		return -1;
	}
	printf("BONJOUR BOB\n");
	return 0;
}

	return 0;
}
