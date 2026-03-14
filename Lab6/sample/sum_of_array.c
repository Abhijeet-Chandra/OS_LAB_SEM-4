#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/msg.h>
#include<sys/shm.h>

typedef struct shared{
	int flag;
	int arr[5];
}shared;


int main(){
	int shmid = shmget(1999, sizeof(shared), IPC_CREAT | 0666);
	shared* sh = (shared*) shmat(shmid, NULL, 0);
	pid_t pid;
	pid = fork();

	sh->flag = 0;
	if(pid == 0){
		while(sh->flag == 0);
		int sum = 0;
		for(int i = 0; i<5; i++){
			sum+=sh->arr[i];
		}
		printf("sum is %d\n",sum);
	}
	else{
		printf("Enter the numbers in array: ");
		for(int i = 0; i<5; i++){
			scanf("%d", &(sh->arr[i]));
		}
		sh->flag = 1;
	}

}
