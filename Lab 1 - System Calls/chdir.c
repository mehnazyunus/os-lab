#include <unistd.h>
#include <fcntl.h> //read and write permissions
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>

int main() {
	
	int filedes = open("file2.txt", O_CREAT | O_RDWR, S_IRWXU);
   	chdir("/home/student/16co124/os lab/file2.txt");
    printf("\nDirectory changed ");
    execlp("pwd", "pwd", NULL);
}
