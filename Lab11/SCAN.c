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
    int n;//number of requests

    printf("Enter the number of requests: ");
    scanf("%d", &n);

    int* req = (int*)malloc(n*sizeof(int));


    printf("\nEnter requests: ");
    for(int i = 0; i<n; i++){
        scanf("%d", &req[i]);
    }

    int head;
    printf("\nEnter head:\n");
    scanf("%d",&head);

    int dick_size;
    printf("\nEnter dick size:\n");
    scanf("%d", &dick_size);

    int dir;
    printf("\nEnter 1 for right and 0 for left\n");
    scanf("%d",&dir);

    sort(req,n);

    //find split index:
    int index = 0;
    for(int i = 0; i<n; i++){
        if(req[i]>head){
            index = i;
            break;
        }
    }

    int total = 0;
    int current = head;
    printf("\nHead Movement:\n");
    printf("Head(%d) ", head);
    if(dir == 1){
        //move right
        for(int i = index; i<n; i++){
            printf("-> %d ", req[i]);
            total += abs(current-req[i]);
            current = req[i];
        }

        //if head is not at rightmost end, then go to end
        if(current != dick_size - 1){
            printf("-> %d ", dick_size-1);
            total+=abs(current-(dick_size-1));
            current = dick_size - 1;
        }

        //move left
        for(int i = index - 1; i>=0; i--){
            printf("-> %d ", req[i]);
            total+=abs(current-req[i]);
            current = req[i];
        }
    }
    else if (dir == 0){
        //move left
        for(int i = index - 1; i>=0; i--){
            printf("-> %d ", req[i]);
            total+=abs(current-req[i]);
            current = req[i];
        }

        //if head is not at 0, bring it at 0
        if(current != 0){
            printf("-> %d ", 0);
            total+=current;
            current = 0;
        }

        //move right
        for(int i = index; i<n; i++){
            printf("-> %d ", req[i]);
            total+=abs(current-req[i]);
            current = req[i];
        }
    }

    printf("\nTotal head movement: %d\n",total);
    free(req);
    return 0;
}