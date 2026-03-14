#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(){
    pid_t pid;
    pid = fork();

    if(pid<0){
        printf("Mera ghee khatam hai");
        exit(1);
    }
    else if(pid == 0){
        printf("Child process exiting..\n");
        exit(0);
    }
    else{
        printf("Parent starting its execution..\n");
        sleep(30);
        printf("Parent finished(but child already ded😭😭😭so sadddddddddd)\n");
    }
    return 0;

}
