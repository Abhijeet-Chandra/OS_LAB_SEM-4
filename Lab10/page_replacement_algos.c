#include<stdio.h>
#include<stdlib.h>

int search(int key, int* frames, int f){
    for(int i = 0; i<f; i++){
        if(key == frames[i]) return i;
    }

    return -1;
}

int findOptimal(int n, int f, int*pages, int*frames, int index){
    int farthest = index, pos = -1;
    for(int i = 0; i<f; i++){
        int j;
        for(j = index+1; j<n; j++){
            if(pages[j] == frames[i]){
                if(j > farthest){
                    farthest = j;
                    pos = i;
                }
                break;
            }
        }
        if(j == n) return i;
    }

    if(pos == -1)return 0;
    else return pos;
}

void fifo(int n, int f, int* pages, int* frames){
    int index = 0, faults = 0;

    //initialize frame
    for(int i = 0; i<f; i++) frames[i] = -1;

    for(int i = 0; i<n; i++){
        int pos = search(pages[i],frames,f);
        //hit
        if(pos != -1){
            //do nothing
        }
        //page fault
        else{
            frames[index] = pages[i];
            index = (index+1) % f;
            faults++;
        }

        printf("Page %d -> ", pages[i]);
        for(int j = 0; j<f; j++){
            if(frames[j] == -1)printf("_ ");
            else printf("%d ", frames[j]);
        }
        printf("\n");
    }

    printf("Total misses: %d\nTotal hits: %d", faults, n-faults);
}

void optimal(int n, int f, int* pages, int* frames){
    int faults = 0;
    for(int i = 0; i<f; i++) frames[i] = -1;
    for(int i = 0; i<n; i++){
        int pos = search(pages[i],frames,f);

        //hit
        if(pos != -1){
            //do nothing
        }
        else{
            int empty_pos = -1;
            for(int j = 0; j<f; j++){
                if(frames[j] == -1){
                    empty_pos = j;
                    break;
                }
            }

            //if there is some empty position:
            if(empty_pos != -1){
                frames[empty_pos] = pages[i];
            }
            else{
                frames[findOptimal(n,f,pages,frames,i)] = pages[i];
            }
            faults++;
        }
        printf("Page %d -> ", pages[i]);
        for(int j = 0; j<f; j++){
            if(frames[j] == -1)printf("_ ");
            else printf("%d ", frames[j]);
        }
        printf("\n");
    }
    printf("Total misses: %d\nTotal hits: %d", faults, n-faults);
}

void LRU(int n, int f, int* pages, int* frames){
    int* time = (int*) malloc(f*sizeof(int));
    int counter = 0, faults = 0;

    for(int i = 0; i<f; i++){
        time[i] = 0;
        frames[i] = -1;
    }

    for(int i = 0; i<n; i++){
        int pos = search(pages[i], frames, f);
        //hit
        if(pos != -1){
            time[pos] = ++counter;
        }
        else{

            //checking if empty space is available
            int empty_pos = -1;
            for(int j = 0; j<f; j++){
                if(frames[j] == -1){
                    empty_pos = j;
                    break;
                }
            }

            //if empty space is available:
            if(empty_pos != -1){
                frames[empty_pos] = pages[i];
                time[empty_pos] = ++ counter;
            }
            //if no empty space then apply lru
            else{
                int lru = 0;
                for(int j = 1; j<f; j++){
                    if(time[j]<time[lru]){
                        lru = j;
                    }
                }
                frames[lru] = pages[i];
                time[lru] = ++counter;
            }
            faults++;
        }

        printf("Page %d -> ", pages[i]);
        for(int j = 0; j<f; j++){
            if(frames[j] == -1)printf("_ ");
            else printf("%d ", frames[j]);
        }
        printf("\n");
    }
    printf("Total misses: %d\nTotal hits: %d", faults, n-faults);
}

void LFU(int n, int f, int* pages, int* frames){
    int* freq = (int* )malloc(f*sizeof(int));
    int* time = (int* )malloc(f*sizeof(int));
    //initialize:
    for(int i = 0; i<f; i++){
        frames[i] = -1;
        time[i] = 0;
        freq[i] = 0;
    }

    int counter = 0, faults = 0;
    for(int i = 0; i<n; i++){
        int pos = search(pages[i], frames, f);
        
        //hit:
        if(pos != -1){
            freq[pos]++;
            time[pos] = ++counter;
        }
        //page fault:
        else{
            //check if there is any empty space:
            int empty_pos = -1;
            for(int j = 0; j<f; j++){
                if(frames[j] == -1){
                    empty_pos = j;
                    break;
                }
            }
            //if empty:
            if(empty_pos != -1){
                frames[empty_pos] = pages[i];
                time[empty_pos] = ++counter;
                freq[empty_pos] = 1;
            }
            //if not empty apply lfu:
            else{
                int lfu = 0;
                for(int j = 0; j<f; j++){
                    if(freq[j]<freq[lfu]||(freq[j]==freq[lfu]&&time[j]<time[lfu])){
                        lfu = j;
                    }
                }
                frames[lfu] = pages[i];
                time[lfu] = ++counter;
                freq[lfu] = 1;
            }
            faults++;
        }

        printf("Page %d -> ", pages[i]);
        for(int j = 0; j<f; j++){
            if(frames[j] == -1)printf("_ ");
            else printf("%d ", frames[j]);
        }
        printf("\n");
    }
    printf("Total misses: %d\nTotal hits: %d", faults, n-faults);
}

void MFU(int n, int f, int* pages, int* frames){
    int* freq = (int*) malloc(f*sizeof(int));
    int* time = (int*) malloc(f*sizeof(int));

    //initialize
    for(int i = 0; i<f; i++){
        freq[i] = 0;
        time[i] = 0;
        frames[i] = -1;
    }

    int counter = 0, faults = 0;

    for(int i = 0; i<n; i++){
        int pos = search(pages[i],frames,f);

        //hit:
        if(pos != -1){
            time[pos] = ++counter;
            freq[pos]++;
        }
        //page fault
        else{
            int empty_pos = -1;
            //check for empty space:
            for(int j = 0; j<f; j++){
                if(frames[j] == -1){
                    empty_pos = j;
                    break;
                }
            }

            //empty slot is there:
            if(empty_pos != -1){
                frames[empty_pos] = pages[i];
                time[empty_pos] = ++counter;
                freq[empty_pos] = 1;
            }
            //no empty slot, apply mfu
            else{
                int mfu = 0;
                for(int j = 0; j<f; j++){
                    if(freq[j] > freq[mfu]||(freq[j] == freq[mfu] && time[j] < time[mfu])){
                        mfu = j;
                    }
                }

                frames[mfu] = pages[i];
                freq[mfu] = 1;
                time[mfu] = ++counter;
            }
            faults++;
        }

        printf("Page %d -> ", pages[i]);
        for(int j = 0; j<f; j++){
            if(frames[j] == -1) printf("_ ");
            else printf("%d ", frames[j]);
        }
        printf("\n");
    }
    printf("Total misses: %d\nTotal hits: %d", faults, n-faults);
}
int main(){
    int n,f;
    printf("Enter the number of pages: ");
    scanf("%d", &n);

    int* pages = (int*) malloc(n*sizeof(int));
    printf("\nEnter the reference string: ");
    for(int i = 0; i<n; i++){
        scanf("%d", &pages[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &f);

    int* frames = (int*) malloc(f*sizeof(int));

    printf("\nFIFO: \n");
    fifo(n,f,pages,frames);

    printf("\nOptimal: \n");
    optimal(n,f,pages,frames);

    printf("\nLRU:\n");
    LRU(n,f,pages,frames);

    printf("\nLFU:\n");
    LFU(n,f,pages,frames);

    printf("\nMFU\n");
    MFU(n,f,pages,frames);
}