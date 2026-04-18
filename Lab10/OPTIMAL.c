#include<stdio.h>
#include<stdlib.h>

int search(int key, int*frames, int f){
    for(int i = 0; i<f; i++){
        if(frames[i] == key) return i;
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

void optimal(int n, int f, int* pages, int* frames){
    for(int i = 0; i<f; i++) frames[i] = -1;

    int fault = 0;
    for(int i = 0; i<n; i++){
        if(search(pages[i],frames,f)==-1){
            int pos;

            int empty = -1;
            for(int j = 0; j<f; j++){
                if(frames[j] == -1){
                    empty = j;
                    break;
                }
            }
            
            if(empty == -1){
                pos = findOptimal(n,f,pages,frames,i);
            }
            else{
                pos = empty;
            }

            frames[pos]= pages[i];
            fault++;
        }

        printf("Page %d-> ", pages[i]);
        for(int j = 0; j<f; j++){
            printf("%d ",frames[j]);
        }
        printf("\n");
    }
    printf("\nTotal page faults: %d\n",fault);
}

int main(){
    int n,f;
    printf("Enter the number of pages: ");
    scanf("%d", &n);

    int*pages = (int*) malloc(n*sizeof(int));

    printf("\nEnter the reference string: ");
    for(int i = 0; i<n; i++){
        scanf("%d",&pages[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &f);

    int*frames = (int*) malloc(f*sizeof(int));

    optimal(n,f,pages,frames);

}