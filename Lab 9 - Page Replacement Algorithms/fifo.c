//Page replacement algorithm : FIFO
#include <stdio.h>

int main() {
  int no_frames, i, pos = 0;
  printf("\nEnter no of frames : ");
  scanf("%d", &no_frames);
  int frame[no_frames];

  for(i = 0; i < no_frames; ++i)
    frame[i] = -1;

  int n, hit = 0;
  int hits = 0, faults = 0;
  printf("\nEnter no of references : ");
  scanf("%d", &n);

  int input[n];
  printf("\nEnter the reference string : ");
  for(i = 0; i < n; ++i)
    scanf("%d", input+i);
    
  for(i = 0; i < n; ++i) {
    hit = 0;
    int j;
    for(j = 0; j < no_frames; ++j) {
      if(frame[j] == input[i]){
        printf("\nHit   ");
        hit = 1;
        hits++;
        break;
      }
    }
    if(!hit){
      printf("\nFault ");
      faults++;
      frame[pos] = input[i];
      pos++;
      if(pos == no_frames)
        pos = 0;
    }
    printf(" Entries : ");
    for(j = 0; j < no_frames; ++j) {
      if(frame[j] == -1)
        printf("- ");
      else
        printf("%d ", frame[j]);
    }
  }
  printf("\nNo of hits : %d\nNo of faults : %d\n", hits, faults);
}
