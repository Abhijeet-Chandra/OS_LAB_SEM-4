#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/msg.h>
#include<sys/shm.h>
#include<unistd.h>

typedef struct shared{
	int flag;
	char data[100];
}shared;

int main(){
	int shmid = shmget(1240, 4096, IPC_CREAT | 0666);
	shared* sh = (shared*)shmat(shmid,NULL,0);

	char str[100];

	do {
		printf("Enter a string: ");
		scanf("%s", str);
		strcpy(sh->data,str);
		sh->flag = 1;

		while(sh->flag == 1);
	} while(strcmp(str,"done") != 0);

	shmdt(sh);
}
