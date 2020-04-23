/*
 * circularQ.c
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4 

typedef char element; //char형 데이터타입 element선언

typedef struct { //구조체 QueueType 선언
	element queue[MAX_QUEUE_SIZE]; //크기가 4인 element형 배열 queue선언
	int front, rear; //정수형 변수 front, rear 선언
}QueueType;


QueueType* createQueue(); //큐를 생성하는 함수
int freeQueue(QueueType *cQ); // 메모리 해제 함수
int isEmpty(QueueType* cQ); //큐가 비었는지 확인하는 함수
int isFull(QueueType* cQ); // 큐가 찼는지 확인하는 함수
void enQueue(QueueType* cQ, element item); //큐를 삽입하는 함수
void deQueue(QueueType* cQ, element* item); //큐를 삭제하는 함수
void printQ(QueueType* cQ); // 큐를 출력하는 함수
void debugQ(QueueType* cQ); // 큐의 상태 출력하는 함수

element getElement(); //큐를 입력받는 함수

int freeQueue(QueueType* cQ) {   // 메모리 해제

	if (cQ == NULL)
		return 1;
	free(cQ);
	return 1;
}


int main(void)
{
	QueueType* cQ = createQueue(); 
	element data; //element형 변수 data선언

	char command; //문자형 변수 cammand선언

	do {
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Dubug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) { 
		case 'i': case 'I': // i 또는 I를 입력
			data = getElement(); //getElement() 호출
			enQueue(cQ, data); //enQueue함수 호출
			break;
		case 'd': case 'D': //d 또는 D를 입력
			deQueue(cQ, &data); //deQueue함수 호춯
			break;
		case 'p': case 'P': //p 또는 P를 입력
			printQ(cQ); //printQ함수 호출
			break;
		case 'b': case 'B': //b 또는 B입력
			debugQ(cQ); //debug함수 호출
			break;
		case 'q': case 'Q': //q 또는 Q입력
			freeQueue(cQ); //freeQueu함수 호출
			break;
		default: //그 외의 문자 입력
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //경고 출력
			break;
		}

	} while (command != 'q' && command != 'Q');


	return 1;
}


QueueType* createQueue()
{
	QueueType* cQ;
	cQ = (QueueType*)malloc(sizeof(QueueType)); //malloc을 통해 동적으로 메모리를 할당받는다.
	cQ->front = 0; //front를 0으로 초기화
	cQ->rear = 0; // rear을 0으로 초기화
	return cQ; // cQ 반환
}

element getElement() 
{
	element item; //element형 변수 item선언
	printf("Input element = "); 
	scanf(" %c", &item); //추가 할 큐를 입력 받는다. 
	return item; //item 반환
}


/* complete the function */
int isEmpty(QueueType* cQ) 
{
	if (cQ->front == cQ->rear) //front와 rear이 같다면 
		return 1; // 1반환
	else
		return 0;

}

/* complete the function */
int isFull(QueueType* cQ)
{
	if ((cQ->rear + 1) % MAX_QUEUE_SIZE == cQ->front) //rear+1을 MAX_QUEUE_SIZE로 나눈 나머지와  front가 같다면
		return 1; // 1반환
	else
		return 0;

}

/* complete the function */
void enQueue(QueueType* cQ, element item)
{
	if (isFull(cQ)) { //isFull함수에서 1이 반환된다면
		printf("CIrcular queue is full !!"); // 큐가 찼다는 에러메세지 프린트
	}
	else {
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE; // rear에 rear+1을 MAX_QUEUE_SIZE로 나눈 나머지 저장 ( rear값 1증가)
		cQ->queue[cQ->rear] = item; //rear이 하나 증가된 곳에 item을 넣는다.
	}
	return 0;
}

/* complete the function */
void deQueue(QueueType* cQ, element* item)
{
	if (isEmpty(cQ)) { //isEmpty함수에서 1이 반환된다면       
		printf("Circular queue is empty  !!"); //큐가 비었다는 에러메세지 출력
	}
	else {
		cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE; /*front에 front+1을 MAX_QUEUE_SIZE로 나눈 나머지 저장 (front값 1증가)
																			front의 앞쪽에 있는 element 삭제*/
		return  cQ->queue[cQ->front]; //front가 하나 증가된 곳에 item을 넣는다.
	}
	return 0;
}

void printQ(QueueType* cQ) {
	int i, first, last;

	first = (cQ->front + 1) % MAX_QUEUE_SIZE; //first에 front+1을 MAX_QUEUE_SIZE로 나눈 나머지를 저장
	last = (cQ->rear + 1) % MAX_QUEUE_SIZE; //last에 rear+1을 MAX_QUEUE_SIZE로 나눈 나머지를 저장

	printf("Circular Queue : [");

	i = first;
	while (i != last) { //i와 last가 다를때까지 반복
		printf("%3c", cQ->queue[i]); //queue[i] 프린트
		i = (i + 1) % MAX_QUEUE_SIZE; 
	}
	printf(" ]\n");
}


void debugQ(QueueType* cQ) {
	printf("\n---DEBUG\n");

	for (int i = 0; i < MAX_QUEUE_SIZE; i++) //i가 MAX_SQUEUE_SIZE(4)까지 반복
	{
		if (i == cQ->front) { // i가 front와 같다면
			printf("  [%d] = front\n", i); //i를 프린트
			continue; 
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]); //[i]=queue[i] 프린트
	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);//front와 출력
}
