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

    int faults = 0;

    //initialize
    for(int i = 0; i<f; i++){
        freq[i] = 0;
        frames[i] = -1;
    }

    for(int i = 0; i<n; i++){
        int pos = search(pages[i], frames, f);

        //hit
        if(pos != -1){
            freq[pos]++;
        }
        //page fault
        else{
            int lfu = 0;
            for(int j = 0; j<f; j++){
                if(freq[j]<freq[lfu]) lfu = j;
            }

            frames[lfu] = pages[i];
            freq[lfu] = 1;
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