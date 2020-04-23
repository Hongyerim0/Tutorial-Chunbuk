/*
 * circularQ.c
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4 

typedef char element; //char�� ������Ÿ�� element����

typedef struct { //����ü QueueType ����
	element queue[MAX_QUEUE_SIZE]; //ũ�Ⱑ 4�� element�� �迭 queue����
	int front, rear; //������ ���� front, rear ����
}QueueType;


QueueType* createQueue(); //ť�� �����ϴ� �Լ�
int freeQueue(QueueType *cQ); // �޸� ���� �Լ�
int isEmpty(QueueType* cQ); //ť�� ������� Ȯ���ϴ� �Լ�
int isFull(QueueType* cQ); // ť�� á���� Ȯ���ϴ� �Լ�
void enQueue(QueueType* cQ, element item); //ť�� �����ϴ� �Լ�
void deQueue(QueueType* cQ, element* item); //ť�� �����ϴ� �Լ�
void printQ(QueueType* cQ); // ť�� ����ϴ� �Լ�
void debugQ(QueueType* cQ); // ť�� ���� ����ϴ� �Լ�

element getElement(); //ť�� �Է¹޴� �Լ�

int freeQueue(QueueType* cQ) {   // �޸� ����

	if (cQ == NULL)
		return 1;
	free(cQ);
	return 1;
}


int main(void)
{
    printf("����Ʈ�����а� 2019038065 ȫ����");
	QueueType* cQ = createQueue(); 
	element data; //element�� ���� data����

	char command; //������ ���� cammand����

	do {
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Dubug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) { 
		case 'i': case 'I': // i �Ǵ� I�� �Է�
			data = getElement(); //getElement() ȣ��
			enQueue(cQ, data); //enQueue�Լ� ȣ��
			break;
		case 'd': case 'D': //d �Ǵ� D�� �Է�
			deQueue(cQ, &data); //deQueue�Լ� ȣ��
			break;
		case 'p': case 'P': //p �Ǵ� P�� �Է�
			printQ(cQ); //printQ�Լ� ȣ��
			break;
		case 'b': case 'B': //b �Ǵ� B�Է�
			debugQ(cQ); //debug�Լ� ȣ��
			break;
		case 'q': case 'Q': //q �Ǵ� Q�Է�
			freeQueue(cQ); //freeQueu�Լ� ȣ��
			break;
		default: //�� ���� ���� �Է�
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //��� ���
			break;
		}


	} while (command != 'q' && command != 'Q');

	return 1;
}


QueueType* createQueue()
{
	QueueType* cQ;
	cQ = (QueueType*)malloc(sizeof(QueueType)); //malloc�� ���� �������� �޸𸮸� �Ҵ�޴´�.
	cQ->front = 0; //front�� 0���� �ʱ�ȭ
	cQ->rear = 0; // rear�� 0���� �ʱ�ȭ
	return cQ; // cQ ��ȯ
}

element getElement() 
{
	element item; //element�� ���� item����
	printf("Input element = "); 
	scanf(" %c", &item); //�߰� �� ť�� �Է� �޴´�. 
	return item; //item ��ȯ
}


/* complete the function */
int isEmpty(QueueType* cQ) 
{
	if (cQ->front == cQ->rear) //front�� rear�� ���ٸ� 
		return 1; // 1��ȯ
	else
		return 0;

}

/* complete the function */
int isFull(QueueType* cQ)
{
	if ((cQ->rear + 1) % MAX_QUEUE_SIZE == cQ->front) //rear+1�� MAX_QUEUE_SIZE�� ���� ��������  front�� ���ٸ�
		return 1; // 1��ȯ
	else
		return 0;

}

/* complete the function */
void enQueue(QueueType* cQ, element item)
{
	if (isFull(cQ)) { //isFull�Լ����� 1�� ��ȯ�ȴٸ�
		printf("CIrcular queue is full !!"); // ť�� á�ٴ� �����޼��� ����Ʈ
	}
	else {
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE; // rear�� rear+1�� MAX_QUEUE_SIZE�� ���� ������ ���� ( rear�� 1����)
		cQ->queue[cQ->rear] = item; //rear�� �ϳ� ������ ���� item�� �ִ´�.
	}
	return 0;
}

/* complete the function */
void deQueue(QueueType* cQ, element* item)
{
	if (isEmpty(cQ)) { //isEmpty�Լ����� 1�� ��ȯ�ȴٸ�       
		printf("Circular queue is empty  !!"); //ť�� ����ٴ� �����޼��� ���
	}
	else {
		cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE; /*front�� front+1�� MAX_QUEUE_SIZE�� ���� ������ ���� (front�� 1����)
																			front�� ���ʿ� �ִ� element ����*/
		return  cQ->queue[cQ->front]; //front�� �ϳ� ������ ���� item�� �ִ´�.
	}
	return 0;
}

void printQ(QueueType* cQ) {
	int i, first, last;

	first = (cQ->front + 1) % MAX_QUEUE_SIZE; //first�� front+1�� MAX_QUEUE_SIZE�� ���� �������� ����
	last = (cQ->rear + 1) % MAX_QUEUE_SIZE; //last�� rear+1�� MAX_QUEUE_SIZE�� ���� �������� ����

	printf("Circular Queue : [");

	i = first;
	while (i != last) { //i�� last�� �ٸ������� �ݺ�
		printf("%3c", cQ->queue[i]); //queue[i] ����Ʈ
		i = (i + 1) % MAX_QUEUE_SIZE; 
	}
	printf(" ]\n");
}


void debugQ(QueueType* cQ) {
	printf("\n---DEBUG\n");

	for (int i = 0; i < MAX_QUEUE_SIZE; i++) //i�� MAX_SQUEUE_SIZE(4)���� �ݺ�
	{
		if (i == cQ->front) { // i�� front�� ���ٸ�
			printf("  [%d] = front\n", i); //i�� ����Ʈ
			continue; 
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]); //[i]=queue[i] ����Ʈ
	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);//front�� ���
}
