/*
 * circularQ.c
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4 

typedef char element; //charÇü µ¥ÀÌÅÍÅ¸ÀÔ element¼±¾ð

typedef struct { //±¸Á¶Ã¼ QueueType ¼±¾ð
	element queue[MAX_QUEUE_SIZE]; //Å©±â°¡ 4ÀÎ elementÇü ¹è¿­ queue¼±¾ð
	int front, rear; //Á¤¼öÇü º¯¼ö front, rear ¼±¾ð
}QueueType;


QueueType* createQueue(); //Å¥¸¦ »ý¼ºÇÏ´Â ÇÔ¼ö
int freeQueue(QueueType *cQ); // ¸Þ¸ð¸® ÇØÁ¦ ÇÔ¼ö
int isEmpty(QueueType* cQ); //Å¥°¡ ºñ¾ú´ÂÁö È®ÀÎÇÏ´Â ÇÔ¼ö
int isFull(QueueType* cQ); // Å¥°¡ Ã¡´ÂÁö È®ÀÎÇÏ´Â ÇÔ¼ö
void enQueue(QueueType* cQ, element item); //Å¥¸¦ »ðÀÔÇÏ´Â ÇÔ¼ö
void deQueue(QueueType* cQ, element* item); //Å¥¸¦ »èÁ¦ÇÏ´Â ÇÔ¼ö
void printQ(QueueType* cQ); // Å¥¸¦ Ãâ·ÂÇÏ´Â ÇÔ¼ö
void debugQ(QueueType* cQ); // Å¥ÀÇ »óÅÂ Ãâ·ÂÇÏ´Â ÇÔ¼ö

element getElement(); //Å¥¸¦ ÀÔ·Â¹Þ´Â ÇÔ¼ö

int freeQueue(QueueType* cQ) {   // ¸Þ¸ð¸® ÇØÁ¦

	if (cQ == NULL)
		return 1;
	free(cQ);
	return 1;
}


int main(void)
{
    printf("¼ÒÇÁÆ®¿¡¾îÇÐ°ú 2019038065 È«¿¹¸²");
	QueueType* cQ = createQueue(); 
	element data; //elementÇü º¯¼ö data¼±¾ð

	char command; //¹®ÀÚÇü º¯¼ö cammand¼±¾ð

	do {
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Dubug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) { 
		case 'i': case 'I': // i ¶Ç´Â I¸¦ ÀÔ·Â
			data = getElement(); //getElement() È£Ãâ
			enQueue(cQ, data); //enQueueÇÔ¼ö È£Ãâ
			break;
		case 'd': case 'D': //d ¶Ç´Â D¸¦ ÀÔ·Â
			deQueue(cQ, &data); //deQueueÇÔ¼ö È£­Œ
			break;
		case 'p': case 'P': //p ¶Ç´Â P¸¦ ÀÔ·Â
			printQ(cQ); //printQÇÔ¼ö È£Ãâ
			break;
		case 'b': case 'B': //b ¶Ç´Â BÀÔ·Â
			debugQ(cQ); //debugÇÔ¼ö È£Ãâ
			break;
		case 'q': case 'Q': //q ¶Ç´Â QÀÔ·Â
			freeQueue(cQ); //freeQueuÇÔ¼ö È£Ãâ
			break;
		default: //±× ¿ÜÀÇ ¹®ÀÚ ÀÔ·Â
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //°æ°í Ãâ·Â
			break;
		}


	} while (command != 'q' && command != 'Q');

	return 1;
}


QueueType* createQueue()
{
	QueueType* cQ;
	cQ = (QueueType*)malloc(sizeof(QueueType)); //mallocÀ» ÅëÇØ µ¿ÀûÀ¸·Î ¸Þ¸ð¸®¸¦ ÇÒ´ç¹Þ´Â´Ù.
	cQ->front = 0; //front¸¦ 0À¸·Î ÃÊ±âÈ­
	cQ->rear = 0; // rearÀ» 0À¸·Î ÃÊ±âÈ­
	return cQ; // cQ ¹ÝÈ¯
}

element getElement() 
{
	element item; //elementÇü º¯¼ö item¼±¾ð
	printf("Input element = "); 
	scanf(" %c", &item); //Ãß°¡ ÇÒ Å¥¸¦ ÀÔ·Â ¹Þ´Â´Ù. 
	return item; //item ¹ÝÈ¯
}


/* complete the function */
int isEmpty(QueueType* cQ) 
{
	if (cQ->front == cQ->rear) //front¿Í rearÀÌ °°´Ù¸é 
		return 1; // 1¹ÝÈ¯
	else
		return 0;

}

/* complete the function */
int isFull(QueueType* cQ)
{
	if ((cQ->rear + 1) % MAX_QUEUE_SIZE == cQ->front) //rear+1À» MAX_QUEUE_SIZE·Î ³ª´« ³ª¸ÓÁö¿Í  front°¡ °°´Ù¸é
		return 1; // 1¹ÝÈ¯
	else
		return 0;

}

/* complete the function */
void enQueue(QueueType* cQ, element item)
{
	if (isFull(cQ)) { //isFullÇÔ¼ö¿¡¼­ 1ÀÌ ¹ÝÈ¯µÈ´Ù¸é
		printf("CIrcular queue is full !!"); // Å¥°¡ Ã¡´Ù´Â ¿¡·¯¸Þ¼¼Áö ÇÁ¸°Æ®
	}
	else {
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE; // rear¿¡ rear+1À» MAX_QUEUE_SIZE·Î ³ª´« ³ª¸ÓÁö ÀúÀå ( rear°ª 1Áõ°¡)
		cQ->queue[cQ->rear] = item; //rearÀÌ ÇÏ³ª Áõ°¡µÈ °÷¿¡ itemÀ» ³Ö´Â´Ù.
	}
	return 0;
}

/* complete the function */
void deQueue(QueueType* cQ, element* item)
{
	if (isEmpty(cQ)) { //isEmptyÇÔ¼ö¿¡¼­ 1ÀÌ ¹ÝÈ¯µÈ´Ù¸é       
		printf("Circular queue is empty  !!"); //Å¥°¡ ºñ¾ú´Ù´Â ¿¡·¯¸Þ¼¼Áö Ãâ·Â
	}
	else {
		cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE; /*front¿¡ front+1À» MAX_QUEUE_SIZE·Î ³ª´« ³ª¸ÓÁö ÀúÀå (front°ª 1Áõ°¡)
																			frontÀÇ ¾ÕÂÊ¿¡ ÀÖ´Â element »èÁ¦*/
		return  cQ->queue[cQ->front]; //front°¡ ÇÏ³ª Áõ°¡µÈ °÷¿¡ itemÀ» ³Ö´Â´Ù.
	}
	return 0;
}

void printQ(QueueType* cQ) {
	int i, first, last;

	first = (cQ->front + 1) % MAX_QUEUE_SIZE; //first¿¡ front+1À» MAX_QUEUE_SIZE·Î ³ª´« ³ª¸ÓÁö¸¦ ÀúÀå
	last = (cQ->rear + 1) % MAX_QUEUE_SIZE; //last¿¡ rear+1À» MAX_QUEUE_SIZE·Î ³ª´« ³ª¸ÓÁö¸¦ ÀúÀå

	printf("Circular Queue : [");

	i = first;
	while (i != last) { //i¿Í last°¡ ´Ù¸¦¶§±îÁö ¹Ýº¹
		printf("%3c", cQ->queue[i]); //queue[i] ÇÁ¸°Æ®
		i = (i + 1) % MAX_QUEUE_SIZE; 
	}
	printf(" ]\n");
}


void debugQ(QueueType* cQ) {
	printf("\n---DEBUG\n");

	for (int i = 0; i < MAX_QUEUE_SIZE; i++) //i°¡ MAX_SQUEUE_SIZE(4)±îÁö ¹Ýº¹
	{
		if (i == cQ->front) { // i°¡ front¿Í °°´Ù¸é
			printf("  [%d] = front\n", i); //i¸¦ ÇÁ¸°Æ®
			continue; 
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]); //[i]=queue[i] ÇÁ¸°Æ®
	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);//front¿Í Ãâ·Â
}
