#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>

#define PORT 3000
#define SERVER "127.0.0.1"

int main() {
	int clientSock;
	int len;
	int rsize;
	char msg[100];
	char buff[1024];
	struct sockaddr_in servAddr;

	clientSock = socket(AF_INET, SOCK_DGRAM, 0);
	if(clientSock < 0) {
		perror("socket() failed");
		exit(0);
	}
	printf("\nSocket created");

	servAddr.sin_family = AF_INET; /*Internet address family*/
	//clientAddr.sin_addr.s_addr = htonl(INADDR_ANY); /*Any incoming interface*/
	servAddr.sin_port = htons(PORT);
	inet_aton(SERVER, &servAddr.sin_addr);
	int sz = sizeof(servAddr);
	//while(strcmp(msg, "exit")) {
	while(1) {
		printf("\nCLIENT : ");
		scanf("%s", msg);
		sendto(clientSock, msg, sizeof(msg),0,(struct sockaddr*)&servAddr, sizeof(servAddr));
		rsize = recvfrom(clientSock, buff, sizeof(buff), 0, (struct sockaddr*)&servAddr, &sz);
		if( rsize != -1) {
			printf("\nSERVER : %s", buff);
		}
	}
		close(clientSock);

	return 0;
}
