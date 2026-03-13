#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>
#define MAX 1000
#define max(a, b) ((a) > (b) ? (a) : (b))
int at[1000],bt[1000],n,pr[1000];

void fcfs(){
	int wt[1000], tat[1000], ct[1000];
	float awt = 0, atat = 0;
	ct[0] = at[0]+bt[0];
	tat[0] = ct[0] - at[0];
	wt[0] = tat[0] - bt[0];
	for(int i = 1; i<n; i++){
		ct[i] = max(ct[i-1],at[i])+bt[i];
		tat[i] = ct[i] - at[i];
		wt[i] = tat[i] - bt[i];
	}

	printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");

	for(int i = 0; i<n; i++){
		printf("%d\t%d\t%d\t%d\t%d\t%d\n",i+1,at[i],bt[i],ct[i],tat[i],wt[i]);
		awt+=wt[i];
		atat+=tat[i];
	}
	printf("\nAverage Waiting Time = %.2f\n", awt/n);
        printf("Average Turnaround Time = %.2f\n", atat/n);
}

void srtf(){
	int wt[1000], tat[1000], ct[1000], rt[1000];
	float awt = 0, atat = 0;
	int completed = 0, smallest = -1, time = 0;
	//initialize rt
	for(int i = 0; i < n; i++){
	    rt[i] = bt[i];
	}
	while(completed<n){
		smallest = -1;
		for(int i = 0; i<n; i++){
			if(at[i]<=time && rt[i]>0){
				if(smallest == -1 || rt[i]<rt[smallest]){
					smallest = i;
				}
			}
		}

		if(smallest == -1){
			time++;
			continue;
		}
		rt[smallest]--;
		time++;

		if(rt[smallest]==0){
			completed++;
			ct[smallest] = time;
		}
	}

	for(int i = 0; i<n; i++){
		tat[i] = ct[i] - at[i];
		wt[i] = tat[i] - bt[i];
		awt+=wt[i];
		atat+=tat[i];
	}

	printf("\nProcess\tAT\tBT\tCT\tWT\tTAT\n");

      for(int i=0;i<n;i++){
    	      printf("P%d\t%d\t%d\t%d\t%d\t%d\n",i+1,at[i],bt[i],ct[i],wt[i],tat[i]);
       }

       printf("\nAverage Waiting Time = %.2f",awt/n);
       printf("\nAverage Turnaround Time = %.2f\n",atat/n);
}

void sjf(){
	int completed = 0, smallest;
	int ct[1000], tat[1000], wt[1000];
	int time = 0;
	int rt[1000];
	float awt = 0, atat = 0;
	for(int i = 0; i<n; i++){
		rt[i] = bt[i];
	}
	while(completed<n){
		smallest = -1;
		for(int i = 0; i<n; i++){
			if(at[i]<=time && rt[i]){
				if(smallest==-1||rt[i]<rt[smallest]){
					smallest = i;
				}
			}
		}
		if(smallest == -1){
			time++;
			continue;
		}

		time+=rt[smallest];
		rt[smallest] = 0;
		ct[smallest] = time;
		completed++;
	}

	for(int i = 0; i<n; i++){
		tat[i] = ct[i] - at[i];
		wt[i] = tat[i] - bt[i];
		awt+=wt[i];
		atat+=tat[i];
	}
	printf("\nProcess\tAT\tBT\tCT\tWT\tTAT\n");

       for(int i=0;i<n;i++){
 	       printf("P%d\t%d\t%d\t%d\t%d\t%d\n",i+1,at[i],bt[i],ct[i],wt[i],tat[i]);
       }

       printf("\nAverage Waiting Time = %.2f",awt/n);
       printf("\nAverage Turnaround Time = %.2f\n",atat/n);
}
void priority_p(){
	int completed = 0, smallest, time = 0;
	int tat[1000], wt[1000], rt[1000], ct[1000];
	float awt = 0, atat = 0;

	for(int i = 0; i<n; i++){
		rt[i] = bt[i];
	}
	while(completed<n){
		smallest = -1;
		for(int i = 0; i<n; i++){
			if(at[i]<=time && rt[i]){
				if(smallest == -1 || pr[i]<pr[smallest]){
					smallest = i;
				}
			}
		}
		if(smallest == -1){
			time++;
			continue;
		}
		rt[smallest]--;
		time++;
		if(rt[smallest] == 0){
			completed++;
			ct[smallest] = time;
		}
	}

	for(int i = 0; i<n; i++){
		tat[i] = ct[i] - at[i];
		wt[i] = tat[i] - bt[i];
		awt+=wt[i];
		atat+=tat[i];
	}
	printf("\nProcess\tAT\tBT\tCT\tWT\tTAT\n");

        for(int i=0;i<n;i++){
 	       printf("P%d\t%d\t%d\t%d\t%d\t%d\n",i+1,at[i],bt[i],ct[i],wt[i],tat[i]);
        }

       printf("\nAverage Waiting Time = %.2f",awt/n);
       printf("\nAverage Turnaround Time = %.2f\n",atat/n);
}

void priority_np(){
	int ct[1000], tat[1000], wt[1000], rt[1000];
	int completed = 0, time = 0, smallest;
	float awt = 0, atat = 0;
	for(int i = 0; i<n; i++){
		rt[i] = bt[i];
	}
	while(completed<n){
		smallest = -1;
		for(int i = 0; i<n; i++){
			if(at[i]<=time && rt[i]>0){
				if(smallest == -1 || pr[i]<pr[smallest]){
					smallest = i;
				}
			}
		}
		if(smallest == -1){
			time++;
			continue;
		}
		completed++;
		time+=rt[smallest];
		rt[smallest] = 0;
		ct[smallest] = time;
	}
	for(int i = 0; i<n; i++){
		tat[i] = ct[i] - at[i];
		wt[i] = tat[i] - bt[i];
		awt+=wt[i];
		atat+=tat[i];
	}
	printf("\nProcess\tAT\tBT\tCT\tWT\tTAT\n");

        for(int i=0;i<n;i++){
 	        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",i+1,at[i],bt[i],ct[i],wt[i],tat[i]);
        }

        printf("\nAverage Waiting Time = %.2f",awt/n);
        printf("\nAverage Turnaround Time = %.2f\n",atat/n);
}

void rr(){
	int ct[1000], tat[1000], wt[1000], rt[1000];
	int time = 0, completed = 0, tq;
	float awt = 0, atat = 0;
	printf("Enter time quantum: ");
	scanf("%d", &tq);

	for(int i = 0; i<n; i++){
		rt[i] = bt[i];
	}
	while(completed<n){
		int done = 1;
		for(int i = 0; i<n; i++){
			if(at[i]<=time && rt[i]>0){
				done = 0;
				if(rt[i]>tq){
					time+=tq;
					rt[i]-=tq;
				}
				else{
					time+=rt[i];
					ct[i] = time;
					rt[i] = 0;
					completed++;
				}
			}
		}
		if(done){
			time++;
		}
	}

	for(int i = 0; i<n; i++){
		tat[i] = ct[i] - at[i];
		wt[i] = tat[i] - bt[i];
		awt+=wt[i];
		atat+=tat[i];
	}

	printf("\nProcess\tAT\tBT\tCT\tWT\tTAT\n");
	for(int i = 0; i < n; i++){
        	printf("P%d\t%d\t%d\t%d\t%d\t%d\n",i+1,at[i],bt[i],ct[i],wt[i],tat[i]);
	}	
    	printf("\nAverage Waiting Time = %.2f",awt/n);
	printf("\nAverage Turnaround Time = %.2f\n",atat/n);
}
int main(){
	printf("Enter the number processes: ");
	scanf("%d", &n);
	for(int i = 0; i<n; i++){
		printf("Enter arrival time for process %d: ",i+1);
		scanf("%d",&at[i]);
		printf("Enter burst time for process %d: ",i+1);
		scanf("%d",&bt[i]);
		printf("Enter priority for process %d: ",i+1);
		scanf("%d",&pr[i]);
	}
	fcfs();
	srtf();
	sjf();
	priority_p();
	priority_np();
	rr();
}
