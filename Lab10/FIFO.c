#include<stdio.h>
#include<stdlib.h>

int search(int key, int* frame, int f){
    for(int i = 0; i<f; i++){
        if(frame[i] == key) return i;
    }
    return -1;
}

void fifo(int n, int f, int* pages, int* frames){
    int index = 0, faults = 0;

    //initialize frame
    for(int i = 0; i<f; i++) frames[i] = -1;
    for(int i=0; i<n; i++){
        if(search(pages[i], frames, f) == -1){
            frames[index] = pages[i];
            index = (index+1) % f;
            faults ++;
        }

        //display frames:
        printf("Page %d -> ", pages[i]);
        for(int j= 0; j<f; j++){
            printf("%d ", frames[j]);
        }
        printf("\n");
    }

    printf("\nTotal page faults: %d\n", faults);
}

int main(){
    int n,f;

    //pages
    printf("Enter the number of pages: ");
    scanf("%d", &n);

    int *pages = (int*) malloc(n*sizeof(int));

    printf("\nEnter the reeference string:\n");
    for(int i = 0; i<n; i++){
        scanf("%d", &pages[i]);
    }


    printf("Enter the number of frames: ");
    scanf("%d", &f);

    int *frames = (int*) malloc(f*sizeof(int));

    fifo(n,f,pages,frames);

    free(frames);
    free(pages);
}