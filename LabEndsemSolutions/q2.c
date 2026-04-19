// implement LSTF (Largest Seek Time First) disk scheduling along with MFU (Most Frequently Used) page replacement.

// Input:

// Number of frames
// Initial head position
// Pairs of (page number, cylinder position) until user enters -1

// Task:

// First, apply LSTF disk scheduling on the given input.
// Using the resulting order, generate the page request sequence.
// Apply MFU page replacement on the generated sequence and display the results.

#include<stdio.h>
#include<stdlib.h>


typedef struct pair{
    int page_no;
    int cylinder_pos;
}pair;

int search(int key, int* frames, int f){
    for(int i = 0; i<f; i++){
        if(key == frames[i]){
            return i;
        }
    }
    return -1;
}

void LSTF(int n, pair pairs[], int head, pair temp[]){
    int* vis = (int*) calloc(n,sizeof(int));
    int total = 0;
    int k = 0;
    for(int i = 0; i<n; i++){
        int index = -1;
        int max = -1000000;
        for(int j = 0; j<n; j++){
            if(!vis[j]){
                int dist = abs(head-(pairs[j].cylinder_pos));
                if(dist > max){
                    max = dist;
                    index = j;
                }
            }
        }
        temp[k++] = pairs[index];
        total+=max;
        head = pairs[index].cylinder_pos;
        vis[index] = 1;
    }

    printf("\nLSTF Order (page, cylinder):\n");
    for(int i = 0; i<n; i++){
        printf("(%d,%d) ", temp[i].page_no, temp[i].cylinder_pos);
    }
    printf("\n");

    printf("\nTotal seek time: %d\n", total);
}

void MFU(int n, int f, pair pairs[], int* frames){
    printf("\nPage request sequence:\n");
    for(int i = 0; i<n; i++){
        printf("Page-%d ",pairs[i].page_no);
    }

    printf("\n");

    int* freq = (int*)malloc(f*sizeof(int));
    int* time = (int*)malloc(f*sizeof(int)); //using lru as tie breaker

    //initialize:
    for(int i = 0; i<f; i++){
        frames[i] = -1;
        time[i] = 0;
        freq[i] = 0;
    }

    int faults = 0, counter = 0;

    for(int i = 0; i<n; i++){
        int pos = search(pairs[i].page_no,frames,f);

        //hit:
        if(pos != -1){
            time[pos] = ++counter;
            freq[pos]++;
        }
        //page fault:
        else{
            //search for empty position
            int empty_pos = -1;
            for(int j = 0; j<f; j++){
                if(frames[j]==-1){
                    empty_pos = j;
                    break;
                }
            }

            //we have some empty position to insert
            if(empty_pos != -1){
                frames[empty_pos] = pairs[i].page_no;
                time[empty_pos] = ++counter;
                freq[empty_pos] = 1;
            }
            else{
                //apply mfu
                int mfu = 0;
                for(int j = 0; j<f; j++){
                    if(freq[j]>freq[mfu]||(freq[j] == freq[mfu] && time[j]<time[mfu])){
                        mfu = j;
                    }
                }
                frames[mfu] = pairs[i].page_no;
                time[mfu] = ++counter;
                freq[mfu] = 1;
            }
            faults++;
        }

        printf("Page %d -> ",pairs[i].page_no);
        for(int j = 0; j<f; j++){
            if(frames[j] == -1)printf("_ ");
            else printf("%d ",frames[j]);
        }
        printf("\n");
    }

    printf("\nTotal number of misses: %d and hits: %d\n", faults, n-faults);
    free(freq);
    free(time);
}

int main(){
    int n;
    int f;
    
    printf("Enter the number of (pages, cylinder) pair: ");
    scanf("%d", &n);

    pair* pairs = (pair*) malloc(n*sizeof(pair));

    printf("Enter (pages,cylinder) pairs:\n");
    for(int i = 0; i<n; i++){
        scanf("%d %d", &(pairs[i].page_no), &(pairs[i].cylinder_pos));
    }

    int head;
    printf("Enter initial head position: ");
    scanf("%d",&head);

    printf("Enter Number of frames: ");
    scanf("%d", &f);

    int* frames = (int*) malloc(f*sizeof(int));

    pair* temp = (pair*) malloc(n*sizeof(pair));

    LSTF(n,pairs,head,temp);
    MFU(n,f,temp,frames);
    free(pairs);
    free(temp);
    free(frames);
}
