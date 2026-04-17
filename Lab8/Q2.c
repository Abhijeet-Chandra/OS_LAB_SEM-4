#include<stdio.h>
#include<stdlib.h>

#define MAX 10

int isSafe(int n, int m, int alloc [][MAX], int request [][MAX] , int avail[], int safeSeq[]){
    int finish[MAX];
    int work[MAX];
    for(int i = 0; i<m; i++) work[i] = avail[i];
    for(int i = 0; i<n; i++) finish[i] = 0;

    int count = 0;
    while(count<n){
        int found = 0;
        for(int i = 0; i<n; i++){
            if(finish[i] == 0){
                int j;
                for(j = 0; j<m; j++){
                    if(request[i][j]> work[j]){
                        break;
                    }
                }
                if(j==m){
                    for(int k = 0; k<m; k++){
                        work[k]+=alloc[i][k];
                    }
                    found = 1;
                    finish[i] = 1;
                    safeSeq[count++] = i;
                }
            }
        }
        if(!found){
            return 0;
        }
    }
    return 1;
}

int main(){
    int n,m;
    printf("Enter the number of processes: ");
    scanf("%d",&n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);

    int alloc[MAX][MAX], request[MAX][MAX], avail[MAX];

    printf("\nEnter Allocated matrix:\n");
    for (int i = 0; i < n; i++){
        for(int j = 0; j<m; j++){
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("\nEnter request matrix:\n");
    for(int i = 0; i<n; i++){
        for(int j = 0; j<m; j++){
            scanf("%d",&request[i][j]);
        }
    }

    printf("\nEnter available matrix:\n");
    for(int i = 0; i<m; i++){
        scanf("%d",&avail[i]);
    }

    int safeSeq[MAX];
    if(isSafe(n,m,alloc,request,avail,safeSeq)){
        printf("\nNo deadlock detected, safe sequence: ");
        for(int i = 0; i<n; i++)
            printf("P%d ",safeSeq[i]);
    }
    else{
        printf("\nDeadlock detected.\n");
        return 0;
    }
    
    return 0;
}