#include <stdio.h>
int main()
{
char charType;
int integerType;
float floatType;
double doubleType;
printf("Size of char: %ld byte\n",sizeof(charType)); //���� charType��  ũ�� ����Ʈ
printf("Size of int: %ld bytes\n",sizeof(integerType)); //���� integerType�� ũ�� ����Ʈ
printf("Size of float: %ld bytes\n",sizeof(floatType)); //���� floatType�� ũ�� ����Ʈ
printf("Size of double: %ld bytes\n",sizeof(doubleType)); //���� doubleType�� ũ�� ����Ʈ
printf("-----------------------------------------\n"); 
printf("Size of char: %ld byte\n",sizeof(char)); // �ڷ��� char�� ũ�� ����Ʈ
printf("Size of int: %ld bytes\n",sizeof(int)); // �ڷ��� int�� ũ�� ����Ʈ
printf("Size of float: %ld bytes\n",sizeof(float)); //�ڷ��� float�� ũ�� ����Ʈ
printf("Size of double: %ld bytes\n",sizeof(double)); //�ڷ��� double�� ũ�� ����Ʈ
printf("-----------------------------------------\n"); 
printf("Size of char*: %ld byte\n",sizeof(char*)); //char�� ������ ������ ũ�� ����Ʈ
printf("Size of int*: %ld bytes\n",sizeof(int*)); //int�� ������ ������ ũ�� ����Ʈ
printf("Size of float*: %ld bytes\n",sizeof(float*)); //float�� ������ ������ ũ�� ����Ʈ
printf("Size of double*: %ld bytes\n",sizeof(double*)); //double�� ������ ������ ũ�� ����Ʈ
printf("\n-------Software ȫ���� 2019038065-------\n");
return 0;
}