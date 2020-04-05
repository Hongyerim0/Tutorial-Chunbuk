#include <stdio.h>
int main()
{
int i;
int *ptr;
int **dptr;
i = 1234;
printf("[checking values before ptr = &i] \n");
printf("value of i == %d\n", i); //i의 값 1234 프린트
printf("address of i == %p\n", &i); //i의 주소 프린트
printf("value of ptr == %p\n", ptr); //ptr의 값 프린트
printf("address of ptr == %p\n", &ptr);//ptr의 주소 프린트
ptr = &i; /* ptr is now holding the address of i */
printf("\n[checking values after ptr = &i] \n");
printf("value of i == %d\n", i); //i의 값 프린트
printf("address of i == %p\n", &i); //i의 주소 프린트
printf("value of ptr == %p\n", ptr);// ptr의 값 프린트(== i의 주소)
printf("address of ptr == %p\n", &ptr);// ptr의 주소 프린트
printf("value of *ptr == %d\n", *ptr); // p가 가리키고 있는 곳의 값 프린트(==i의 값)
dptr = &ptr; /* dptr is now holding the address of ptr */
printf("\n[checking values after dptr = &ptr] \n");
printf("value of i == %d\n", i); // i의 값 프린트
printf("address of i == %p\n", &i); //i의 주소 프린트
printf("value of ptr == %p\n", ptr); //ptr의 값 프린트(==i의 주소)
printf("address of ptr == %p\n", &ptr); //ptr의 주소 프린트
printf("value of *ptr == %d\n", *ptr); //ptr이 가리키고 있는 곳의 값 프린트
printf("value of dptr == %p\n", dptr); //dptr의 값 프린트(==ptr의 주소)
printf("address of dptr == %p\n", &dptr);//dptr의 주소 프린트
printf("value of *dptr == %p\n", *dptr);// dptr이 가리키고 있는 곳의 값 프린트(==ptr의 값 == i의 주소)
printf("value of **dptr == %d\n", **dptr);// dptr의 값 프린트(==ptr이 가리키고 있는 곳의 값==i의 값)
*ptr = 7777; /* changing the value of *ptr */
printf("\n[after *ptr = 7777] \n"); //ptr이 가리키는 곳의 값을 7777로 변환 (i의 값을 7777로 변환)
printf("value of i == %d\n", i); //i의 값 프린트
printf("value of *ptr == %d\n", *ptr); //ptr이 가리키고 있는 곳의 값 프린트(==i의 값)
printf("value of **dptr == %d\n", **dptr); // dptr의 값 프린트 (==ptr이 가리키고 있는 곳의 값==i의 값)
**dptr = 8888; /* changing the value of **dptr */
printf("\n[after **dptr = 8888] \n"); //dptr의 가리키고 있는 ptr이 가리키는 곳의 값을 8888로 변환 (i의 값을 8888로 변환)
printf("value of i == %d\n", i); // i의 값 프린트
printf("value of *ptr == %d\n", *ptr); // ptr이 가리키는 곳의 값 프린트(==i의 값)
printf("value of **dptr == %d\n", **dptr); //dptr이 가리키고 있는 ptr이 가리키는 곳의 값 프린트(==i의 값)

printf("\n-------Software 홍예림 2019038065-------\n");
return 0;
}
