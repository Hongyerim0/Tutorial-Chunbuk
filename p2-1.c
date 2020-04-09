#include<stdio.h>
#define MAX_SIZE 100 //MAZ_SIZE==100 

float sum(float [],int); //함수 프로토타입 선언        
float input[MAX_SIZE], answer; //100개의 실수를 저장하는 배열 선언, float형 변수 answer선언  
int i; //int형 변수 i 선언                          

void main(void)                 
{
    for(i=0; i< MAX_SIZE; i++) //i=0부터 i=99까지 반복
    {
        input[i]=i; //배열 input[i]에 i 저장        
    }

    /* for checking call by reference */
    printf("address of input = %p\n", input); // input의 시작주소 프린트(==&input[0]) 

    answer = sum(input,MAX_SIZE); //함수 sum 호출해서 반환받은 값 answer에 저장, 인자로 &input[0]과 100 넘겨준다.            
    printf("The sum is : %f\n", answer); // answer 프린트 (함수 sum을 통해 받은 값 프린트)     
    
    printf("\n----Software 2019038065 홍예림----\n");
}
float sum(float list[], int n ) //list에 &input[0]복사, 100이 n에 복사              
{
    printf("value of list = %p\n", list); // list의 값 출력(== &input[0])      
    printf("address of list = %p\n\n", &list); //list의 주소 출력   

    int i; // int형 변수 i 선언                                      
    float tempsum = 0; // float형 변수 tempsum 선언, 0으로 초기화                          
    for(i=0; i<n; i++) // i=0부터 i=99 까지 반복
       tempsum += list[i]; //temsum = tempsum+ list[i] (0+1+2+3+ ... +99)

    return tempsum; //tempsum 반환
}

