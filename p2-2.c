#include<stdio.h>

void print1 (int *ptr, int rows); //�Լ� ������Ÿ�� ����

int main()
{

     int one[] = {0,1,2,3,4}; // �迭 one ���������� 0,1,2,3,4�� �ʱ�ȭ

     printf("one      =%p\n",  one); //one�� �� ����Ʈ(==&one[0])
     printf("&one     =%p\n", &one); //one[0]�� �ּ� ����Ʈ
     printf("&one[0]  =%p\n", &one[0]); //one[0]�� �ּ� ����Ʈ
     printf("\n");

     print1(&one[0],5); //print1�Լ� ȣ��, one[0]�� �ּҿ� 5�� ���ڷ� �Ѱ��ش�.
     
     printf("----Software 2019038065 ȫ����----\n");
     
     return 0;   
 
}

void print1(int *ptr, int rows) //*ptr�� &one[0] ����,  rows�� 5����
{
    /* print out a one-dimensional array using a pointer */

    int i; // int�� ���� i���� 
    printf("Address \t Contents \n");
    for(i=0; i<rows; i++) // i=0���� i=4���� �ݺ�
        printf("%p  \t   %5d\n" , ptr + i, *(ptr + i)); //ptr+i�� ����Ű�� ���� �ּ�, ����Ű�� ���� �� ����Ʈ
     printf("\n");
    
}
