#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "socket.h"

int socket_server;

socket_server = socket(AF_INET, SOCK_STREAM, 0);

if (socket_server == -1) {
	perror("socket_server");
}

struct sockaddr_in saddr;
saddr.sin_family = AF_INET;
saddr.sin_port = htons(8080);
saddr.sin_addr.s_addr = INADDR_ANY;

int socket_bind;

socket_bind = bind(socket_server, (struct sockaddr *)&saddr, sizeof(saddr)) == -1) {
	perror("bind socket_server");
}

if (listen(socket_serveur,10) == -1) {
	perror ("listen socket_server");
}


int socket_client;
socket_client = accept(socket_server, NULL, NULL);
if (socket_client == -1) {
	perror("accept");
}

