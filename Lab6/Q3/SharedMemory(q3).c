#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<unistd.h>

typedef struct shared{
    int flag;
    char a;
}shared;

int main(){
    pid_t pid;
    int shmid = shmget(1999, sizeof(shared), IPC_CREAT | 0666);
    shared* sh = (shared*)shmat(shmid, NULL, 0);

    sh->flag = 0;

    pid = fork();

    if(pid<0){
        printf("Khatam tata bye bye good bye!");
    }
    else if(pid == 0){
        while(sh->flag == 0);
        printf("Child received %c\n",sh->a);
        sh->a = (char)(sh->a+1);
        sh->flag = 0;
    }
    else{
        printf("Enter a character: ");
        scanf(" %c",&(sh->a));
        sh->flag = 1;
        while(sh->flag == 1);
        printf("Next character: %c\n",sh->a);
    }

    shmdt(sh);
    shmctl(shmid, IPC_RMID, NULL);
}
