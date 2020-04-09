#include <stdio.h>
#include <stdlib.h>

void main(){
    int list[5]; // 5개의 정수를 저장하는 배열 선언
    int *plist[5]={NULL,}; // 정수에 대한 포인터 5개 NULL로 초기화

    plist[0]=(int *)malloc(sizeof(int)); //4bytes를 힙 영역에서 할당해서 그 메모리의 주소를 넘겨 받아 plist[0]에 저장

    list[0]=1; //list[0]의 값 1로 초기화
    list[1]=100; //list[0]의 값 100 으로 초기화

    *plist[0]=200; //plist[0]이 가리키는 곳의 값에 200 저장

    printf("value of list[0]  =%d\n",list[0]); //list[0]의 값 프린트 
    printf("address of list[0]      =%p\n",&list[0]); //list[0]의 주소 프린트
    printf("value of list           =%p\n",list); // list[0]의 값 프린트
    printf("address of list (&list) =%p\n",&list); /* list[0]의 주소 프린트
                                                      배열의 이름은 배열의 시작주소이다*/
    printf("-----------------------------------------\n\n");
    printf("value of list[1]     =%d\n",list[1]); //list[1]의 값 프린트
    printf("address of list[1]   =%p\n",&list[1]); //lsit[1]의 주소 프린트
    printf("value of *(list+1)   =%d\n",*(list+1)); //list[1]의 값 프린트 (*(list+1)==list[1])
    printf("address of list+1    =%p\n",list+1); // list[1]의 주소 프린트 (list+1==&list[1])
    

    printf("------------------------------------------\n\n"); 

     printf("value of *plist[0] =%d\n",*plist[0]); // plist[0]이 가리키고 있는 곳(heap영역)의 값(==200) 프린트
     printf("&plist[0]          =%p\n",&plist[0]); //plist[0]의 주소 프린트
     printf("&plist             =%p\n",&plist); //plist[0]의 주소 프린트
     printf("plist              =%p\n",plist); // plist[0]의 주소 프린트(배열의 이름은 배열의 시작주소이다.)
     printf("plist[0]           =%p\n",plist[0]); //plist[0]의 값 프린트(heap영역에 있는 malloc을 통해서 받은 주소)
     printf("plist[1]           =%p\n",plist[1]); //plist[1]의 값 프린트(malloc으로 선언해 중 plist[0]을 제외한 나머지는 null값을 갖는다.)
     printf("plist[2]           =%p\n",plist[2]); //plist[2]의 값 프린트(malloc으로 선언해 중 plist[0]을 제외한 나머지는 null값을 갖는다.)
     printf("plist[3]           =%p\n",plist[3]); //plist[3]의 값 프린트(malloc으로 선언해 중 plist[0]을 제외한 나머지는 null값을 갖는다.)
     printf("plist[4]           =%p\n",plist[4]); //plist[4]의 값 프린트(malloc으로 선언해 중 plist[0]을 제외한 나머지는 null값을 갖는다.)
 
     free(plist[0]); //plist[0]에 할당한 메모리 해제

     printf("\n\n----Software 2019038065 홍예림----\n");
    }

