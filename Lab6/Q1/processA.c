#include<stdio.h>
#include<sys/msg.h>
#include<stdlib.h>
#include<string.h>

struct msg{
	long type;
	int number;
};

int main(){
	int qid = msgget(1236, IPC_CREAT | 0666);

	struct msg message;

	message.type = 1;
	int num;
	printf("Enter a number : ");
	scanf("%d", &num);
	message.number = num;

	msgsnd(qid, &message, sizeof(message.number), 0);
}
