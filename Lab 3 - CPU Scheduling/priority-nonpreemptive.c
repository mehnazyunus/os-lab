#include <stdio.h>
#include <limits.h>

struct process  {
	int id;
	int turn;
	int comp;
	int wait;
	int arrival;
	int burst;
	int rem;
	int priority; //lower number means higher priority 
};

int main () {
	int n, i;
	printf("\nEnter no of processes : ");
	scanf("%d", &n);
	struct process p[n];
	printf("\nEnter process ID, burst time, arrival time, priority : ");
	for(i = 0; i < n; ++i) {
		scanf("%d%d%d%d", &p[i].id, &p[i].burst, &p[i].arrival, &p[i].priority);
		p[i].rem = p[i].burst;
	}

	int done = 0, time = 0;
	int minp = INT_MAX;
	int cur = -1;
	//int check = 0;
	int executing = 0;
	while(done < n) {

		if(!executing) {
			for(i = 0; i < n; ++i) {
				if(p[i].arrival <= time && p[i].priority < minp && p[i].rem != 0) {
					minp = p[i].priority;
					cur = i;
					executing = 1;
				}
			}
		}
		if(cur != -1)
			printf("\nTime : %d Current : %d", time, p[cur].id);	
		if(!executing) {
			time++;
			continue;
		}
		p[cur].rem--;
		if(p[cur].rem == 0) {
			p[cur].comp = time+1;
			p[cur].turn = p[cur].comp - p[cur].arrival;
			p[cur].wait = p[cur].turn - p[cur].burst;
			executing = 0;
			done++;
			minp = INT_MAX;
		}
		time++;
	}

	int tturn = 0, twait = 0;
	printf("\nProcess ID\tArrival time\tBurst time\tTurnaround tie\tCompletion time\tWaiting time");
	for(i = 0; i < n; ++i) {
		tturn += p[i].turn;
		twait += p[i].wait;
		printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d", p[i].id, p[i].arrival, p[i].burst, p[i].turn, p[i].comp, p[i].wait);
	}
	printf("\nAverage waiting time : %.2f\nAverage turnaround time : %.2f", (float)twait/n, (float)tturn/n);
	
	return 0;
}