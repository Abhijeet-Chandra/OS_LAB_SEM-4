#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>

int main()
{
    int fd;
    int arr[4];

    mkfifo("fifo1",0666);

    fd = open("fifo1",O_WRONLY);

    if(fd == -1)
    {
        perror("open failed");
        exit(1);
    }

    printf("Enter 4 integers: ");
    for(int i=0;i<4;i++)
        scanf("%d",&arr[i]);

    write(fd,arr,sizeof(arr));

    close(fd);
    return 0;
}
