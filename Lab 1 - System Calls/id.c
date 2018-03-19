#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>

void main() {
	char c;
	start :
	printf("UID : %d\nEUID: %d\nPID : %d\nPPID : %d\nGID : %d\nEGID : %d", getuid(), geteuid(), getpid(), getppid(), getgid(), getegid());
	
	printf("\nDo you want to exit ? ");
	scanf("%c", &c);
	if(c == 'y')
		exit(0);
	else
		goto start;
}
