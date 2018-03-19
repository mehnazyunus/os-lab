#include <stdio.h>
#include <limits.h>
struct process {
	int id;
	int arrival;
	int burst;
	int wait;
	int turn;
	int comp;
	int arrived;
	int rem;
};

void sort(struct process p[], int n) {
	int i, j;
	for(i = 0; i < n; ++i) {
		for(j = 0; j < n-i-1; ++j) {
			if(p[j].arrival > p[j+1].arrival) {
				struct process t = p[j];
				p[j] = p[j+1];
				p[j+1] = p[j];
			}
		}
	}
}

int main() {
	int n, i;
	printf("\nEnter the no of processes : ");
	scanf("%d", &n);
	struct process p[n];
	printf("\nEnter process ID, arrival time, burst time : ");
	for(i = 0; i < n; ++i) {
		scanf("%d%d%d", &p[i].id, &p[i].arrival, &p[i].burst);
		p[i].rem = p[i].burst;
	}

	sort(p, n);

	int cur;
	int done = 0, time = 0, j;
	int minburst = INT_MAX;
	int check = 0;
	while(done < n) {

		for(j = 0; j < n; ++j) {
			if(p[j].arrival <= time && p[j].rem < minburst && p[j].rem != 0) {
				cur = j;
				minburst = p[j].rem;
				check = 1;
			}
		}
		if(check == 0) {
			printf("\nTime : %d Current : %d", time, p[cur].id);
			time++;
			continue;
		}
		p[cur].rem --;
		minburst = p[cur].rem;
		
		if(p[cur].rem == 0) {
			done++;
			minburst = INT_MAX;
			p[cur].comp = time + 1;
			p[cur].turn = p[cur].comp - p[cur].arrival;
			p[cur].wait = p[cur].turn - p[cur].burst;
		}
		printf("\nTime : %d Current : %d", time, p[cur].id);
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
