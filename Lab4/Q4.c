#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<time.h>
#include<pthread.h>
// #include<sys/wait.h>
int arr1[100], arr2[100], arr3[100], n;

void* bubble_sort(void*arg){
    clock_t start = clock();
    for(int i = 0; i<n-1; i++){
        for(int j = 0; j<n-i-1; j++){
            if(arr1[j]>arr1[j+1]){
                int temp = arr1[j];
                arr1[j] = arr1[j+1];
                arr1[j+1] = temp;
            }
        }
    }
    clock_t end = clock();
    double time_taken = (double)(end-start)/CLOCKS_PER_SEC;
    printf("Time taken by bubble sort: %f secs\n", time_taken);
    pthread_exit(NULL);
}

void* selection_sort(void*arg){
    clock_t start = clock();
    int min;
    for(int i = 0; i<n-1; i++){
        int min = i;
        for(int j = i+1; j<n; j++){
            if(arr2[j]<arr2[min]){
                min = j;
            }
        }
        int temp = arr2[i];
        arr2[i] = arr2[min];
        arr2[min] = temp;
    }
    clock_t end = clock();
    double time_taken = (double)(end-start)/CLOCKS_PER_SEC;
    printf("Time taken by selection sort: %f secs\n", time_taken);
    pthread_exit(NULL);
}

void* insertion_sort(void* arg){
    clock_t start = clock();
    for(int i = 1; i<n; i++){
        int temp = arr3[i];
        int j = i-1;
        while(j>=0 && arr3[j]>temp){
            arr3[j+1] = arr3[j];
            j--;
        }
        arr3[j+1] = temp;
    }
    clock_t end = clock();
    double time_taken = (double)(end-start)/CLOCKS_PER_SEC;
    printf("Time taken by insertion sort: %f secs\n", time_taken);
    pthread_exit(NULL);
}

int main(){
    pthread_t t1,t2,t3;
    printf("Enter the number of elements: ");
    scanf("%d",&n);
    for(int i = 0; i<n; i++){
        printf("Enter element %d: ",i+1);
        scanf("%d",&arr1[i]);
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
    }

    pthread_create(&t1,NULL,bubble_sort,NULL);
    pthread_create(&t2,NULL,selection_sort,NULL);
    pthread_create(&t3,NULL,insertion_sort,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);

    printf("\nFinal Sorted Array (Bubble Sort Result):\n");
    for(int i=0;i<n;i++){
        printf("%d ",arr1[i]);
    }

    printf("\n");
}
