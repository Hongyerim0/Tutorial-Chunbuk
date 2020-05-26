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

	printf("소프트웨어학과 2019038065 홍예림");
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

void recursiveInorder(Node* ptr) //순환
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
void iterativeInorder(Node* node) //반복
{
	while(1) {
		for (; node; node = node->left)
			push(node); /*스택에 삽입 */
		node = pop(); /*스택에서 삭제 */

		if (!node) break; /* 공백 스택 */

		printf(" [%d] ", node->key);
		node = node->right;
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
{
	if (!ptr) /* 공백 트리 */
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
	parent = NULL; // tmp의 부모노드

	// key를 갖는 노드 tmp를 탐색한다
	while (tmp != NULL && tmp->key != key)
	{
		parent = tmp;
		if (key < parent->key) // 입력한 key가 더 작으면 왼쪽으로 이동
			tmp = parent->left;
		else //입력한 key가 더 크면 오른쪽으로 이동
			tmp = parent->right;
	}
	// 탐색 후 key가 트리에 없다면 tmp는 NULL
	if (tmp == NULL) //
	{
		printf("입력한 key는 존재하지 않습니다.");
		return;
	}
	// 탐색 성공
	if (tmp->left == NULL && tmp->right == NULL) //단말노드였을 경우
	{
		if (parent != NULL) // 부모 노드가 NULL이 아닐 때
		{
			if (parent->left == tmp)
				parent->left = NULL;
			else
				parent->right = NULL;
		}
		else // 부모 노드가 NULL 이라면, 삭제하려는 노드가 루트 노드다.
			head = NULL;
	}
	else if(tmp->left== NULL || tmp->right==NULL) { //하나의 자식을 가진 비리프 노드의 경우
		if (tmp->left != NULL) //tmp의 왼쪽에 노드가 있을 때
			child = tmp->left;
		else //tmp의 오른쪽에 노드가 있을 때
			child = tmp->right;
		if (parent !=NULL) //부모 노드가 NULL이 아닐 때
		{
			if (tmp == parent->left) 
				parent->left = child;
			else 
				parent->left = child;
		}
		else
			head->left = child;
	}
	else { //두 개의 자식을 가진 비리프 노드의 경우 (오른쪽 서브트리에서 가장 작은 원소로 대체)
		psub = tmp; 
		sub = tmp->right;
		while (sub->left != NULL) { 
			psub = sub;
			sub = sub->right;
		}
		if (psub->left == sub) { //삭제할 노드의 부모노드와 삭제할 노드의 자식과 연결
			psub->left = sub->right;
		}
		else {
			psub->right = sub->right;
		}		
		tmp->key = sub->key;
		tmp = sub;
	}
	free(tmp); //메모리 해제
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

Node* pop() //스택 삭제
{
	Node* x=NULL;
	if (top == -1)
		return '\0';
	else {
		x = stack[top--];
	}
	return x;
}

void push(Node* aNode) //스택 삽입
{	if(top< MAX_STACK_SIZE -1 && aNode!=NULL)
	stack[++top] = aNode;
}

Node* deQueue() //큐 삭제
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

void enQueue(Node* aNode) //큐 삽입
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
