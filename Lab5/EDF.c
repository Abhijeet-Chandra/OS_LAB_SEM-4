#include<stdio.h>
#include<stdlib.h>
int main(){
    int n, e[1000], p[1000], completed = 0,earliest;
    int rt[1000], d[1000], release[1000];
    printf("Enter the number of processes: ");
    scanf("%d",&n);
    for (int i = 0; i < n; i++)
    {
        printf("Enter execution/burst time: ");
        scanf("%d",&e[i]);
        printf("Enter period: ");
        scanf("%d",&p[i]);
        rt[i] = e[i];
        release[i] = p[i];
        d[i] = p[i];
    }
    
    
    int time = 0;
    int limit = 50; //simulation time
    while(time<limit){
        for(int i = 0; i<n; i++){
            if(time == release[i]){
                rt[i] = e[i];
                d[i] = time+p[i];
                release[i]+=p[i];
            }
        }
        int earliest = -1;
        for(int i = 0; i<n; i++){
            if(rt[i]>0){
                if(earliest == -1 || d[i]<d[earliest]){
                    earliest = i;
                }
            }
        }

        if(earliest == -1){
            printf("Idle ");
        }
        else{
            printf("P%d ",earliest);
            rt[earliest]--;
        }
        time++;
    }
}
