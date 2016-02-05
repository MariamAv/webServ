#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "socket.h"

int socket_server;

int create_server(int port) {

	socket_server = socket(AF_INET, SOCK_STREAM, 0);

	if (socket_server == -1) {
		perror("socket_server");
		return -1;
	}
	struct sockaddr_in saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port);
	saddr.sin_addr.s_addr = INADDR_ANY;

	int socket_bind;

	socket_bind = bind(socket_server, (struct sockaddr *)&saddr, sizeof(saddr));
	if (socket_bind == -1) {
		perror("bind socket_server");
		return -1;
	}
	
	return 0;
}

int create_listen() {
	if (listen(socket_server,10) == -1) {
		perror ("listen socket_server");
		return -1;
	}
	return 0;
}

int create_client() {

	int socket_client;
	socket_client = accept(socket_server, NULL, NULL);
	if (socket_client == -1) {
		perror("accept");
		return -1;
	}
	return 0;
}
