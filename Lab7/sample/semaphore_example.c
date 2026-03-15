#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>

sem_t semaphore;

void*fun1(void* arg){
    sem_wait(&semaphore);
    printf("Thread 1\n");
}

void*fun2(void*arg){
    printf("Thread 2\n");
    sem_post(&semaphore);
}

int main(){
    pthread_t t1,t2;
    sem_init(&semaphore,0,0);
    pthread_create(&t1,NULL,fun1,NULL);
    pthread_create(&t2,NULL,fun2,NULL);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    sem_destroy(&semaphore);
}
