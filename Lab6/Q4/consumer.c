#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/msg.h>
#include<sys/shm.h>
#include<unistd.h>

typedef struct shared{
	int flag;
	char data[];
}shared;

int main(){
	int shmid = shmget(1240, 4096, IPC_CREAT | 0666);
	shared* sh = (shared*)shmat(shmid,NULL,0);

	do {
		while(sh->flag == 0);

		printf("Consumed: %s\n", sh->data);

		sh->flag = 0;
	} while(strcmp(sh->data,"done") != 0);

	shmctl(shmid, IPC_RMID, NULL);
}
