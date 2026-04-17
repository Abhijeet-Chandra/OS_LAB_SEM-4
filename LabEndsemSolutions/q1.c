/*Note: this program is for single resource*/
#include<stdio.h>
#include<stdlib.h>

int n,m;
#define MAX 10

int blocks[MAX], tempBlocks[MAX], alloc[MAX], max[MAX], need[MAX];

int bestFit(int req){
    int best = -1;
    for(int j = 0; j<m; j++){
        if(tempBlocks[j] >= req){
            if(best == -1 || tempBlocks[j] < tempBlocks[best]){
                best = j;
            }
        }
    }
    return best;
}

int isSafe(int avail){
    int finish[MAX] = {0};
    int safeSeq[MAX];
    int count = 0;
    while(count<n){
        int found = 0;
        for(int i = 0; i<n; i++){
            if(finish[i] == 0 && need[i] <= avail){
                avail+=alloc[i];
                safeSeq[count++] = i;
                finish[i] = 1;
                found = 1;
            }
        }
        if(!found){
            printf("\nUnsafe state\n");
            return 0;
        }
    }

    printf("\nSafe | Seq: ");
    for(int i=0;i<n;i++)
        printf("P%d ", safeSeq[i]);

    printf("\n");

    return 1;
}

int main(){
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the number of memory blocks: ");
    scanf("%d", &m);

    printf("\nEnter the block sizes: \n");
    for(int i = 0; i<m; i++){
        scanf("%d",&blocks[i]);
        tempBlocks[i] = blocks[i];
    }

    printf("Enter the max need for each process: ");
    for(int i = 0; i<n; i++){
        scanf("%d",&max[i]);
        alloc[i] = 0;
        need[i] = max[i];
    }

    while(1){
        int pid, req;
        printf("Enter process id and amount of memory its requesting: ");
        scanf("%d", &pid);
        if(pid == -1)break;
        scanf("%d", &req);

        printf("\nMemory available Before best fit allocation: ");
        for(int i = 0; i<m; i++){
            printf("%d ", tempBlocks[i]);
        }

        //req <= need
        if(req > need[pid]){
            printf("Khatam tata bye bye good bye!");
            continue;
        }

        //the next step that we did generally is checking if req <= available, but here since we have multiple availables ( multiple memory block ), we will use best fit

        int idx = bestFit(req);

        if(idx == -1){
            printf("No suitable block\n");
            continue;
        }

        //allocate:
        tempBlocks[idx] -= req;
        need[pid] -= req;
        alloc[pid] += req;

        //calculate total available memory (this we will use to check if system is in safe state or not)
        int avail = 0;
        for(int i = 0; i<m; i++) avail += tempBlocks[i];

        printf("\nMemory available after best fit allocation: ");
        for(int i = 0; i<m; i++){
            printf("%d ", tempBlocks[i]);
        }

        //safety check (bankers algo):

        if(!isSafe(avail)){
            //roll back
            tempBlocks[idx] += req;
            alloc[pid] -=req;
            need[pid] += req;
            printf("\nRequest rolled back\n");
        }
    }

    printf("\nFinal Allocation:\n");
    for(int i=0;i<n;i++)
        printf("P%d: %d\n", i, alloc[i]);

        
    return 0;
}
