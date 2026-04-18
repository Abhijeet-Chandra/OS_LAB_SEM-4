#include<stdio.h>
#include<stdlib.h>

#define MAX 10

int alloc[MAX][MAX], max[MAX][MAX], avail[MAX], need[MAX][MAX];
int n,m;

void calculateNeed(){
    for(int i = 0; i<n; i++){
        for(int j = 0; j<m; j++){
            need[i][j] = max[i][j] - alloc[i][j]; 
        }
    }
}

int isSafe(int safeSeq[]){
    int count = 0;
    int finish[MAX] = {0};
    int work[MAX];
    for(int i = 0; i<m; i++) work[i] = avail[i];
    while(count < n){
        int found = 0;
        for(int i = 0; i<n; i++){
            if(finish[i] == 0){
                int j;
                for(j = 0; j<m; j++){
                    if(need[i][j] > work[j]){
                        break;
                    }
                }
                if(j == m){
                    for(int k = 0; k<m; k++){
                        work[k] += alloc[i][k];
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

void requestResource(){
    int process;
    printf("Enter process number: ");
    scanf("%d",&process);
    printf("Enter resource vector: ");
    int request[MAX];
    for(int i = 0; i<m; i++) scanf("%d", &request[i]);

    //request <= need
    for(int i = 0; i<m; i++){
        if(request[i] > need[process][i]){
            printf("Request exceeds need!!");
            return;
        }
    }

    //request <= available
    for(int i = 0; i<m; i++){
        if(request[i] > avail[i]){
            printf("Resource exceeds avail!!");
            return;
        }
    }

    //temporary allocation:
    for(int i = 0; i<m; i++){
        need[process][i] -= request[i];
        avail[i] -= request[i];
        alloc[process][i] += request[i];
    }

    //checking if its safe:
    int safeSeq[MAX];
    if(isSafe(safeSeq)){
        printf("\nResource granted, safe sequence: ");
        for(int i = 0; i<n; i++) printf("P%d->", safeSeq[i]);
        printf("end\n");
    }
    else{
        printf("Resource not granted, rolling back...");
        for(int i = 0; i<m; i++){
            need[process][i] += request[i];
            avail[i] += request[i];
            alloc[process][i] -= request[i];
        }
    }
}

void printMat(int mat[][MAX]){
    for(int i = 0; i<n; i++){
        for(int j = 0; j<m; j++){
            printf("%d\t", mat[i][j]);
        }
        printf("\n");
    }
}

int main(){
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);

    printf("\nEnter allocation matrix:\n");
    for(int i = 0; i<n; i++){
        for(int j = 0; j<m; j++){
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("\nEnter Max matrix:\n");
    for(int i = 0; i<n; i++){
        for(int j = 0; j<m; j++){
            scanf("%d", &max[i][j]);
        }
    }

    printf("\nEnter available resources: ");
    for(int i = 0; i<m; i++)scanf("%d", &avail[i]);

    //calculating need:
    calculateNeed();

    printf("\nNeed matrix:\n");
    //printing need:

    printMat(need);

    //bankers:
    int safeSeq[MAX];
    if(isSafe(safeSeq)){
        printf("\nSystem is safe, safe sequence: ");
        for(int i = 0; i<n; i++) printf("P%d->",safeSeq[i]);
        printf("end\n");
    }
    else{
        printf("\nSystem is not safe!!\n");
        return 0;
    }


    char ch;
    do
    {
        requestResource();
        printf("Do you want to add another request? (y/n): ");
        scanf(" %c", &ch);
    } while (ch == 'y' || ch == 'Y');
    
}