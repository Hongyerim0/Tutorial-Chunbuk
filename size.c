#include<stdio.h>
#include<stdlib.h>

void main()
{
      int **x; //���� ������ ���� **X ����

      printf("sizeof(x)    = %lu\n",  sizeof(x)); //�ּҸ� �����ϱ� ������ 4bytes ����Ʈ
      printf("sizeof(*x)   = %lu\n", sizeof(*x)); //�� �� �������� ���� �ּҸ� �����ϱ� ������ 4bytes ����Ʈ
      printf("sizeof(**x)) = %lu\n", sizeof(**x)); //�� �� �������� ���� ũ��(int��) 4bytes ����Ʈ
      
      printf("\n\n----Software 2019038065 ȫ����----\n");

}
