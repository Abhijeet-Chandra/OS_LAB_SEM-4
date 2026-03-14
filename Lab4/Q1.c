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
    }
    if(pid == 0){
        printf("Child Process Executing\n");
        printf("Child PID: %d\n",getpid());
        printf("Child PPID: %d\n",getppid());
    }
    else{
        wait(NULL);
        printf("Parent Process Executing\n");
        printf("Parent PID: %d\n",getpid());
        printf("Parent PPID: %d",getppid());
    }
}
