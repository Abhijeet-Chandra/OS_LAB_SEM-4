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
	sh->flag = 1;
	do{
		while(sh->flag != 1);
		printf("Enter your message: ");
		scanf("%s",msg);
		strcpy(sh->text,msg);
		sh->flag = 0;
		
		if(strcmp(msg,"Bye")==0) break;
		while(sh->flag != 1);
		printf("Received: %s\n", sh->text);

	}while(strcmp(msg, "Bye") != 0);
}
