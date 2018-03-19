#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>

#define PORT 3000

int main() {
	int servSock;
	int len;
	int rsize;
	char msg[100];
	char buff[1024];
	struct sockaddr_in servAddr;
	struct sockaddr_in clientAddr;

	servSock = socket(AF_INET, SOCK_DGRAM, 0);
	if(servSock < 0) {
		perror("socket() failed");
		exit(0);
	}
	printf("\nSocket created");

	servAddr.sin_family = AF_INET; /*Internet address family*/
	servAddr.sin_port = htons(PORT);
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY); /*Any incoming interface*/

	if(bind(servSock, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0) {
		perror("bind() failed");
		exit(0);
	}
	printf("\nBind successful\n\n");

		while(1) {
		int sz = sizeof(servAddr);
		rsize = recvfrom(servSock, buff, sizeof(buff),0,(struct sockaddr*)&clientAddr, &sz );
		if(rsize != 0)
				printf("\nCLIENT : %s", buff);
		printf("\nSERVER : ");
		scanf("%s", msg);
		sendto(servSock, msg, sizeof(msg), 0,(struct sockaddr*)&clientAddr, sz);
	}
		close(servSock);

	return 0;
}
