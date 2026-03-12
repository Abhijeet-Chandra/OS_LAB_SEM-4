#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>
#define MAX 1000
#define max(a, b) ((a) > (b) ? (a) : (b))
int main(){
	int at[1000],bt[1000],wt[1000], tat[1000], ct[1000],n;
	float awt = 0, atat = 0;
	printf("Enter the number processes: ");
	scanf("%d", &n);
	for(int i = 0; i<n; i++){
		printf("Enter arrival time for process %d: ",i+1);
		scanf("%d",&at[i]);
		printf("Enter burst time for process %d: ",i+1);
		scanf("%d",&bt[i]);
	}
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
