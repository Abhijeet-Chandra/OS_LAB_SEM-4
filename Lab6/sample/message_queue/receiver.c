#include<stdio.h>
#include<stdlib.h>
#include<sys/msg.h>
#include<sys/wait.h>
#include<string.h>
struct msg{
	long type;
	char text[100];
};

int main(){
	struct msg message;
	int qid = msgget(6969, IPC_CREAT | 0666);
	msgrcv(qid, &message, sizeof(message.text), 1, 0);
	printf("Size of %s is %d\n", message.text, strlen(message.text));
}
