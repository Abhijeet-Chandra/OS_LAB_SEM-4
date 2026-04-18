#include<stdio.h>
#include<stdlib.h>

int main(){
    int n; //number of requests
    int head; //initial head position

    printf("Enter the number of requests: ");
    scanf("%d", &n);

    int * req = (int*) malloc(n*sizeof(int));
    printf("\nEnter requests: ");
    for(int i = 0; i<n; i++){
        scanf("%d", &req[i]);
    }

    printf("\nEnter initial head position: ");
    scanf("%d", &head);

    printf("\nMovement sequence:\n");
    printf("Head(%d) ", head);
    for(int i = 0; i<n; i++){
        printf("-> %d ", req[i]);
    }

    int total = 0;

    for(int i = 0; i<n; i++){
        total+=abs(head - req[i]);
        head = req[i];
    }

    printf("\nTotal head movements: %d", total);
    free(req);
}