#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<sys/wait.h>
#include<unistd.h>
#include<string.h>


typedef struct shared{
	int flag;
	char text[100];
}shared;

int main(){
	int shmid = shmget(1888, sizeof(shared), IPC_CREAT | 0666);
	shared* sh = (shared*) shmat(shmid, NULL, 0);

	char msg[100];
	do{
		while(sh->flag != 0);
		printf("Text received: %s\n",sh->text);
		if(strcmp(sh->text,"Bye")==0) break;
		printf("Enter your message: ");
		scanf("%s",msg);
		strcpy(sh->text,msg);
		sh->flag = 1;

	}while(strcmp(msg, "Bye") != 0);
}
