#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>


int main(){
    pid_t pid;
    pid = fork();

    if(pid<0){
        printf("Laude lag gaye");
        exit(1);
    }
    if(pid == 0){
        printf("Loading q1 using exec: ");
        execl("./q1", "q1", NULL);
    }
    else{
        wait(NULL);
        printf("\nParent process Finished\n");
    }
}
