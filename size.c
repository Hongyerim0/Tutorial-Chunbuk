#include<stdio.h>
#include<stdlib.h>

void main()
{
      int **x; //이중 포인터 변수 **X 선언

      printf("sizeof(x)    = %lu\n",  sizeof(x)); //주소를 저장하기 때문에 4bytes 프린트
      printf("sizeof(*x)   = %lu\n", sizeof(*x)); //한 번 역참조한 곳의 주소를 저장하기 때문에 4bytes 프린트
      printf("sizeof(**x)) = %lu\n", sizeof(**x)); //두 번 역참조한 곳의 크기(int형) 4bytes 프린트
      
      printf("\n\n----Software 2019038065 홍예림----\n");

}
