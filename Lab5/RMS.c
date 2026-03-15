#include<stdio.h>
#include<stdlib.h>

int main(){
    int p[100], e[100]; //given
    int release[100],rt[100];
    int time = 0, limit = 50,n;

    printf("Enter the number of processes: ");
    scanf("%d",&n);
    for(int i = 0; i<n; i++){
        printf("Enter burst time: ");
        scanf("%d",&e[i]);
        printf("Enter period: ");
        scanf("%d",&p[i]);
        release[i] = 0;
        rt[i] = e[i];
    }
    while(time<limit){
        for(int i = 0; i<n; i++){
            if(time == release[i]){
                rt[i] = e[i];
                release[i] += p[i];
            }
        }

        int chosen = -1;
        for(int i = 0; i<n; i++){
            if(rt[i]>0){
                if(chosen == -1 || p[i] < p[chosen]){
                    chosen = i;
                }
            }
        }
        if(chosen == -1){
            printf("Idle ");
        }
        else{
            printf("P%d ",chosen);
            rt[chosen]--;
        }
        time++;
    }
}
