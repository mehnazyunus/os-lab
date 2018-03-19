#include <stdio.h>
#include <stdlib.h>

struct request {
  int no;
  int served;
};

int main() {
  int n, i, j, time = 0, initital, max, c, prev;

  printf("\nEnter total no of requests : " );
  scanf("%d", &n);

  struct request r[n];
  //printf("\nEnter the previous request : ");
  //scanf("%d", &prev);

  printf("\nEnter the initital position : ");
  scanf("%d", &initital);

  printf("\nEnter cylinder size : ");
  scanf("%d", &max);
  max--;

  printf("\nEnter the requests : " );
  for(i = 0; i < n; ++i) {
    scanf("%d", &r[i].no);
    r[i].served = 0;
  }  

  printf("\nPath : %d-> ", initital);
  int cur = initital;
  int pos;

  for(j = 0; j < n; ++j) {
    int shortest = max;
    for(i = 0; i < n; ++i){
      if(abs(cur - r[i].no) < shortest && !r[i].served) {
        shortest = abs(cur - r[i].no);
        pos = i;
      }
    }
    cur = r[pos].no;
    r[pos].served = 1;
    time += shortest;
    printf("%d-> ", r[pos].no);
  }
  printf("\nSeek time : %d\n", time);
}
