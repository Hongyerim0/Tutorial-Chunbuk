/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>



typedef struct node {
	int key;
	struct node* left;
	struct node* right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */



int main()
{
	char command;
	int key;
	Node* head = NULL;

	printf("����Ʈ�����а� 2019038065 ȫ����");
	do {
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if (*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}

void recursiveInorder(Node* ptr) //��ȯ
{
	if (ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node) //�ݺ�
{
	while(1) {
		for (; node; node = node->left)
			push(node); /*���ÿ� ���� */
		node = pop(); /*���ÿ��� ���� */

		if (!node) break; /* ���� ���� */

		printf(" [%d] ", node->key);
		node = node->right;
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
{
	if (!ptr) /* ���� Ʈ�� */
		return;
	enQueue(ptr);
	while(1) {
		ptr = deQueue();
		if (ptr) {
			printf(" [%d]  ", ptr->key);
			if (ptr->left)
				enQueue(ptr->left);
			if (ptr->right)
				enQueue(ptr->right);
		}
		else break;
	}
}

int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while (ptr != NULL) {

		/* if there is a node for the key, then just return */
		if (ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if (ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if (parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}

int deleteNode(Node* head, int key)
{
	Node* tmp, * parent, * child, * sub, * psub;

	tmp = head->left;
	parent = NULL; // tmp�� �θ���

	// key�� ���� ��� tmp�� Ž���Ѵ�
	while (tmp != NULL && tmp->key != key)
	{
		parent = tmp;
		if (key < parent->key) // �Է��� key�� �� ������ �������� �̵�
			tmp = parent->left;
		else //�Է��� key�� �� ũ�� ���������� �̵�
			tmp = parent->right;
	}
	// Ž�� �� key�� Ʈ���� ���ٸ� tmp�� NULL
	if (tmp == NULL) //
	{
		printf("�Է��� key�� �������� �ʽ��ϴ�.");
		return;
	}
	// Ž�� ����
	if (tmp->left == NULL && tmp->right == NULL) //�ܸ���忴�� ���
	{
		if (parent != NULL) // �θ� ��尡 NULL�� �ƴ� ��
		{
			if (parent->left == tmp)
				parent->left = NULL;
			else
				parent->right = NULL;
		}
		else // �θ� ��尡 NULL �̶��, �����Ϸ��� ��尡 ��Ʈ ����.
			head = NULL;
	}
	else if(tmp->left== NULL || tmp->right==NULL) { //�ϳ��� �ڽ��� ���� ���� ����� ���
		if (tmp->left != NULL) //tmp�� ���ʿ� ��尡 ���� ��
			child = tmp->left;
		else //tmp�� �����ʿ� ��尡 ���� ��
			child = tmp->right;
		if (parent !=NULL) //�θ� ��尡 NULL�� �ƴ� ��
		{
			if (tmp == parent->left) 
				parent->left = child;
			else 
				parent->left = child;
		}
		else
			head->left = child;
	}
	else { //�� ���� �ڽ��� ���� ���� ����� ��� (������ ����Ʈ������ ���� ���� ���ҷ� ��ü)
		psub = tmp; 
		sub = tmp->right;
		while (sub->left != NULL) { 
			psub = sub;
			sub = sub->right;
		}
		if (psub->left == sub) { //������ ����� �θ���� ������ ����� �ڽİ� ����
			psub->left = sub->right;
		}
		else {
			psub->right = sub->right;
		}		
		tmp->key = sub->key;
		tmp = sub;
	}
	free(tmp); //�޸� ����
}

void freeNode(Node* ptr)
{
	if (ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if (head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}

Node* pop() //���� ����
{
	Node* x=NULL;
	if (top == -1)
		return '\0';
	else {
		x = stack[top--];
	}
	return x;
}

void push(Node* aNode) //���� ����
{	if(top< MAX_STACK_SIZE -1 && aNode!=NULL)
	stack[++top] = aNode;
}

Node* deQueue() //ť ����
{
	Node* node = NULL;

	if (front == rear) {
		if (front != -1) {
			node = queue[front];
			front = rear = -1;
		}
		return node;
	}
	node = queue[front];
	front++;
	return node;
}

void enQueue(Node* aNode) //ť ����
{
	if (rear == MAX_QUEUE_SIZE - 1) {
		return;
	}
	if (front == -1) {
		front++;
	}
	rear++;
	queue[rear] = aNode;
}
