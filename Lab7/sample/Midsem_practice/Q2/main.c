#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
typedef struct process{
    int pid;
    int at;
    int bt;
    int pr;
}process;
int n;

void* sort(void* arg){
    process* p = (process*)arg;
    for(int i = 0; i<n-1; i++){
        for(int j = 0; j<n-i-1; j++){
            if(p[j].at>p[j+1].at){
                process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
            else if((p[j].at == p[j+1].at)&&(p[j].pr<p[j+1].pr)){
                process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
    return NULL;
}

void* rr(void* arg){
    process* p = (process*)arg;

    int ct[1000], tat[1000], wt[1000], rt[1000];
    int queue[1000], visited[1000] = {0};

    int front = 0, rear = 0;
    int time = 0, completed = 0, tq;

    float awt = 0, atat = 0;

    printf("Enter time quantum: ");
    scanf("%d",&tq);

    for(int i=0;i<n;i++)
        rt[i] = p[i].bt;

    queue[rear++] = 0;
    visited[0] = 1;
    time = p[0].at;

    while(completed < n){

        int i = queue[front++];

        if(rt[i] > tq){
            time += tq;
            rt[i] -= tq;
        }
        else{
            time += rt[i];
            rt[i] = 0;
            ct[i] = time;
            completed++;
        }

        for(int j=0;j<n;j++){
            if(p[j].at <= time && visited[j]==0){
                queue[rear++] = j;
                visited[j] = 1;
            }
        }

        if(rt[i] > 0)
            queue[rear++] = i;

        if(front == rear){
            for(int j=0;j<n;j++){
                if(visited[j]==0){
                    queue[rear++] = j;
                    visited[j] = 1;
                    time = p[j].at;
                    break;
                }
            }
        }
    }

    for(int i=0;i<n;i++){
        tat[i] = ct[i] - p[i].at;
        wt[i] = tat[i] - p[i].bt;

        awt += wt[i];
        atat += tat[i];
    }

    printf("\nRound Robin\n");
    printf("P\tAT\tBT\tPR\tCT\tTAT\tWT\n");

    for(int i=0;i<n;i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        p[i].pid,p[i].at,p[i].bt,p[i].pr,ct[i],tat[i],wt[i]);
    }

    printf("Average WT = %.2f\n",awt/n);
    printf("Average TAT = %.2f\n",atat/n);

    return NULL;
}

int main(){
    pthread_t t1, t2;
    printf("Enter the number of processes: ");
    scanf("%d",&n);
    process* p = (process*)malloc(n*sizeof(process));
    for(int i = 0; i<n; i++){
        printf("Enter process ID: ");
        scanf("%d",&(p[i].pid));
        printf("Enter arrival time: ");
        scanf("%d",&(p[i].at));
        printf("Enter burst time: ");
        scanf("%d",&(p[i].bt));
        printf("Enter priority: ");
        scanf("%d",&(p[i].pr));
    }
    pthread_create(&t1,NULL,sort,p);
    pthread_join(t1,NULL);
    pthread_create(&t2,NULL,rr,p);
    pthread_join(t2,NULL);
}
