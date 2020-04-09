#include<stdio.h>
#include<stdlib.h>
void main(){
    int list[5]; //5개의 정수를 저장하는 배열 선언
    int *plist[5]; //정수에 대한 포인터 5개 선언

    list[0]=10; //list[0]의 값 10으로 초기화
    list[1]=11; //list[1]의 값 11으로 초기화

    plist[0]=(int*)malloc(sizeof(int)); //4bytes를 힙 영역에서 할당해서 그 메모리의 주소를 넘겨 받아 plist[0]에 저장
    
    printf("list[0] \t=%d\n",list[0]); //list[0]의 값 프린트(위에서 초기화 해준 값 10)
    printf("address of list \t=%p\n",list); //list의 시작 주소 프린트(==&list[0])
    printf("address of list[0] \t=%p\n", &list[0]); //list[0]의 주소 프린트
    printf("address of list+0 \t=%p\n", list+0); //list[0]의 주소 프린트
    printf("address of list+1 \t=%p\n", list+1); //list[1]의 주소 프린트,&list[0]보다 4증가 (list+1 == &list[1])
    printf("address of list+2 \t=%p\n", list+2); //list[2]의 주소 프린트,&list[1]보다 4증가(list+2 == &list[2])
    printf("address of list+3 \t=%p\n", list+3); //list[3]의 주소 프린트,&list[2]보다 4증가(list+3 == &list[3])
    printf("address of list+4 \t=%p\n", list+4); //list[4]의 주소 프린트,&list[3]보다 4증가(list+4 == &list[4])
    printf("address of list[4] \t=%p\n", &list[4]); //list[4]의 주소 프린트

    free(plist[0]); // plist[0]에 할당한 메모리 해제

    printf("\n\n----Software 2019038065 홍예림----\n");

}