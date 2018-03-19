#include <stdio.h>

int main() {
  int n, i, j, time = 0, initital, max, c, prev;

  printf("\nEnter total no of requests : " );
  scanf("%d", &n);

  int request[n];
  printf("\nEnter the previous request : ");
  scanf("%d", &prev);

  printf("\nEnter the initital position : ");
  scanf("%d", &initital);

  printf("\nEnter cylinder size : ");
  scanf("%d", &max);
  max--;
  printf("\nEnter the requests : " );
  for(i = 0; i < n; ++i)
    scanf("%d", &request[i]);

  int dif = initital-prev;
  if(dif < 0)
      c = 1;
  else
      c = 2;

  int first = max, last = 0;
  for(i = 0; i < n; ++i)
    if(request[i] < first)
      first = request[i];

  for(i = 0; i < n; ++i)
    if(request[i] > last)
      last = request[i];

  printf("\nPath : %d->", initital);
  if(c == 2) {
    for(i = initital; i <= last; ++i)
      for(j = 0; j < n; ++j)
        if(request[j] == i)
          printf("%d->", i);

    for(i = initital; i >= first; --i)
      for(j = 0; j < n; ++j)
        if(request[j] == i)
          printf("%d->", i);

    time = last - initital + last - first;
  }
  else if(c == 1) {
    for(i = initital; i >= 0; --i)
      for(j = 0; j < n; ++j)
        if(request[j] == i)
          printf("%d->", i);

    for(i = initital; i <= max; ++i)
      for(j = 0; j < n; ++j)
        if(request[j] == i)
          printf("%d->", i);

    time = initital - first + last - first;
  }

  printf("\nSeek time : %d\n", time);
}
