#include<stdio.h>
#include<stdlib.h>

#define MAX 10
int holes[MAX];
int processes[MAX];
int n,m;
void firstFit(){
    int h[MAX];
    for(int i = 0; i<n; i++)
        h[i] = holes[i];
    
    int ans[MAX];
    for(int i=0; i<m; i++) ans[i] = -1;
    for(int i = 0; i<m; i++){
        for (int j = 0; j < n; j++)
        {
            if(h[j]>=processes[i]){
                ans[i] = j;
                h[j] -= processes[i];
                break;
            }
        }
        
    }
    printf("\nFirst Fit:\n");
    for(int i = 0; i<m; i++){
        if(ans[i]!=-1){
            printf("P%d (%dK) -> block %d\n",i,processes[i],ans[i]);
        }
        else{
            printf("P%d (%dK) -> Not allocated\n",i,processes[i]);
        }
    }

    printf("\nRemaining memory block sizes after first fit allocation:\n");
    for(int i = 0; i<n; i++)
        printf("%d|",h[i]);
}

void bestFit(){
    int h[MAX];
    for(int i = 0; i<n; i++) h[i] = holes[i];

    int ans[MAX];

    for(int i = 0; i<m; i++) ans[i] = -1;

    for(int i = 0; i<m; i++){
        int best = -1;
        for(int j = 0; j<n; j++){
            if(h[j] >= processes[i]){
                if(best == -1 || h[j] < h[best]){
                    best = j;
                }
            }
        }
        if(best != -1){
            ans[i] = best;
            h[best] -= processes[i];
        }
    }

    printf("\nBest Fit:\n");
    for(int i = 0; i<m; i++){
        if(ans[i]!=-1){
            printf("P%d (%dK) -> Block %d\n", i, processes[i], ans[i]);
        }
        else{
            printf("P%d (%dK) -> Not Allocated\n", i, processes[i]);
        }
    }

    printf("\nRemaining memory block sizes after best fit allocation:\n");
    for(int i = 0; i<n; i++)
        printf("%d|",h[i]);
}


void worstFit(){
    int h[MAX];
    for(int i = 0; i<n; i++) h[i] = holes[i];

    int ans[MAX];
    for(int i = 0; i<m; i++)ans[i] = -1;

    for(int i = 0; i<m; i++){
        int worst = -1;
        for(int j = 0; j<n; j++){
            if(h[j]>=processes[i]){
                if(worst == -1 || h[j] > h[worst]){
                    worst = j;
                }
            }
        }
        if(worst != -1){
            ans[i] = worst;
            h[worst] -= processes[i];
        }
    }

    printf("\nWorst Fit:\n");
    for(int i=0; i<m; i++){
        if(ans[i] != -1){
            printf("P%d (%dK) -> Block %d\n", i, processes[i], ans[i]);
        }
        else{
            printf("P%d (%dK) -> Not Allocated\n", i, processes[i]);
        }
    }

    printf("\nRemaining memory block sizes after worst fit allocation:\n");
    for(int i = 0; i<n; i++)
        printf("%d|",h[i]);
}

int main(){
    
    printf("Enter the number of holes: ");
    scanf("%d", &n);

    
    printf("\nEnter sizes of holes:\n");
    for(int i = 0; i<n; i++)
        scanf("%d",&holes[i]);
    
    printf("\nEnter the number of processes: ");
    scanf("%d",&m);


    printf("\nEnter the sizes of processes:\n");
    for(int i = 0; i<m; i++)
        scanf("%d",&processes[i]);

    firstFit();
    bestFit();
    worstFit();
}