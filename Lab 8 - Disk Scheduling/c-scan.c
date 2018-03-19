#include <stdio.h>

int main() {
  int n, i, j, time = 0, initial, max, c, prev;

  printf("\nEnter total no of requests : " );
  scanf("%d", &n);

  int request[n];
  printf("\nEnter the previous request : ");
  scanf("%d", &prev);

  printf("\nEnter the initial position : ");
  scanf("%d", &initial);

  printf("\nEnter cylinder size : ");
  scanf("%d", &max);
  max--;

  printf("\nEnter the requests : " );
  for(i = 0; i < n; ++i)
    scanf("%d", &request[i]);

  int dif = initial-prev;
  if(dif < 0)
      c = 1;
  else
      c = 2;

  printf("\nPath : %d->", initial);
  if(c == 2) { //right
    for(i = initial; i <= max; ++i)
      for(j = 0; j < n; ++j)
        if(request[j] == i)
          printf("%d->", i);

    printf("%d->0->", max);

    for(i = 0; i <= initial; ++i)
      for(j = 0; j < n; ++j)
        if(request[j] == i)
          printf("%d->", i);

    time = max;
  }
  else if(c == 1) { //left
    for(i = initial; i >= 0; --i)
      for(j = 0; j < n; ++j)
        if(request[j] == i)
          printf("%d->", i);

    printf("0->%d->", max);

    for(i = max; i >= initial; --i)
      for(j = 0; j < n; ++j)
        if(request[j] == i)
          printf("%d->", i);

    time = max;
  }

  printf("\nSeek time : %d\n", time);
}
