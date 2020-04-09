#include<stdio.h>

void print1 (int *ptr, int rows); //함수 프로토타입 선언

int main()
{

     int one[] = {0,1,2,3,4}; // 배열 one 순차적으로 0,1,2,3,4로 초기화

     printf("one      =%p\n",  one); //one의 값 프린트(==&one[0])
     printf("&one     =%p\n", &one); //one[0]의 주소 프린트
     printf("&one[0]  =%p\n", &one[0]); //one[0]의 주소 프린트
     printf("\n");

     print1(&one[0],5); //print1함수 호출, one[0]의 주소와 5를 인자로 넘겨준다.
     
     printf("----Software 2019038065 홍예림----\n");
     
     return 0;   
 
}

void print1(int *ptr, int rows) //*ptr에 &one[0] 복사,  rows에 5복사
{
    /* print out a one-dimensional array using a pointer */

    int i; // int형 변수 i선언 
    printf("Address \t Contents \n");
    for(i=0; i<rows; i++) // i=0부터 i=4까지 반복
        printf("%p  \t   %5d\n" , ptr + i, *(ptr + i)); //ptr+i가 가리키는 곳의 주소, 가리키는 곳의 값 프린트
     printf("\n");
    
}
