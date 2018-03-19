#include <stdio.h>
#define N 100

struct process {
	int id;
	int size;
};

struct partition {
	int pid;
	int size;
};

int memory, n=0, total=1; // n - no of processes, total- no of partitions


struct process p[N];
struct partition part[N];

int fragment(int n) {
	int i, ext = 0;
	for(i = 0; i < total; ++i) {
		
		if(part[i].pid == -1)
			ext += part[i].size;
	}
	return ext;	
}

int find() {
	int i;
	
	for(i = 0; i < total; ++i)
		if(part[i].size >= p[n].size && part[i].pid == -1)//not allocated
			return i;
	return -1;	
}

int insert(int pos) {
	
	int i;
	for(i = total; i > pos; --i)
		part[i] = part[i-1];

	part[i].size = p[n].size;
	part[i].pid = p[n].id;

	part[i+1].size -= part[i].size;
	total++;
}

int removepart(int pos){
	part[pos].pid = -1;

	//if next partition is unallocated, combine
	if(pos != total-1 && part[pos+1].pid == -1){
		int i;
		part[pos].size += part[pos+1].size;
		for(i = pos+1; i < total-1; ++i)
			part[i] = part[i+1];
		total--;
	}

	//if previous partition is unallocated, combine
	if(pos != 0 && part[pos-1].pid == -1) {
		int i;
		part[pos-1].size += part[pos].size;
		for(i = pos; i < total-1; ++i)
			part[i] = part[i+1];
		total--;
	}

}

int main() {
	int c, rem;
	printf("\nEnter total memory size : ");
	scanf("%d", &memory);
	rem = memory;

	part[0].pid = -1; //not allocated
	part[0].size = memory; 

	do {
		printf("\n\n1.Process enters memory 2.Process leaves memory 3.Exit \nEnter your choice : ");
		scanf("%d", &c);
		if(c == 1) {
			printf("\nEnter size of process %d: ", n);
			scanf("%d", &p[n].size);
			p[n].id = n;

			int pos = find();
			
			if(pos == -1) {
				int ext = fragment(n);
				printf("\nContiguous memory not available. External fragmentation : %d", ext);
			}
			else if(part[pos].size == p[n].size) {
				part[pos].pid = n;
				rem -= p[n].size;
				printf("\nMemory allocated");
			}
			else {
				insert(pos);
				rem -= p[n].size;
				part[pos].pid = n;
				printf("\nMemory allocated");
			}
			printf("\nMemory remaining : %d", rem);
			n++;
		}
		if(c == 2) {
			int id;
			printf("\nEnter id of process to be removed : ");
			scanf("%d", &id);
			int i;
			for(i = 0;i < total; ++i)
				if(part[i].pid == id) {
					removepart(i);
					rem += part[i].size;
				}
			printf("\nMemory remaining : %d", rem);
		}
	}while(c != 3);
}