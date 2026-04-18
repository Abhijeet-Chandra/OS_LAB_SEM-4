#include<stdio.h>
#include<stdlib.h>


int search(int key, int* frames, int f){
    for(int i = 0; i<f; i++){
        if(key == frames[i]) return i;
    }
    return -1;
}

void LRU(int n, int f, int*pages, int* frames){
    int time[f];
    int faults = 0, counter = 0;

    //initialize:
    for(int i = 0; i<f; i++){
        time[i] = 0;
        frames[i] = -1;
    }

    for(int i = 0; i<n; i++){
        int pos = search(pages[i], frames, f);

        //hit:
        if(pos != -1){
            time[pos] = ++counter;
        }
        //page fault
        else{
            int lru = 0;
            for(int j = 1; j<f; j++){
                if(time[j]<time[lru]) lru = j;
            }

            frames[lru] = pages[i];
            time[lru] = ++counter;
            faults++;
        }

        printf("Page %d -> ", pages[i]);
        for(int j = 0; j < f; j++){
            if(frames[j] == -1) printf("- ");
            else printf("%d ", frames[j]);
        }
        printf("\n");
    }

    printf("\nTotal Page Faults (LRU): %d\n", faults);
}

int main(){
    int n,f;
    printf("Enter the number of pages: ");
    scanf("%d", &n);

    int *pages = (int*) malloc(n*sizeof(pages));
    printf("\nEnter reference string: ");
    for(int i = 0; i<n; i++)scanf("%d", &pages[i]);

    printf("Enter the number of frames: ");
    scanf("%d", &f);

    int* frames = (int*) malloc(f*sizeof(int));

    LRU(n,f,pages,frames);

    free(pages);
    free(frames);
}