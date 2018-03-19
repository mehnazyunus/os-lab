#include <stdio.h>
#include <unistd.h>

int main() {
  printf("\nExecuting using execl");
  execl("./hello", "./hello", NULL);
  printf("\nEnd");
  return 0;
}
