#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<sys/shm.h>
#include<pthread.h>
#include<sys/wait.h>
#include<unistd.h>

sem_t lock;

typedef struct student{
    int id;
    int pages;
}student;

typedef struct shared{
    int n;
    student s[100];
}shared;

void* fun(void* arg){
    student* s = (student*)arg;

    printf("Student %d waiting for printer\n",s->id);
    sem_wait(&lock);
    printf("Student %d is requesting printer...\n",s->id);
    sleep(2);
    printf("Student %d is allocated printer.\n",s->id);
    printf("Student %d is printing %d pages..\n",s->id, s->pages);
    sleep(s->pages%5);
    printf("Student %d finished printing.\n",s->id);
    sem_post(&lock);
    return NULL;
}



int main(){
    int shmid = shmget(1234, sizeof(shared), IPC_CREAT | 0666);
    shared* sh = (shared*)shmat(shmid,NULL,0);  

    sem_init(&lock,0,3);
    pthread_t thread[sh->n];

    for(int i = 0; i<sh->n; i++){
        pthread_create(&thread[i],NULL,fun,&(sh->s[i]));
    }

    for(int i = 0; i<sh->n; i++)
        pthread_join(thread[i],NULL);

    sem_destroy(&lock);
    return 0;
}
