#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

volatile int counter = 0;
pthread_mutex_t mutex;

void*count(void* arg){
    for(int i = 0; i<100; i++){
        pthread_mutex_lock(&mutex);
        counter++;
        printf("%d\n",counter);
        pthread_mutex_unlock(&mutex);
    }
}

int main(){
    pthread_t thread1, thread2;
    pthread_mutex_init( &mutex,NULL);
    pthread_create(&thread1,NULL,count,NULL);
    pthread_create(&thread2,NULL,count,NULL);
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    pthread_mutex_destroy(&mutex);
    return 0;
}
