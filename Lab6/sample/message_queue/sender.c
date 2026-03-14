#include<stdio.h>
#include<stdlib.h>
#include<sys/msg.h>
#include<sys/wait.h>

struct msg{
	long type;
	char text[100];
};

int main(){
	int qid = msgget(6969, IPC_CREAT | 0666);
	struct msg message;
	printf("Enter a string: ");
	scanf("%s", message.text);
	message.type = 1;
	msgsnd(qid, &message, sizeof(message.text), 0);
}

