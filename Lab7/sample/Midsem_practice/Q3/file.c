#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<unistd.h>
#include<sys/wait.h>
typedef struct process{
    int id; //process id
    int at; //arrival time
    int bt; //burst time
    int pr; //priority
}process;

typedef struct shared{
    process p[100];
    int n; //number of processes
}shared;

void sort(process p[], shared* sh){
    for(int i = 0; i<sh->n-1 ; i++){
        for(int j = 0; j<sh->n-i-1; j++){
            if(p[j].at>p[j+1].at){
                process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}

int main(){
    //allocation memory using shmget
    int shmid = shmget(1999, sizeof(shared), IPC_CREAT | 0666); //in place of 1999 you can write any other number too, and 0666 means that file has both read and write permission
    
    //attaching current process' memory segment to shared memory space:
    shared * sh = (shared*) shmat(shmid, NULL, 0);

    //Note : since 'sh' is pointer to structure we have to access its members using -> sign

    sort(sh->p,sh);

    //applying preemptive priority algo:

    int completed = 0, time = 0; //completed represents number of processes that are completed, time represents current time
    int ct[1000], tat[1000], wt[1000], rt[1000];
    int highest; //process with highest priority

    //initialize rt
    for(int i = 0; i<sh->n; i++){
        rt[i] = sh->p[i].bt;
    }

    while(completed<sh->n){
        highest = -1;
        for(int i = 0; i<sh->n; i++){
            if(sh->p[i].at <= time && rt[i] > 0){
                if(highest == -1 || sh->p[i].pr < sh->p[highest].pr){
                    highest = i;
                }
            }
        }

        if(highest == -1){ //no processes selected
            time++;
            continue;
        }
        rt[highest]--;
        time++;

        if(rt[highest]==0){
            ct[highest] = time;
            completed++;
        }
    }

    float awt = 0, atat= 0;
    //calculation of turnaround time and waiting time:
    for(int i = 0; i<sh->n; i++){
        tat[i] = ct[i] - sh->p[i].at;
        wt[i] = tat[i] - sh->p[i].bt;
        awt+=wt[i];
        atat+=tat[i];
    }

    printf("Final table:\n");

    printf("PID\tAT\tBT\tPR\tCT\tWT\n");
    for(int i = 0; i<sh->n; i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",sh->p[i].id,sh->p[i].at,sh->p[i].bt,sh->p[i].pr,ct[i],wt[i]);
    }

    printf("Average waiting time: %f\n",awt/sh->n);
    printf("Average turnaround time: %f\n",atat/sh->n);
    shmdt(sh);
    shmctl(shmid, IPC_RMID, NULL);
}
