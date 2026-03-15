#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#define SIZE 10

sem_t slots_empty;
sem_t slots_taken;
sem_t mutex;
int buf[10];
int f = -1, r = -1;

void *produce(void *arg)
{

    for (int i = 0; i < 10; i++)
    {
        sem_wait(&slots_empty);
        sem_wait(&mutex);
        // produce here:
        r = (r + 1) % SIZE;
        buf[r] = i;
        printf("Produced: %d\n",i);
        sem_post(&mutex);
        sem_post(&slots_taken);
    }
    return NULL;
}

void* consume(void *arg){
    for(int i = 0; i<10; i++){
        sem_wait(&slots_taken);
        sem_wait(&mutex);
        //consume:
        f = (f+1)%SIZE;
        int item = buf[f];
        printf("Consumed: %d\n",item);
        sem_post(&mutex);
        sem_post(&slots_empty);
    }
    return NULL;
}

int main(){
    pthread_t t1, t2;
    sem_init(&slots_empty,0,SIZE);
    sem_init(&slots_taken,0,0);
    sem_init(&mutex,0,1);
    pthread_create(&t1,NULL,produce,NULL);
    pthread_create(&t2,NULL,consume,NULL);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    sem_destroy(&mutex);
    sem_destroy(&slots_empty);
    sem_destroy(&slots_taken);
    return 0;
}
