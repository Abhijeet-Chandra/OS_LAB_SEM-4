#include<stdio.h>
#include<stdlib.h>

#define max(a,b) ((a)>(b)?(a):(b))

typedef struct process{
    int at;
    int bt;
    int pr;
}process;

int n;

void sort(process p[]){
    for(int i = 0; i<n-1; i++){
        for(int j = 0; j<n-i-1; j++){
            if(p[j].at>p[j+1].at){
                process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}

void fcfs(process p[]){
    int ct[1000],tat[1000],wt[1000];
    float awt = 0, atat = 0;

    ct[0] = p[0].at + p[0].bt;
    tat[0] = ct[0] - p[0].at;
    wt[0] = tat[0] - p[0].bt;

    for(int i=1;i<n;i++)
        ct[i] = max(ct[i-1],p[i].at) + p[i].bt;

    for(int i=1;i<n;i++){
        tat[i] = ct[i] - p[i].at;
        wt[i] = tat[i] - p[i].bt;
    }

    printf("\nFCFS\n");
    printf("P\tAT\tBT\tCT\tTAT\tWT\n");

    for(int i=0;i<n;i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
        i+1,p[i].at,p[i].bt,ct[i],tat[i],wt[i]);
        awt+=wt[i];
        atat+=tat[i];
    }

    printf("Average WT = %.2f\n",awt/n);
    printf("Average TAT = %.2f\n",atat/n);
}

void srtf(process p[]){
    int ct[1000], tat[1000], wt[1000], rt[1000];
    int smallest, time=0, completed=0;
    float awt=0, atat=0;

    for(int i=0;i<n;i++)
        rt[i] = p[i].bt;

    while(completed<n){
        smallest = -1;

        for(int i=0;i<n;i++){
            if(p[i].at<=time && rt[i]>0){
                if(smallest==-1 || rt[i]<rt[smallest] ||
                (rt[i]==rt[smallest] && p[i].at<p[smallest].at))
                    smallest=i;
            }
        }

        if(smallest==-1){
            time++;
            continue;
        }

        rt[smallest]--;
        time++;

        if(rt[smallest]==0){
            completed++;
            ct[smallest]=time;
        }
    }

    for(int i=0;i<n;i++){
        tat[i]=ct[i]-p[i].at;
        wt[i]=tat[i]-p[i].bt;
        awt+=wt[i];
        atat+=tat[i];
    }

    printf("\nSRTF\n");
    printf("P\tAT\tBT\tCT\tTAT\tWT\n");

    for(int i=0;i<n;i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
        i+1,p[i].at,p[i].bt,ct[i],tat[i],wt[i]);

    printf("Average WT = %.2f\n",awt/n);
    printf("Average TAT = %.2f\n",atat/n);
}

void sjf(process p[]){
    int ct[1000], tat[1000], wt[1000], rt[1000];
    int completed=0, time=0, smallest;
    float awt=0, atat=0;

    for(int i=0;i<n;i++)
        rt[i]=p[i].bt;

    while(completed<n){
        smallest=-1;

        for(int i=0;i<n;i++){
            if(p[i].at<=time && rt[i]>0){
                if(smallest==-1 || rt[i]<rt[smallest] ||
                (rt[i]==rt[smallest] && p[i].at<p[smallest].at))
                    smallest=i;
            }
        }

        if(smallest==-1){
            time++;
            continue;
        }

        time += rt[smallest];
        ct[smallest] = time;
        rt[smallest] = 0;
        completed++;
    }

    for(int i=0;i<n;i++){
        tat[i]=ct[i]-p[i].at;
        wt[i]=tat[i]-p[i].bt;
        awt+=wt[i];
        atat+=tat[i];
    }

    printf("\nSJF\n");
    printf("P\tAT\tBT\tCT\tTAT\tWT\n");

    for(int i=0;i<n;i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
        i+1,p[i].at,p[i].bt,ct[i],tat[i],wt[i]);

    printf("Average WT = %.2f\n",awt/n);
    printf("Average TAT = %.2f\n",atat/n);
}

void priority_p(process p[]){
    int ct[1000], tat[1000], wt[1000], rt[1000];
    int smallest, time=0, completed=0;
    float awt=0, atat=0;

    for(int i=0;i<n;i++)
        rt[i]=p[i].bt;

    while(completed<n){
        smallest=-1;

        for(int i=0;i<n;i++){
            if(p[i].at<=time && rt[i]>0){
                if(smallest==-1 || p[i].pr>p[smallest].pr ||
                (p[i].pr==p[smallest].pr && p[i].at<p[smallest].at))
                    smallest=i;
            }
        }

        if(smallest==-1){
            time++;
            continue;
        }

        rt[smallest]--;
        time++;

        if(rt[smallest]==0){
            completed++;
            ct[smallest]=time;
        }
    }

    for(int i=0;i<n;i++){
        tat[i]=ct[i]-p[i].at;
        wt[i]=tat[i]-p[i].bt;
        awt+=wt[i];
        atat+=tat[i];
    }

    printf("\nPriority Preemptive\n");
    printf("P\tAT\tBT\tPR\tCT\tTAT\tWT\n");

    for(int i=0;i<n;i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        i+1,p[i].at,p[i].bt,p[i].pr,ct[i],tat[i],wt[i]);

    printf("Average WT = %.2f\n",awt/n);
    printf("Average TAT = %.2f\n",atat/n);
}

void priority_np(process p[]){
    int ct[1000], tat[1000], wt[1000], rt[1000];
    int completed=0, time=0, smallest;
    float awt=0, atat=0;

    for(int i=0;i<n;i++)
        rt[i]=p[i].bt;

    while(completed<n){
        smallest=-1;

        for(int i=0;i<n;i++){
            if(p[i].at<=time && rt[i]>0){
                if(smallest==-1 || p[i].pr>p[smallest].pr ||
                (p[i].pr==p[smallest].pr && p[i].at<p[smallest].at))
                    smallest=i;
            }
        }

        if(smallest==-1){
            time++;
            continue;
        }

        time += rt[smallest];
        ct[smallest]=time;
        rt[smallest]=0;
        completed++;
    }

    for(int i=0;i<n;i++){
        tat[i]=ct[i]-p[i].at;
        wt[i]=tat[i]-p[i].bt;
        awt+=wt[i];
        atat+=tat[i];
    }

    printf("\nPriority Non-Preemptive\n");
    printf("P\tAT\tBT\tPR\tCT\tTAT\tWT\n");

    for(int i=0;i<n;i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        i+1,p[i].at,p[i].bt,p[i].pr,ct[i],tat[i],wt[i]);

    printf("Average WT = %.2f\n",awt/n);
    printf("Average TAT = %.2f\n",atat/n);
}

void rr(process p[]){
    int ct[1000], tat[1000], wt[1000], rt[1000];
    int time = 0, completed = 0, tq;
    float awt = 0, atat = 0;
    printf("Enter time quantum: ");
    scanf("%d",&tq);

    for(int i = 0; i<n; i++){
        rt[i] = p[i].bt;
    }

    while(completed<n){
        int done = 1;
        for(int i = 0; i<n; i++){
            if(p[i].at<=time && rt[i]>0){
                done = 0;
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
            }
        }

        if(done){
            time++;
        }
    }
    for(int i=0;i<n;i++){
        tat[i]=ct[i]-p[i].at;
        wt[i]=tat[i]-p[i].bt;
        awt+=wt[i];
        atat+=tat[i];
    }
    printf("\nRound Robin\n");
    printf("P\tAT\tBT\tPR\tCT\tTAT\tWT\n");

    for(int i=0;i<n;i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        i+1,p[i].at,p[i].bt,p[i].pr,ct[i],tat[i],wt[i]);

    printf("Average WT = %.2f\n",awt/n);
    printf("Average TAT = %.2f\n",atat/n);
}

int main(){
    printf("Enter number of processes: ");
    scanf("%d",&n);

    process *p = malloc(n*sizeof(process));

    for(int i=0;i<n;i++){
        printf("Arrival time P%d: ",i+1);
        scanf("%d",&p[i].at);

        printf("Burst time P%d: ",i+1);
        scanf("%d",&p[i].bt);

        printf("Priority P%d: ",i+1);
        scanf("%d",&p[i].pr);
    }

    sort(p);

    fcfs(p);
    srtf(p);
    sjf(p);
    priority_p(p);
    priority_np(p);
    rr(p);

    free(p);
}
