#include <stdio.h>

int main() {
  int no_frames, i, pos, j, k;
  printf("\nEnter no of frames : ");
  scanf("%d", &no_frames);
  int frame[no_frames];

  for(i = 0; i < no_frames; ++i)
    frame[i] = -1;

  int n, hit = 0;
  int hits = 0, faults = 0, allocated = 0;
  printf("\nEnter no of references : ");
  scanf("%d", &n);

  int reference[n];
  printf("\nEnter the reference string : ");
  for(i = 0; i < n; ++i)
    scanf("%d", reference+i);

  for(i = 0; i < n; ++i) {

    hit = 0, allocated = 0;
    for(j = 0; j < no_frames; ++j) {
      if(frame[j] == -1){
        frame[j] = reference[i];
        allocated = 1;
        printf("\nFault ");
        faults++;
        break;
      }

      if(frame[j] == reference[i] && !allocated){
        printf("\nHit   ");
        hit = 1;
        hits++;
        break;
      }
    }
    if(!hit && !allocated) {
      faults++;
      printf("\nFault ");
      int dis = i;
      for(k = 0; k < no_frames; ++k){
        for(j = i+1; j >= 0; --j) {
          if(frame[k] == reference[j]) {
            if(j < dis){
              dis = j;
              pos = k;
            }
            break;
          }
        }
        if(j == 0){
          dis = 0;
          pos = k;
          break;
        }
      }
      frame[pos] = reference[i];
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
