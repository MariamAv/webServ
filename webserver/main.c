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
		perror("socket error");
		return -1;
	}

	int socket_client;
	if ((socket_client = accept(socket_server, NULL, NULL)) == -1) {
		perror("Connection refused");
		return -1;
	} 

	puts("Client connected\n");

	const char* message = "\n\nBonjour cher Client,\nVous êtes désormais connecté à ce magnifique serveur !\nGrâce à ce serveur vous pouvez envoyer des messages à vous mêmes et faire pleins d'autres trucs, à vous de le découvrir ! ;)\n\n     (\\(\\        ~~~~~        /)/)          \n     (^.^)    { WELCOME }    (^.^)          \n    o(n_n)       ~~~~~       (n_n)o                        \n\n"; 

	if (write(socket_client, message, strlen(message)) == -1) {
		perror("write1 error");
		return -1;
    }

	char msg_ent[100];
	int lecture;
	while((lecture = recv(socket_client, msg_ent, sizeof(msg_ent), 0))>0){
		if (write(socket_client, msg_ent, strlen(msg_ent)) == -1) {
			perror("write2 error");
			return -1;
   		}
		memset(msg_ent,0, sizeof(msg_ent));
	}

    close(socket_server);
    close(socket_client);
	puts("Connection Closed\n");

	return 0;
}
