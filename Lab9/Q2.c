#include<stdio.h>
#include<stdlib.h>

int main(){
    int address;
    int page_size = 32;
    printf("Enter logical address: ");
    scanf("%d",&address);

    int page = address/page_size;
    int offset = address%page_size;

    printf("Page number: %d\n",page);
    printf("Offset: %d\n",offset);
    return 0;
}