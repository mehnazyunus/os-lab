#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define PORT 3200
#define MAXPENDING 5

int main() {

	//variables
	int sockfd; //return value of socket function
	int clientSock; //socket that holds connection
	int rval;
	char buff[1024];
	char msg[300];

	struct sockaddr_in serverAddr;
	struct sockaddr_in clientAddr;


	//create socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0); //af_inet : tcp/ip socket
	if(sockfd < 0){
		perror("Failed to create socket");
		exit(0);
	}
	printf("\nSocket created");

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_port = htons(PORT);

	//call bind
	if(bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
		perror("Bind failed");
		exit(0);
	}
	printf("\nBind successful");

	//listen
	if(listen(sockfd, MAXPENDING) < 0) {
		perror("\nError in listening");
		exit(0);
	}
	printf("\nServer running...\n");

	int sz = sizeof(clientAddr);
	//accept
	clientSock = accept(sockfd, (struct sockaddr *) &clientAddr, &sz);
	if(clientSock == -1) {
		perror("Accept failed");
		exit(0);
	}
    printf("\nConnection established\n");
		//memset(msg, '\0', 1024);
    while(strcmp(msg, "exit"))
	{
        memset(buff, '\0', 1024);
				//memset(msg, '\0', 1024);
		printf("\tSERVER : ");
		scanf("%s",msg);

		send(clientSock, msg, strlen(msg)+1, 0);
		rval = read(clientSock, buff, 1024);

		printf("\tCLIENT : %s\n", buff);
	}


	return 0;
}
