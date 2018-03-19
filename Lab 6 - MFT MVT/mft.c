#include <stdio.h>
struct process {
  int id;
  int mem;
  int part; //partition allocated
  int ext;
};

struct partition {
  int size;
  int id;
  int allocated;
  int fragment;
};

void sort(struct partition p[], int n) {
  int i, j;
  for(i = 0; i < n; ++i) {
    for(j = 0; j < n-i-1; ++j) {
      if(p[j].size > p[j+1].size) {
        struct partition t;
        t = p[j];
        p[j] = p[j+1];
        p[j+1] = t;
      }
    }
  }
}

int main() {
  int n, i, no_process, c; //no of partitions
  int total, entered = 0;
  printf("\nEnter total memory : ");
  scanf("%d", &total);
  printf("\nEnter no of partitions : " );
  scanf("%d", &n);
  int ext = 0;
  struct partition p[n];
  printf("\nEnter each partition size : ");
  for(i = 0; i < n; ++i) {
    scanf("%d", &p[i].size);
    p[i].id = i+1;
    p[i].allocated = 0;
    p[i].fragment = 0;
    ext += p[i].size;
    entered += p[i].size;
  }

  if(entered < total) {
    p[n].size = total - entered;
    p[n].id = n+1;
    p[n].allocated = 0;
    p[n].fragment = 0;
    ext += p[n].size;
    n++;
  }
  printf("\nSize of partition %d : %d", n, p[n-1].size);

  printf("\nEnter no of processes : ");
  scanf("%d", &no_process);

  struct process pro[no_process];
  printf("\nEnter memory required for each process : " );
  for(i = 0; i < no_process; ++i) {
    scanf("%d", &pro[i].mem);
    pro[i].id = i+1;
    pro[i].part = 0;
  }

  sort(p, n);

  int j;
  for(i = 0; i < no_process; ++i) {
    for(j = 0; j < n; ++j) {
      if(pro[i].mem <= p[j].size && !p[j].allocated){
        p[j].allocated = 1;
        p[j].fragment = p[j].size - pro[i].mem;
        pro[i].part = p[j].id; //allocated partition
        ext -= p[j].size;
        pro[i].ext = ext;
        break;
      }
    }
    if(j==n)
      pro[i].ext =ext;
  }

  printf("\nProcess ID\tMemory required\tAllocated\tPartition allocated\tExternal fragmentation");
  for(i = 0; i < no_process; ++i) {
    if(pro[i].part)
      printf("\n%d\t\t%d\t\tYES\t\t%d\t\t\t---", pro[i].id, pro[i].mem, pro[i].part);
    else
      printf("\n%d\t\t%d\t\tNO\t\t---\t\t\t%d", pro[i].id, pro[i].mem, pro[i].ext);
  }

  printf("\n\nInternal fragmentation\nPartition no\tFragment size");
  int external = 0, internal = 0;
  for(i = 0; i < n; ++i) {
    if(!p[i].allocated) {
      external += p[i].size;
      printf("\n%d\t\t---",p[i].id);
    }
    else {
      printf("\n%d\t\t%d",p[i].id, p[i].fragment);
      internal += p[i].fragment;
    }
  }

  //printf("\n\nTotal external fragmentation : %d", external);
  printf("\nTotal internal fragmentation : %d\n", internal);

  do {
    int id, frag;
    printf("\nEnter id of process which leaves : ");
    scanf("%d", &id);
    int partid =  pro[id-1].part;
    for(i = 0; i < n; ++i)
      if(p[i].id == partid)
        p[i].allocated = 0;

    printf("\nEnter memory required for new process : ");
    scanf("%d", &pro[no_process++].mem);
    pro[no_process-1].part = 0;

    for(j = 0; j < n; ++j) {
      if(pro[no_process-1].mem <= p[j].size && !p[j].allocated){
        //printf("\nj : %d, id: %d",j, p[j].id);
        p[j].allocated = 1;
        p[j].fragment = p[j].size - pro[no_process-1].mem;
        pro[no_process-1].part = p[j].id; //allocated partition
        frag = p[j].fragment;
        break;
      }
    }
    if(j < n) {
      printf("\nPartition %d allocated to process ", pro[no_process-1].part);
      printf("\nInternal fragmentation : %d", frag);
    }
    else
      printf("\nNo partition available");
    printf("\nContinue?(0/1)");
    scanf("%d", &c);
  }while(c);

}
