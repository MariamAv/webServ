#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
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
	if ((socket_server = create_server(8080)) == -1) {
		perror("socket");
		return -1;
	}

	int socket_client;
	if ((socket_client = accept(socket_server, NULL, NULL)) == -1) {
		perror("Connection refused");
		return -1;
	} 

	puts("Client connected\n");

	const char* message = "Bonjour 123\n"; 

	if (write(socket_client, message, strlen(message)) == -1) {
		perror("write");
		return -1;
    }


    close(socket_server);
    close(socket_client);

	return 0;
}
