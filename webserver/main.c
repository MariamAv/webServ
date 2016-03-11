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

	const char* message = "Bonjour cher Client,\nVous êtes désormais connecté à ce magnifique serveur !\nPourquoi est-il magnifique ?\nJe n'en sais rien...\nMais il est magnifique, ok ????\nC'est pas parce que t'as des complexe sur toi et ta vie que tout est moche hein !!! Ce serveur est magnifique parce que je le dis, et tu le trouve magnifique parce que je le dis aussi !! Alors arrête de faire genre c'est nul, c'est pas vrai ! C'est MAGNIFIQUE !!! L'incarnation de la magnificience, l'une des plus grandes merveille du monde !!!\nSi tu crois que tu sais faire mieux que ça, eh bah TANT PIS POUR TOI spèce de Jaloux wesh !!!!!!!!!!!!\n"; 

	if (write(socket_client, message, strlen(message)) == -1) {
		perror("write1 error");
		return -1;
    }

	char msg_ent[100];
	int lecture;
	while((lecture = recv(socket_client, msg_ent, 50, 0))>0){
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
