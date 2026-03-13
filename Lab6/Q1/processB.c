#include<stdio.h>
#include<stdlib.h>
#include<sys/msg.h>

struct msg{
	long type;
	int number;
};

int main(){
	int qid = msgget(1236, IPC_CREAT | 0666);

	struct msg message;

	msgrcv(qid,&message,sizeof(message.number),1,0);

	int rev = 0;
	int n = message.number;
	while(n!=0){
		int rd = n%10;
		rev = rev*10 + rd;
		n /= 10;
	}

	if(rev == message.number){
		printf("Received %d, It is a palindrome!\n", message.number);
	}
	else{
		printf("Received %d, It is not a palindrome!\n", message.number);
	}
}
