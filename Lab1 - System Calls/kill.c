#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

void main() {
	
  int ppid = getppid();
  kill(ppid, SIGKILL);
}
