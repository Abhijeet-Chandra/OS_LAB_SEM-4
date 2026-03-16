#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/shm.h>
#include<sys/wait.h>

typedef struct student{
    int id;
    int pages;
}student;

typedef struct shared
{
    int n;
    student s[100];
}shared;

int main(){
    int shmid = shmget(1234, sizeof(shared), IPC_CREAT | 0666);
    shared* sh = (shared*)shmat(shmid,NULL,0);
    printf("Enter the number of students: ");
    scanf("%d",&sh->n);

    

    for(int i = 0; i<sh->n; i++){
        printf("Enter student %d ID: ",i+1);
        scanf("%d",&(sh->s[i].id));
        printf("Enter the number of pages for student %d: ",i+1);
        scanf("%d",&(sh->s[i].pages));
    }

    printf("Student details:\n");
    printf("ID\tPages\n");
    for (int i = 0; i < sh->n; i++)
    {
        printf("%d\t%d\n",sh->s[i].id,sh->s[i].pages);
    }

    pid_t pid = fork();

    if(pid == 0){
        execl("./sync","sync",NULL);
        perror("Exec failed!!");
    }
    else{
        wait(NULL);
    }
    return 0;
}
