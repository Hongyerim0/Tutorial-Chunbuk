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
 /* �ʿ��� ������� �߰� if necessary */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;

/* �Լ� ����Ʈ */

/* note: initialize�� ���������͸� �Ű������� ����
		 singly-linked-list�� initialize�� �������� ���� �Ұ� */
int initialize(headNode** h);

/* note: freeList�� �̱������͸� �Ű������� ����
		- initialize�� �� �ٸ��� ���� �Ұ�
		 - ���������͸� �Ű������� �޾Ƶ� ������ �� ���� �� */
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

	printf("����Ʈ�����а� 2019038065 ȫ���� \n\n");
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
   //h�� ����� listnode �޸� ����
   //headnode�� �����Ǿ����
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
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->rlink = NULL;
	node->llink = NULL;
	node->key = key;
	if (h->first == NULL) {
		h->first = node; // List�� ��������� ���� ó���� ����
		return 0;
	}
listNode* tmp = h->first;
while (tmp->rlink != NULL) { //�� ������ ���� �̵�
	tmp = tmp->rlink;
}
tmp->rlink = node;  // �� ������ ��� ������ ����
node->llink = tmp; 

return 0;
}

/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {
	listNode* tmp = h->first;
	listNode* prev = NULL;

	if (h->first == NULL) {
		printf("nothing to delete");
		return 0;
	}
	//������ ��带 Ž��
	while (tmp->rlink != NULL) {
		prev = tmp; // while�� ����� prev�� ����Ű�� ��尡 ���������� �� ��° ���
		tmp = tmp->rlink; //while�� ����� tmp�� ����Ű�� ��尡 ������ ���
	}
	if (prev == NULL) { // ����Ʈ�� ��尡 �� �� ���̸� ù ���� ����
		deleteFirst(h);
	}
	else {
		prev->rlink = tmp->rlink; //���������� �� ��° ��尡 NULL�� ����Ű���� ��
		free(tmp); // �޸�����
	}
	return 0;
}

/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	listNode* tmp = h->first;
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;

	if (h->first == NULL) { //List�� ������� ó���� ����
		h->first = node;
		return 0;
	}
	node->rlink = h->first; //head�� ����Ű�� ��尡 node�� ���������� ����Ű�� ���
	node->llink = NULL; //node�� listó���̱� ������ ������ NULL

	h->first = node; //��尡 ù��° ����
	return 0;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {
	if (h->first == NULL) {
		printf("nothing to delete");
		return 0;
	}
	listNode* tmp = h->first;
	h->first = tmp->rlink; //head�� ����Ű�� ����� ���� ��带 head�� ����Ű�� ���� ����

	free(tmp); // �޸� ����

	return 0;
}

/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {
	listNode* p = h->first;
	listNode* q = NULL; //������ ����Ʈ�� ù ��° ��带 ����ų ������
	listNode* r = NULL; //������ ����Ʈ�� �̾�� �ӽ� ������

	while (p != NULL) {
		r = q; //������ ����Ʈ�� �ӽ� ����
		q = p; //�� �������� �̾���� �ϴ� ��带 �޾ƿ�
		p = p->rlink; //p�� ���� ��� ����
		q->rlink = r; //r�� q�� ���� ��� ����
		q->llink = p; //p�� q�� ������� ����
	}
	h->first = q; //���� ����Ʈ�� ��带 ������ ����Ʈ�� �ٲ���

	return 0;
}

/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = NULL;
	node->rlink = NULL;

	listNode* tmp = h->first;
	listNode* prev = NULL;

	if (h->first == NULL) {
		insertFirst(h, key); //����Ʈ�� ��������� ���� ó���� ����
		return 0;
	}
	// key���� ū ���� ������ ��尡 ���� ������ listŽ��
	while (tmp != NULL && tmp->key <= key) {
		prev = tmp; // while�� ����� prev�� ����Ű�� ��尡 key���� ū ���� ������ ��� �ٷ� �������
		tmp = tmp->rlink; // while�� ����� tmp�� ����Ű�� ��尡 key���� ū ���� ������ ù ��° ���
	}
	if (prev== NULL) { //���� ù ��尡 key���� ū ���� ��忴���� ���� �տ� ����
		insertFirst(h, key);
	}
	else if (tmp == NULL) { //key���� ū ���� ���� ��尡 ������ ���� �ڿ� ����
		insertLast(h, key);
	}
	else { 
		node->rlink = tmp; 
		node->llink = tmp->llink; //key���� ū�� �ٷ� �������� key�� ���� ��带 ����Ŵ
		tmp->llink->rlink = node; //key���� ū���� �������� ����Ų ��尡 ���������� ����Ű�� ��尡 node�� ����Ŵ
	}
	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {
	listNode* tmp = h->first;
	listNode* prev = NULL;

	if (h->first == NULL) {
		printf("nothing to delete\n");
		return 0;
	}
	//key�� ���� ���� ���� ��带 ã�´�.
	while (tmp != NULL && tmp->key != key) {
		prev = tmp; // while�� ����� prev�� ����Ű�� ��尡 key�� �������� ��� �ٷ� ���� ���
		tmp = tmp->rlink; // while�� ����� tmp�� ����Ű�� ��尡 key�� ���� ���� ���
	}
	if (prev == NULL) { // key�� ���� ���� ���� ��尡 ù ��° ���
		deleteFirst(h);
	}
	else if (tmp == NULL) { // key�� ���� ���� ����. �׳� ����
		return 0;
	}
	else if (tmp->rlink == NULL) { //key�� ���� ���� ������ ���
		deleteLast(h);
	}
	else { // key�� ���� ���� ���� ��尡 �߰��� ���
		tmp->llink->rlink = tmp->rlink; 
		tmp->rlink->llink = tmp->llink;
		free(tmp); // �޸� ����
	}
	return 1;
}