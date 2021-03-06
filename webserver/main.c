#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>
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

	initialiser_signaux();

	int socket_server;
	if ((socket_server = create_server(8080)) == -1) {
		perror("socket error");
		return -1;
	}

	int socket_client = accept(socket_server, NULL, NULL);
	if (socket_client == -1) {
		perror("Connection Refused");
		return -1;
	} 

	puts("Client Connected\n");



	const char* message = "\n __      __      ___.     _________                   \n/  \\    /  \\ ____\\_ |__  /   _____/ ______________  __\n\\   \\/\\/   // __ \\| __ \\ \\_____  \\_/ __ \\_  __ \\  \\/ /\n \\        /\\  ___/| \\_\\ \\/        \\  ___/|  | \\/\\   / \n  \\__/\\  /  \\___  >___  /_______  /\\___  >__|    \\_/  \n       \\/       \\/    \\/        \\/     \\/             \n                                            ________________________\n  _______________________-------------------                        `\\\n /:--__                                                              |\n||< > |                                   ___________________________/\n| \\__/_________________-------------------                         |\n|                                                                  |\n |                             { WELCOME }                         |\n |                                                                  |\n |                        Bonjour cher Client,                      |\n  |        Vous êtes désormais connecté à ce magnifique serveur !    |\n  |      Grâce à ce serveur vous pouvez envoyer des messages         |\n  |        à vous même et faire pleins d'autres trucs,               |\n  |      à vous de le découvrir ! ;)                                  |\n   |                                                                  |\n   |                               /)/)                               |\n   |                              (^.^)                              |\n  |                               (n_n)o         ____________________|_\n  |  ___________________-------------------------                      `\\\n  |/`--_                                                                 |\n  ||[ ]||                                            ___________________/\n   \\===/___________________--------------------------\n\n\n"; 

	if (write(socket_client, message, strlen(message)) == -1) {
		perror("write1 error");
		return -1;
    }

	char msg_ent[100];
	int lecture;
	initialiser_signaux() ;
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

void initialiser_signaux(void) { 	
	puts("Signal Initialized\n");
	if (signal(SIGPIPE, SIG_IGN) == SIG_ERR) {
		perror(" signal ");
	}		
}
