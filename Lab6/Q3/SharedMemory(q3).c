#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/msg.h>
#include<sys/wait.h>
#include<sys/shm.h>
#include<unistd.h>


int main(){
	pid_t pid;
	int shmid = shmget(1235, sizeof(char), IPC_CREAT | 0666);
	char *a = (char*) shmat(shmid, NULL, 0);

	pid = fork();
	if(pid == 0){
		sleep(5);
		printf("Successor is: %c", (char)(a[0]+1)); 
	}
	else{
		printf("Enter a character: ");
		scanf("%s", a);
	}
	shmdt(a);
	shmctl(shmid, IPC_RMID, NULL);
}
