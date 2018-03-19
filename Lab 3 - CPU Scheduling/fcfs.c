#include <stdio.h>
struct process {
  int id;
  int burst;
  int wait;
  int turn;
  int arrival;
};

void sort(struct process a[], int n) {
  int i, j;
  for(i = 0; i< n; ++i) {
    for(j = 0; j < n-i-1; ++j) {
      if(a[j].arrival > a[j+1].arrival){
        struct process p = a[j];
        a[j] = a[j+1];
        a[j+1] = p;
      }
    }
  }
}

int main() {
  int n, i;
  printf("\nEnter no of processes : ");
  scanf("%d", &n );
  struct process p[n];

  printf("\nEnter process burst time, arrival time : ");
  for(i = 0; i < n; ++i) {
    scanf("%d",&p[i].burst);
    scanf("%d", &p[i].arrival);
    p[i].id = i+1;
  }

  sort(p, n);

  p[0].wait = 0;
  p[0].turn = p[0].burst;
  int comp = p[0].burst + p[0].arrival;
  for(i = 1; i< n; ++i){
    if(p[i].arrival - comp > 0)
      comp = p[i].arrival;
    comp += p[i].burst;
    p[i].turn = comp - p[i].arrival;
    p[i].wait = p[i].turn - p[i].burst;
  }
  int twait = 0, tturn = 0;
  for(i = 0; i < n; ++i) {
    twait += p[i].wait;
    tturn += p[i].turn;
  }

  printf("\nProcess ID\tArrival time\tBurst time\tWait time\tTurnaround time");
  for(i = 0; i < n; ++i)
    printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d", p[i].id, p[i].arrival, p[i].burst, p[i].wait, p[i].turn);

  printf("\nAverage turnaround time : %.2f\nAverage waiting time : %.2f", twait/(float)n, tturn/(float)n);
}
