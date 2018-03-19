#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>

void main() {
	fork();
	fork();
	fork();
	fork();
	printf("Hello\n");
}
