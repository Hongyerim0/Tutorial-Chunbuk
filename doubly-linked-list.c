/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */

#include<stdio.h>
#include<stdlib.h>
 /* 필요한 헤더파일 추가 if necessary */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
		 singly-linked-list의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
		- initialize와 왜 다른지 이해 할것
		 - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode = NULL;

	printf("소프트웨어학과 2019038065 홍예림 \n\n");
	do {
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}
	} while (command != 'q' && command != 'Q');

	return 1;
}

int initialize(headNode** h) {
	if (*h != NULL) {
		freeList(*h);
	}
	*h = (headNode*)malloc(sizeof(headNode));
	(*h)->first = NULL;
	return 1;
}

int freeList(headNode* h) {
   //h와 연결된 listnode 메모리 해제
   //headnode도 해제되어야함
	listNode* p = h->first;
	listNode* prev = NULL;
	while (p != NULL) {
		prev = p;
		p = p->llink;
		free(prev);
	}
	free(h);
	return 0;
}

void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while (p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->rlink = NULL;
	node->llink = NULL;
	node->key = key;
	if (h->first == NULL) {
		h->first = node; // List가 비어있으면 제일 처음에 삽입
		return 0;
	}
listNode* tmp = h->first;
while (tmp->rlink != NULL) { //맨 마지막 노드로 이동
	tmp = tmp->rlink;
}
tmp->rlink = node;  // 맨 마지막 노드 다음에 삽입
node->llink = tmp; 

return 0;
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	listNode* tmp = h->first;
	listNode* prev = NULL;

	if (h->first == NULL) {
		printf("nothing to delete");
		return 0;
	}
	//마지막 노드를 탐색
	while (tmp->rlink != NULL) {
		prev = tmp; // while을 벗어나면 prev가 가리키는 노드가 마지막에서 두 번째 노드
		tmp = tmp->rlink; //while을 벗어나면 tmp가 가리키는 노드가 마지막 노드
	}
	if (prev == NULL) { // 리스트에 노드가 한 개 뿐이면 첫 원소 삭제
		deleteFirst(h);
	}
	else {
		prev->rlink = tmp->rlink; //마지막에서 두 번째 노드가 NULL을 가리키도록 함
		free(tmp); // 메모리해제
	}
	return 0;
}

/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	listNode* tmp = h->first;
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;

	if (h->first == NULL) { //List가 비었으면 처음에 삽입
		h->first = node;
		return 0;
	}
	node->rlink = h->first; //head가 가리키는 노드가 node가 오른쪽으로 가리키는 노드
	node->llink = NULL; //node가 list처음이기 때문에 왼쪽은 NULL

	h->first = node; //노드가 첫번째 원소
	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	if (h->first == NULL) {
		printf("nothing to delete");
		return 0;
	}
	listNode* tmp = h->first;
	h->first = tmp->rlink; //head가 가리키는 노드의 다음 노드를 head가 가리키는 노드로 변경

	free(tmp); // 메모리 해제

	return 0;
}

/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
	listNode* p = h->first;
	listNode* q = NULL; //뒤집힌 리스트의 첫 번째 노드를 가리킬 포인터
	listNode* r = NULL; //뒤집힌 리스트를 이어나갈 임시 포인터

	while (p != NULL) {
		r = q; //뒤집힌 리스트를 임시 저장
		q = p; //그 다음으로 이어줘야 하는 노드를 받아옴
		p = p->rlink; //p는 다음 노드 저장
		q->rlink = r; //r에 q의 다음 노드 저장
		q->llink = p; //p에 q의 이전노드 저장
	}
	h->first = q; //원래 리스트의 헤드를 뒤집힌 리스트로 바꿔줌

	return 0;
}

/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = NULL;
	node->rlink = NULL;

	listNode* tmp = h->first;
	listNode* prev = NULL;

	if (h->first == NULL) {
		insertFirst(h, key); //리스트가 비어있으면 제일 처음에 삽입
		return 0;
	}
	// key보다 큰 값이 나오는 노드가 나올 때까지 list탐색
	while (tmp != NULL && tmp->key <= key) {
		prev = tmp; // while을 벗어나면 prev가 가리키는 노드가 key보다 큰 값이 나오는 노드 바로 이전노드
		tmp = tmp->rlink; // while을 벗어나면 tmp가 가리키는 노드가 key보다 큰 값이 나오는 첫 번째 노드
	}
	if (prev== NULL) { //제일 첫 노드가 key보다 큰 값인 노드였으면 제일 앞에 삽입
		insertFirst(h, key);
	}
	else if (tmp == NULL) { //key보다 큰 값을 갖는 노드가 없으면 가장 뒤에 삽입
		insertLast(h, key);
	}
	else { 
		node->rlink = tmp; 
		node->llink = tmp->llink; //key보다 큰값 바로 이전노드는 key를 담은 노드를 가리킴
		tmp->llink->rlink = node; //key보다 큰값이 왼쪽으로 가리킨 노드가 오른쪽으로 가리키는 노드가 node를 가리킴
	}
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	listNode* tmp = h->first;
	listNode* prev = NULL;

	if (h->first == NULL) {
		printf("nothing to delete\n");
		return 0;
	}
	//key와 같은 값을 갖는 노드를 찾는다.
	while (tmp != NULL && tmp->key != key) {
		prev = tmp; // while을 벗어나면 prev가 가리키는 노드가 key와 같은값인 노드 바로 이전 노드
		tmp = tmp->rlink; // while을 벗어나면 tmp가 가리키는 노드가 key와 같은 값인 노드
	}
	if (prev == NULL) { // key와 같은 값을 갖는 노드가 첫 번째 노드
		deleteFirst(h);
	}
	else if (tmp == NULL) { // key와 같은 값이 없음. 그냥 리턴
		return 0;
	}
	else if (tmp->rlink == NULL) { //key와 같은 값이 마지막 노드
		deleteLast(h);
	}
	else { // key와 같은 값을 갖는 노드가 중간인 경우
		tmp->llink->rlink = tmp->rlink; 
		tmp->rlink->llink = tmp->llink;
		free(tmp); // 메모리 해제
	}
	return 1;
}