#include<stdio.h>
#include<stdlib.h>

void sort(int arr[], int n){
    for(int i = 0; i<n-1; i++){
        for(int j = 0; j<n-i-1; j++){
            if(arr[j]>arr[j+1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main(){
    int n;
    printf("\nEnter the number of requests:\n");
    scanf("%d",&n);
    int*req = (int*)malloc(n*sizeof(int));
    printf("\nEnter requests:\n");
    for(int i = 0; i<n; i++) scanf("%d", &req[i]);

    int head;
    printf("\nEnter initial head position:\n");
    scanf("%d",&head);

    int dir;
    printf("\nEnter 1 for right and 0 for left:\n");
    scanf("%d",&dir);

    int total = 0;

    sort(req,n);

    printf("\nHead Movement:\n");
    printf("Head(%d) ", head);

    int current = head;
    int index = 0;

    for(int i = 0; i<n; i++){
        if(req[i]>head){
            index = i;
            break;
        }
    }

    if(dir == 1){
        //move right
        for(int i = index; i<n; i++){
            printf("-> %d ", req[i]);
            total+=abs(current-req[i]);
            current = req[i];
        }

        current = req[0]; //go to first request
        
        for(int i = 0; i<=index-1; i++){
            printf("-> %d ", req[i]);
            total+=abs(current-req[i]);
            current = req[i];
        }
    }
    else if(dir == 0){
        //move left
        for(int i = index - 1; i>=0; i--){
            printf("-> %d ", req[i]);
            total+=abs(current-req[i]);
            current = req[i];
        }
        current = req[n-1];

        for(int i = n-1; i>=index; i--){
            printf("-> %d ", req[i]);
            total+=abs(current-req[i]);
            current = req[i];
        }
    }

    printf("\nTotal Head Movements: %d\n",total);
}
