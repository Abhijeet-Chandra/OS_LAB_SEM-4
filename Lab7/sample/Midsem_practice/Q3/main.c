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

int main(){
    //allocation memory using shmget
    int shmid = shmget(1999, sizeof(shared), IPC_CREAT | 0666); //in place of 1999 you can write any other number too, and 0666 means that file has both read and write permission

    if(shmid == -1){
        perror("shmget failed");
        exit(1);
    }

    //attaching current process' memory segment to shared memory space:
    shared * sh = (shared*) shmat(shmid, NULL, 0);
    if(sh == (void*)-1){
        perror("shmat failed");
        exit(1);
    }

    //Note : since 'sh' is pointer to structure we have to access its members using -> sign

    //input:
    printf("Enter the number of processes: ");
    scanf("%d",&sh->n);

    for(int i = 0; i<sh->n; i++){
        printf("Enter process id: ");
        scanf("%d",&sh->p[i].id);
        printf("Enter arrival time: ");
        scanf("%d",&sh->p[i].at);
        printf("Enter burst time: ");
        scanf("%d",&sh->p[i].bt);
        printf("Enter priority: ");
        scanf("%d",&sh->p[i].pr);
    }

    //display:
    printf("PID\tAT\tBT\tPR\n");
    for(int i = 0; i<sh->n; i++){
        printf("%d\t%d\t%d\t%d\n",sh->p[i].id,sh->p[i].at,sh->p[i].bt,sh->p[i].pr);
    }

    pid_t pid = fork();

    if(pid == 0){
        execl("./file","file",NULL);
    }
    else{
        wait(NULL);
    }

    shmdt(sh);
    return 0;
}
