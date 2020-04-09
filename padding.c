#include <stdio.h>
#include <stdlib.h>

struct student{
    char lastName[13]; /* 13 bytes*/
    int studentId; /* 4bytes */
    short grade; /* 2 bytes */
};

int main(){

    struct student pst; //student구조체 pst선언
    
    printf("size of student= %ld\n",sizeof(struct student)); /* student구조체의 크기는 19byte지만 lastname의 나머지 3byte 
                                                               graded의 나머지 2bytes를 패딩처리를 하여 16+4+4=24bytes가 프린트 됨*/ 
    printf("size of int= %ld\n",sizeof(int)); //자료형 int의 크기 프린트
    printf("size of short= %ld",sizeof(short)); //자료형 short의 크기 프린트

    printf("\n\n----Software 2019038065 홍예림----\n");

    return 0;

}

