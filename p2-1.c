#include<stdio.h>
#define MAX_SIZE 100 //MAZ_SIZE==100 

float sum(float [],int); //�Լ� ������Ÿ�� ����        
float input[MAX_SIZE], answer; //100���� �Ǽ��� �����ϴ� �迭 ����, float�� ���� answer����  
int i; //int�� ���� i ����                          

void main(void)                 
{
    for(i=0; i< MAX_SIZE; i++) //i=0���� i=99���� �ݺ�
    {
        input[i]=i; //�迭 input[i]�� i ����        
    }

    /* for checking call by reference */
    printf("address of input = %p\n", input); // input�� �����ּ� ����Ʈ(==&input[0]) 

    answer = sum(input,MAX_SIZE); //�Լ� sum ȣ���ؼ� ��ȯ���� �� answer�� ����, ���ڷ� &input[0]�� 100 �Ѱ��ش�.            
    printf("The sum is : %f\n", answer); // answer ����Ʈ (�Լ� sum�� ���� ���� �� ����Ʈ)     
    
    printf("\n----Software 2019038065 ȫ����----\n");
}
float sum(float list[], int n ) //list�� &input[0]����, 100�� n�� ����              
{
    printf("value of list = %p\n", list); // list�� �� ���(== &input[0])      
    printf("address of list = %p\n\n", &list); //list�� �ּ� ���   

    int i; // int�� ���� i ����                                      
    float tempsum = 0; // float�� ���� tempsum ����, 0���� �ʱ�ȭ                          
    for(i=0; i<n; i++) // i=0���� i=99 ���� �ݺ�
       tempsum += list[i]; //temsum = tempsum+ list[i] (0+1+2+3+ ... +99)

    return tempsum; //tempsum ��ȯ
}

