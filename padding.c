#include <stdio.h>
#include <stdlib.h>

struct student{
    char lastName[13]; /* 13 bytes*/
    int studentId; /* 4bytes */
    short grade; /* 2 bytes */
};

int main(){

    struct student pst; //student����ü pst����
    
    printf("size of student= %ld\n",sizeof(struct student)); /* student����ü�� ũ��� 19byte���� lastname�� ������ 3byte 
                                                               graded�� ������ 2bytes�� �е�ó���� �Ͽ� 16+4+4=24bytes�� ����Ʈ ��*/ 
    printf("size of int= %ld\n",sizeof(int)); //�ڷ��� int�� ũ�� ����Ʈ
    printf("size of short= %ld",sizeof(short)); //�ڷ��� short�� ũ�� ����Ʈ

    printf("\n\n----Software 2019038065 ȫ����----\n");

    return 0;

}

