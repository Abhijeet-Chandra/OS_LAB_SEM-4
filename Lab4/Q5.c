#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

int* arr;
void*fibo(void*arg){
    int *n = (int*)arg;
    arr = (int*)malloc((*n)*sizeof(int));
    arr[0] = 0;
    arr[1] = 1;
    for(int i = 2; i<(*n); i++){
        arr[i] = arr[i-1]+arr[i-2];
    }
    return NULL;
}

int main(){
    pthread_t t;
    int n;
    printf("Enter the number of elements: ");
    scanf("%d",&n);
    pthread_create(&t,NULL,fibo,&n);
    pthread_join(t,NULL);

    printf("Fibonacci sequence is: ");
    for(int i = 0; i<n; i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
    free(arr);
    return 0;
}
