#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#include <sys/wait.h>
void main() {
	fork();
	printf("Hello\n");
	//wait(NULL);
	printf("World\n");
}
