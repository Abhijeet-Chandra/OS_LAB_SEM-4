// Implement LCFS (Last Come First Serve) disk scheduling along with LFU (Least Frequently Used) page replacement.

// Input:

// Number of frames
// Initial head position
// Pairs of (page number, cylinder position) until user enters -1

// Task:

// First, apply LCFS disk scheduling on the given input.
// Using the resulting order, generate the page request sequence.
// Apply LFU page replacement on the generated sequence and display the results.


#include<stdio.h>
#include<stdlib.h>

int search(int key, int*frames, int f){
    for(int i = 0; i<f; i++){
        if(frames[i] == key)return i;
    }
    return -1;
}


typedef struct pair{
    int page_no;
    int cylinder_pos;
}pair;


void LCFS(int n, pair pairs[], int head, pair temp[]){
    int total = 0;
    int k = 0;
    for(int i = n-1; i>=0; i--){
        temp[k++] = pairs[i];
        total+=abs(head-(pairs[i].cylinder_pos));
        head = pairs[i].cylinder_pos;
    }

    printf("\nAfter LCFS, Page request sequence:\n");
    for(int i = 0; i<n; i++){
        printf("(Cylinder position: %d, Page number: %d)\n", temp[i].cylinder_pos, temp[i].page_no);
    }
    printf("\nTotal number of head movements: %d\n",total);

}

void LFU(int n, int f, pair pairs[], int* frames){
    int* freq = (int*) malloc(f*sizeof(int));
    int* time = (int*) malloc(f*sizeof(int));

    //initialize:
    for(int i = 0; i<f; i++){
        frames[i] = -1;
        freq[i] = 0;
        time[i] = 0;
    }

    int counter = 0, faults = 0;

    for(int i = 0; i<n; i++){
        int pos = search(pairs[i].page_no, frames, f);

        //hit
        if(pos != -1){
            time[pos] = ++counter;
            freq[pos]++;
        }
        //page fault
        else{
            int empty_pos = -1;
            for(int j = 0; j<f; j++){
                if(frames[j] == -1){
                    empty_pos = j;
                    break;
                }
            }
            //if empty space is there:
            if(empty_pos != -1){
                frames[empty_pos] = pairs[i].page_no;
                freq[empty_pos] = 1;
                time[empty_pos] = ++counter;
            }
            else{
                //apply lfu
                int lfu = 0;
                for(int j = 0; j<f; j++){
                    if(freq[j]<freq[lfu]||(freq[j]==freq[lfu]&&time[j]<time[lfu])){
                        lfu = j;
                    }
                }
                frames[lfu] = pairs[i].page_no;
                freq[lfu] = 1;
                time[lfu] = ++counter;
            }
            faults++;
        }
        printf("Page %d -> ", pairs[i].page_no);
        for(int j = 0; j<f; j++){
            if(frames[j] == -1)printf("_ ");
            else printf("%d ",frames[j]);
        }
        printf("\n");
    }
    printf("\nNumber of misses: %d and hits: %d", faults, n-faults);

    free(freq);
    free(time);
}

int main(){
    int n,f;
    printf("Enter the number of (page number, cylinder_pos) pairs: ");
    scanf("%d",&n);

    pair* pairs = (pair*) malloc(n*sizeof(pair));

    printf("Enter (page_number, cylinder_pos) pairs:\n");
    for(int i = 0; i<n; i++){
        scanf("%d %d", &(pairs[i].page_no), &(pairs[i].cylinder_pos));
    }

    int head;
    printf("Enter initial head position: ");
    scanf("%d",&head);

    printf("Enter number of frames: ");
    scanf("%d",&f);

    int* frames = (int*) malloc(f*sizeof(int));
    
    pair* temp = (pair*)malloc(n*sizeof(pair));

    LCFS(n,pairs,head,temp);
    LFU(n,f,temp,frames);

    free(pairs);
    free(temp);
    free(frames);
}