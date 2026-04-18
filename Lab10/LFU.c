#include<stdio.h>
#include<stdlib.h>

int search(int key, int* frames, int f){
    for(int i = 0; i<f; i++){
        if(key == frames[i]) return i;
    }
    return -1;
}

void LFU(int n, int f, int* pages, int* frames){
    int * freq = (int*)  malloc(f*sizeof(int));
    int * time = (int*) malloc(f*sizeof(int));//for breaking tie if frequencies are equal ( basically we will apply LRU then)

    int faults = 0, counter = 0;

    //initialize
    for(int i = 0; i<f; i++){
        freq[i] = 0;
        time[i] = 0;
        frames[i] = -1;
    }

    for(int i = 0; i<n; i++){
        int pos = search(pages[i], frames, f);

        //hit
        if(pos != -1){
            freq[pos]++;
            time[pos] = ++counter;
        }
        //page fault
        else{
            //check if any position is empty
            int pos_empty = -1;
            for(int j = 0; j<f; j++){
                if(frames[j] == -1){
                    pos_empty = j;
                    break;
                }
            }
            //if empty then place it there
            if(pos_empty != -1){
                frames[pos_empty] = pages[i];
                freq[pos_empty] = 1;
                time[pos_empty] = ++counter;
            }
            //else apply lfu
            else{
                int lfu = 0;
                for(int j = 1; j<f; j++){
                    if(freq[j]<freq[lfu] || (freq[j] == freq[lfu]&&time[j]<time[lfu])) lfu = j;
                }

                frames[lfu] = pages[i];
                freq[lfu] = 1;
                time[lfu] = ++counter;
            }
            faults++;
        }

        printf("Page %d -> ", pages[i]);
        for(int j = 0; j < f; j++){
            if(frames[j] == -1) printf("- ");
            else printf("%d ", frames[j]);
        }
        printf("\n");
    }
    printf("\nTotal Page Faults (LFU): %d\n", faults);

    free(freq);
    free(time);
}

int main(){
    int n,f;
    printf("Enter the number of pages: ");
    scanf("%d", &n);

    int* pages = (int*) malloc(n*sizeof(int));

    printf("\nEnter the reference string:\n");

    for(int i = 0; i<n; i++)scanf("%d", &pages[i]);

    printf("Enter the number of frames: ");
    scanf("%d", &f);

    int* frames = (int*) malloc(f*sizeof(int));

    LFU(n,f,pages,frames);

    free(pages);
    free(frames);
}