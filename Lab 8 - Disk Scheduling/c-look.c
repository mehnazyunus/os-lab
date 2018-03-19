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

  int first = max, last = 0, midf = 0, midl = max;
  for(i = 0; i < n; ++i)
    if(request[i] < first)
      first = request[i];

  for(i = 0; i < n; ++i)
    if(request[i] > last)
      last = request[i];

  for(i = 0; i < n; ++i)
    if(request[i] > midf && request[i] >= first && request[i] <= initial)
      midf = request[i];

  for(i = 0; i < n; ++i)
    if(request[i] < midl && request[i] >= initial && request[i] <= last)
      midl = request[i];


  printf("\nPath : %d->", initial);
  if(c == 2) { //right
    for(i = initial; i <= last; ++i)
      for(j = 0; j < n; ++j)
        if(request[j] == i)
          printf("%d->", i);

    for(i = first; i <= midf; ++i)
      for(j = 0; j < n; ++j)
        if(request[j] == i)
          printf("%d->", i);

    time = last - initial + midf - first;
  }
  else if(c == 1) { //left
    for(i = initial; i >= first; --i)
      for(j = 0; j < n; ++j)
        if(request[j] == i)
          printf("%d->", i);

    for(i = last; i >= midl; --i)
      for(j = 0; j < n; ++j)
        if(request[j] == i)
          printf("%d->", i);

    time = initial - first + last - midl;
  }

  printf("\nSeek time : %d\n", time);
}
