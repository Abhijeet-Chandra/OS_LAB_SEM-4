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

    int* req = (int*)malloc(n*sizeof(int));

    printf("\nEnter requests:\n");
    for(int i = 0; i<n; i++){
        scanf("%d",&req[i]);
    }

    int head;
    printf("\nEnter head:\n");
    scanf("%d",&head);

    int dick_size;
    printf("\nEnter dick_size:\n");
    scanf("%d",&dick_size);

    int dir;
    printf("\nEnter 1 for right and 0 for left:\n");
    scanf("%d",&dir);

    int current = head;
    int total = 0;
    printf("\nHead Movement:\n");
    printf("Head(%d) ",head);

    sort(req,n);

    int index = 0;
    for(int i = 0; i<n; i++){
        if(req[i]>head){
            index = i;
            break;
        }
    }

    if(dir == 1){
        //move right:
        for(int i = index; i<n; i++){
            printf("-> %d ", req[i]);
            total+=abs(current-req[i]);
            current = req[i];
        }
        
        //it pointer is not at the end, move it to the end
        if(current != dick_size - 1){
            total+=abs(current-(dick_size-1));
            current = dick_size - 1;
        }

        printf("-> %d -> 0",dick_size -1 );
        current = 0; //move it to beginning (aisa hona nhi chahiye, but ab lab manual me yahi diya hai bro)

        for(int i = 0; i<=index-1; i++){
            printf(" -> %d ", req[i]);
            total+=abs(current-req[i]);
            current = req[i];
        }

    }
    else if(dir == 0){
        //move left:
        for(int i = index-1; i>=0; i--){
            printf("-> %d ", req[i]);
            total+=abs(current-req[i]);
            current = req[i];
        }
        
        //it pointer is not at the end, move it to the end
        if(current != 0){
            total+=abs(current-(0));
            current = 0;
        }

        printf("-> 0 -> %d",dick_size -1 );
        current = dick_size-1; //move it to end (aisa hona nhi chahiye, but ab lab manual me yahi diya hai bro)

        for(int i = n-1; i>=index; i--){
            printf(" -> %d ", req[i]);
            total+=abs(current-req[i]);
            current = req[i];
        }
    }

    printf("\nTotal head movement: %d\n",total);
    free(req);
    return 0;
}