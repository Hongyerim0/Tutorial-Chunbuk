#include <stdio.h>
int main()
{
int i;
int *ptr;
int **dptr;
i = 1234;
printf("[checking values before ptr = &i] \n");
printf("value of i == %d\n", i); //i�� �� 1234 ����Ʈ
printf("address of i == %p\n", &i); //i�� �ּ� ����Ʈ
printf("value of ptr == %p\n", ptr); //ptr�� �� ����Ʈ
printf("address of ptr == %p\n", &ptr);//ptr�� �ּ� ����Ʈ
ptr = &i; /* ptr is now holding the address of i */
printf("\n[checking values after ptr = &i] \n");
printf("value of i == %d\n", i); //i�� �� ����Ʈ
printf("address of i == %p\n", &i); //i�� �ּ� ����Ʈ
printf("value of ptr == %p\n", ptr);// ptr�� �� ����Ʈ(== i�� �ּ�)
printf("address of ptr == %p\n", &ptr);// ptr�� �ּ� ����Ʈ
printf("value of *ptr == %d\n", *ptr); // p�� ����Ű�� �ִ� ���� �� ����Ʈ(==i�� ��)
dptr = &ptr; /* dptr is now holding the address of ptr */
printf("\n[checking values after dptr = &ptr] \n");
printf("value of i == %d\n", i); // i�� �� ����Ʈ
printf("address of i == %p\n", &i); //i�� �ּ� ����Ʈ
printf("value of ptr == %p\n", ptr); //ptr�� �� ����Ʈ(==i�� �ּ�)
printf("address of ptr == %p\n", &ptr); //ptr�� �ּ� ����Ʈ
printf("value of *ptr == %d\n", *ptr); //ptr�� ����Ű�� �ִ� ���� �� ����Ʈ
printf("value of dptr == %p\n", dptr); //dptr�� �� ����Ʈ(==ptr�� �ּ�)
printf("address of dptr == %p\n", &dptr);//dptr�� �ּ� ����Ʈ
printf("value of *dptr == %p\n", *dptr);// dptr�� ����Ű�� �ִ� ���� �� ����Ʈ(==ptr�� �� == i�� �ּ�)
printf("value of **dptr == %d\n", **dptr);// dptr�� �� ����Ʈ(==ptr�� ����Ű�� �ִ� ���� ��==i�� ��)
*ptr = 7777; /* changing the value of *ptr */
printf("\n[after *ptr = 7777] \n"); //ptr�� ����Ű�� ���� ���� 7777�� ��ȯ (i�� ���� 7777�� ��ȯ)
printf("value of i == %d\n", i); //i�� �� ����Ʈ
printf("value of *ptr == %d\n", *ptr); //ptr�� ����Ű�� �ִ� ���� �� ����Ʈ(==i�� ��)
printf("value of **dptr == %d\n", **dptr); // dptr�� �� ����Ʈ (==ptr�� ����Ű�� �ִ� ���� ��==i�� ��)
**dptr = 8888; /* changing the value of **dptr */
printf("\n[after **dptr = 8888] \n"); //dptr�� ����Ű�� �ִ� ptr�� ����Ű�� ���� ���� 8888�� ��ȯ (i�� ���� 8888�� ��ȯ)
printf("value of i == %d\n", i); // i�� �� ����Ʈ
printf("value of *ptr == %d\n", *ptr); // ptr�� ����Ű�� ���� �� ����Ʈ(==i�� ��)
printf("value of **dptr == %d\n", **dptr); //dptr�� ����Ű�� �ִ� ptr�� ����Ű�� ���� �� ����Ʈ(==i�� ��)

printf("\n-------Software ȫ���� 2019038065-------\n");
return 0;
}
