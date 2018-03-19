#include <stdio.h>
#include <stdlib.h>

int main() {
  int n, i, time = 0, initital;
  printf("\nEnter total no of requests : " );
  scanf("%d", &n);
  int request[n];
  printf("\nEnter the initital position : ");
  scanf("%d", &initital);
  printf("\nEnter the requests : " );
  for(i = 0; i < n; ++i)
    scanf("%d", &request[i]);
  time = abs(request[0] - initital);
  printf("\nPath : %d->", initital);
  for(i = 0; i < n-1; ++i) {
    printf("%d->", request[i]);
    //printf("\n%d time: %d", abs(request[i] - request[i+1]), time);
    time += abs(request[i] - request[i+1]);
  }
  printf("%d", request[n-1]);
  printf("\nSeek time : %d\n", time);
}
