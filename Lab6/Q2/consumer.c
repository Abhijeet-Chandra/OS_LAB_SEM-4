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

    fd = open("fifo1",O_RDONLY);

    if(fd == -1)
    {
        perror("open failed");
        exit(1);
    }

    read(fd,arr,sizeof(arr));

    printf("Received integers: ");
    for(int i=0;i<4;i++)
        printf("%d\t",arr[i]);

    printf("\n");

    close(fd);
    return 0;
}
