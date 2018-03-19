#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int i = 3;
void sig_handler(int signo) {
  printf("Handler called\n");
  i--;
  alarm(10);
}

int main(void) {
  signal(SIGALRM, sig_handler);
  alarm(10);
  while(i){}
  return 0;
}
