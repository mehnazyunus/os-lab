#include <stdio.h>
#define N 100

struct process {
  int id;
  int burst;
  int wait;
  int turn;
  int arrival;
  int rem;
  int comp;
  int inq; //check whether process is in queue or not
};

int queue[N];
int front = -1, rear = -1;

void enqueue(int data) {
  if(front == -1) 
    front = rear = 0;
  else
    rear = (rear + 1)%N;
  queue[rear] = data;
}

int dequeue() {
  if(front == -1)
    return -1;
  int del = queue[front];
  if(front == rear)
    front = rear = -1;
  else 
    front = (front+1)%N;
  return del;
}

void sort(struct process a[], int n) {
  
  for(int i = 0; i < n; ++i) {
    int pos = i, small = a[i].arrival;
    for(int j = i; j < n; ++j){
      if(a[j].arrival < small) {
        small = a[j].arrival;
        pos = j;
      }
    }
    struct process t = a[i];
    a[i] = a[pos];
    a[pos] = t;
  }
}

int main() {
  
  int n, i, tq, j, k;
  float twait = 0, tturn = 0;
  int done = 0;

  printf("\nEnter no of processes : ");
  scanf("%d", &n );
  
  struct process p[n];
  printf("\nEnter process ID, burst time, arrival time : ");
  for(j = 0; j < n; ++j) {
 
    scanf("%d",&p[j].id);
    scanf("%d",&p[j].burst);
    scanf("%d", &p[j].arrival);
    p[j].rem = p[j].burst;
    p[j].inq = 0;
 
  }

  printf("\nEnter time quantum : ");
  scanf("%d", &tq);
 
  sort(p,n); //sort according to arrival times
 
  int time = 0;
  enqueue(p[0].id); //enqueue the job which arrives first
 
  while(done < n) {
      int curid = dequeue(); //id of the job is dequeued
      int cur;
    
      for(i = 0; i < n; ++i) //find the index of the dequeued job
        if(p[i].id == curid)
          cur = i;
      p[cur].inq = 0;
      
      if(p[cur].rem <= tq) { //the job can be completed in this time quantum
        time += p[cur].rem; 
               
        p[cur].rem = 0;
        p[cur].comp = time;
        p[cur].turn = p[cur].comp - p[cur].arrival;
        p[cur].wait = p[cur].turn - p[cur].burst;
        done++;
        
        for(i = 0; i < n; ++i){ //enqueue the jobs which arrive during the quantum
          if(!p[i].inq && p[i].rem != 0 && p[i].arrival <= time && i != cur) {
            p[i].inq = 1;
            enqueue(p[i].id);
          }
        }
     
      }

      else { //the job cannot be completed so it is executed for time tq and then put back in the queue after the jobs which arrive in this quantum
        time += tq;
        p[cur].rem -= tq; //decrement the remaining time 
        
        for(i = 0; i < n; ++i){ //enqueue the jobs which arrive during the quantum
          if(!p[i].inq && p[i].rem != 0 && p[i].arrival <= time && i != cur){
            p[i].inq = 1;
            enqueue(p[i].id);
          }
         } 
         
        enqueue(p[cur].id); //enqueue the current job
        p[cur].inq = 1;
      }
  }
  
  printf("\nProcess ID\tBurst time\tWaiting time\tTurnaround time\tCompletion time");
  for(int i = 0; i < n; ++i) {
    twait += p[i].wait;
    tturn += p[i].turn;
    printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d", p[i].id, p[i].burst, p[i].wait, p[i].turn, p[i].comp);
  }
  printf("\nAverage waiting time : %.2f", twait/(float)n);
  printf("\nAverage turnaround time : %.2f", tturn/(float)n);
}