// Pagetable implementation
#include <stdio.h>
#include <stdlib.h>

int main() {
  int phy_mem, log_mem, pg_size;
  printf("\nEnter the physical memory size : ");
  scanf("%d", &phy_mem);
  printf("\nEnter the logical memory size : ");
  scanf("%d", &log_mem);
  printf("\nEnter page size : ");
  scanf("%d", &pg_size);

  int no_frames = phy_mem/pg_size;
  int no_pages = log_mem/pg_size;

  int pagetable[no_pages];
  int i, j;

  printf("\nEnter the page table entries: ");
  for(i = 0; i < no_pages; ++i) {

    printf("\nEntry %d : ", i);
    scanf("%d", &pagetable[i]);

    if(pagetable[i] >= no_frames){
      printf("\nFrame %d does not exist\n", pagetable[i]);
      i--;
    }

    for(j = 0; j < i ; ++j){
      if(pagetable[i] == pagetable[j] && pagetable[i] != -1){
        printf("\nMultiple pages map to same frame\n");
        i--;
      }
    }
  }
  int c;
  do{
    int log_add;
    printf("\nEnter logical address: ");
    scanf("%d", &log_add);
    int frame_no = pagetable[log_add/pg_size];

    if(frame_no != -1) {
      int offset = log_add % pg_size;
      int phy_add = frame_no*pg_size + offset;
      printf("\nPhysical address : %d", phy_add);
    }
    else {
      printf("\nPage table entry does not exist");
    }
    printf("\nDo you want to continue?(0/1)");
    scanf("%d", &c);
  }while(c == 1);
}
