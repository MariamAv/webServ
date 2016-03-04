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

	const char* message = "Bonjour cher Client,\nVous êtes désormais connecté à ce magnifique serveur !\nPourquoi est-il magnifique ?\nJe n'en sais rien... \n"; 

	if (write(socket_client, message, strlen(message)) == -1) {
		perror("write1");
		return -1;
    }

/*
boucle : 
- attente d'un message entrant sur le socket
- renvoi du message recu write socket
*/

	char msg_ent[50];
	int lecture;
	while((lecture = recv(socket_client, msg_ent, 50, 0))>0){
		if (write(socket_client, msg_ent, strlen(msg_ent)) == -1) {
			perror("write2");
			return -1;
   		}
	}


    close(socket_server);
    close(socket_client);

	return 0;
}
