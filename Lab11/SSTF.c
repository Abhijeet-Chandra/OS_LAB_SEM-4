#include<stdio.h>
#include<stdlib.h>

int main(){
    int n; //no of requests;
    printf("Enter the number of requests: ");
    scanf("%d", &n);

    int* req = (int*) malloc(n*sizeof(int));
    int* vis = (int*) calloc(n,sizeof(int));


    printf("\nEnter requests:\n");
    for(int i = 0; i<n; i++) scanf("%d",&req[i]);

    int head;
    printf("Enter initial head position: ");
    scanf("%d", &head);

    int total = 0;
    printf("\nHead movement:\n");
    printf("Head(%d) ", head);

    for(int i = 0; i<n; i++){
        int min = 1000000;
        int index = -1;
        for(int j = 0; j<n; j++){
            if(!vis[j]){
                int dist = abs(head - req[j]);
                if(dist<min){
                    min = dist;
                    index = j;
                }
            }
        }
        printf("-> %d ", req[index]);
        total+=min;
        head = req[index];
        vis[index] = 1;
    }

    printf("\nTotal head movement is: %d\n",total);
    free(req);
    free(vis);
    return 0;
}