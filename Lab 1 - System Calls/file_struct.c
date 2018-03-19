#include <unistd.h>
#include <fcntl.h> //read and write permissions
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>

int main () {
	
	int filed = creat("file1.txt", S_IRWXU);
	char str[100];
	int filedes = open("file2.txt", O_CREAT | O_RDWR, S_IRWXU);
	if(filedes < 0)
	  perror("\nError");
	else
	  printf("File opened with file descriptor : %d\n", filedes);

	int old = umask(0022);
	printf("\nOld mode : %d", old);

	if(link("file2.txt", "file3.txt") < 0)
	  perror("Error");
	else
	  printf("\nFile linked");

	if(unlink("file2.txt") < 0)
	  perror("Error");
	else
	  printf("\nFile unlinked");

	int copy = dup(filedes);

	if(access("file3.txt", F_OK) == 0)
	  printf("\nFile exists\n");
	else
	  printf("\nFile does not exist");

	if(chmod("file3.txt", S_IRGRP | S_IWGRP | S_IRWXU) < 0)
	  perror("Error");
	else
	  printf("\nPermissions changed");

	int ch = chown("file3.txt", 1001, 1004);
	if(ch < 0)
	  perror("Error");

	int sizew = write(filedes, "Hello world!\n", sizeof("Hello world!\n"));
	printf("\nWrite returns %d\n", sizew);

	lseek(filedes, -5, SEEK_CUR);

	int sizer = read(filedes, str, 11);
	str[11] = '\0';
	printf("\nData read : %s\nReturned : %d\n", str, sizer);
	close(filedes);
}
