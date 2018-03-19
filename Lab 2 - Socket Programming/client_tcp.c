#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 3000
#define SERVER "127.0.0.1"

int main() {
	int clientSock;
	int msgLen;
	char msg[1024];
	char buffer[1024];

	struct sockaddr_in serverAddr;

	/*Create a TCP socket */
	clientSock = socket(AF_INET, SOCK_STREAM, 0);
	if(clientSock < 0) {
		perror("socket() failed");
		exit(0);
	}

	serverAddr.sin_family = AF_INET; //Internet address family
	inet_addr(SERVER, serverAddr.sin_addr); //Server IP address
	serverAddr.sin_port = htons(PORT); //Server port

	/*Connect to server */
	if(connect(clientSock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
		perror("connect() failed");
		exit(0);
	}

	//msgLen = strlen(msg);
	while(strcmp(msg, "exit"))
	{
               // bzero(buffer,sizeof(buffer));
		int valread = read(clientSock, buffer, 1024);
		if(valread != -1)
			printf("\tSERVER : %s\n", buffer);

		printf("\tCLIENT : ");
		scanf("%s",msg);

		send(clientSock, msg, strlen(msg), 0);
	}

	return 0;
}
