#include <stdio.h>
#include <stdlib.h>
int p, r; //no of processes and resources
int available[100];
int max[100][100]; //max no of instances of each resource that a process demands
int allocated[100][100]; //no of instances of each resource currenly allocated
int need[100][100]; //Remaining resource need of each process
//Max = Allocated + Need
int work[100];
int safe[100];

int safety() {
  int i, j;
  int finish[p];
  
  for(i = 0; i < p; i++)
    for(j = 0; j < r; ++j)
      need[i][j] = max[i][j] - allocated[i][j];

  for(i = 0; i < p; ++i)
    finish[i] = 0;


	for(i = 0; i < r; ++i)
		work[i] = available[i];

  int done = 0;
  while(done < p) {
    int found = 0;
    int cur;
    for(i = 0; i < p; ++i) {
      if(!finish[i]) {
        int j;
        for(j = 0; j < r; ++j)
          if(!(need[i][j] <= work[j]))
            break;
        if(j == r) { //need < work for all resources
          int k;
		      for(k = 0; k < r; ++k) 
             work[k] += allocated[i][k];
          		       
          found = 1;  
          finish[i] = 1;
          safe[done++] = i;
        }
      }
    }
    if(!found) {
      int j;
      for(j = 0; j < p; ++j)
        if(!finish[j]) 
          break;
      if(j < p) {
        printf("\nNo safe state exists");
        return 0;
      }
    }
  }
  printf("\nSafe sequence : ");
  int k;
  for(k = 0; k < p; ++k)
    printf("%d ", safe[k]);
	return 1;
}

void request() {
  int id, i;
  int req[r];
  printf("\nEnter process number(zero indexed)");
  scanf("%d", &id);
  printf("\nEnter the request");
  for(i = 0; i < r; ++i)
    scanf("%d", &req[i]);

  for(i = 0; i < r; ++i) 
    if(req[i] > need[id][i]) {
      printf("\nError. Request greater than need"); 
      return;
    }
  for(i = 0; i < r; ++i)
    if(req[i] > available[i]) {
      printf("\nResources unavailable");
      return;
    }
  for(i = 0; i < r; ++i) {
    available[i] -= req[i];
    allocated[id][i] += req[i];
    need[id][i] -= req[i];
  }  
	
  int x = safety();
  if(x == 0){
    printf("\nNo safe sequence now " );
    exit(0);
  }
}      

int main() {
  
  int i, j;
  printf("\nEnter no of processes and resources : ");
  scanf("%d%d", &p, &r);  

  printf("\nEnter maximum instances of each resource available");
  for(i = 0; i < r; ++i) {
    scanf("%d", &available[i]);
    work[i] = available[i];
  }

  printf("\nEnter the maximum resources required for each process: ");
  for(i = 0; i < p; i++)
    for(j = 0; j < r; ++j)
      scanf("%d", &max[i][j]);

  printf("\nEnter the allocated resources : ");
  for(i = 0; i < p; i++)
    for(j = 0; j < r; ++j)
      scanf("%d", &allocated[i][j]);

  int x = safety();
  if(x) {
    int c;
  	do {
      request();
      printf("\nDo you want to check more processes ? (0/1)");
      scanf("%d", &c);  
    }while(c == 1);
  }
  return 0;
}
