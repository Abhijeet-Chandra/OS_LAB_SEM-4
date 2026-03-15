#include<stdio.h>

int main()
{
    int n, tq;
    int at[50], bt[50], rt[50];
    int ct[50], wt[50], tat[50];

    printf("Enter number of processes: ");
    scanf("%d",&n);

    for(int i=0;i<n;i++)
    {
        printf("Enter arrival time for process %d: ",i+1);
        scanf("%d",&at[i]);

        printf("Enter burst time for process %d: ",i+1);
        scanf("%d",&bt[i]);

        rt[i] = bt[i];
    }

    printf("Enter time quantum: ");
    scanf("%d",&tq);

    int completed = 0;
    int queue[1000], visited[1000] = {0}, front = 0, rear = 0, time = 0;

    queue[rear++] = 0;
    visited[0] = 1;
    time = at[0];

    while(completed<n){
        int i = queue[front++];

        if(rt[i]>tq){
            time+=tq;
            rt[i]-=tq;
        }
        else{
            time+=rt[i];
            rt[i] = 0;
            ct[i] = time;
            completed++;
        }

        for(int j = 0; j<n; j++){
            if(at[j]<=time && visited[j] == 0){
                queue[rear++] = j;
                visited[j] = 1;
            }
        }
        if(rt[i]>0)
            queue[rear++] = i;

        if(front == rear){
            for (int j = 0; j < n; j++)
            {
                if(visited[j]==0){
                    queue[rear++] = j;
                    visited[j] = 1;
                    time = at[j];
                    break;
                }
            }
            
        }
    }

    for(int i = 0; i<n; i++){
        tat[i] = ct[i]- at[i];
        wt[i] = tat[i] - bt[i];
    }

    float avgwt=0, avgtat=0;

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");

    for(int i=0;i<n;i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
        i+1,at[i],bt[i],ct[i],tat[i],wt[i]);

        avgwt += wt[i];
        avgtat += tat[i];
    }

    printf("\nAverage Waiting Time = %.2f",avgwt/n);
    printf("\nAverage Turnaround Time = %.2f\n",avgtat/n);

    return 0;
}
