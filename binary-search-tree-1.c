/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int key;
	struct Node* left;
	struct Node* right;
} Node;

int initializeBST(Node** h);


/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */



int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	printf("소프트웨어학과 2019038065 홍예림");
	do {
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
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
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
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
	(*h)->left = *h;
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}

void inorderTraversal(Node* ptr)
{
	if (ptr) {
		inorderTraversal(ptr->left);
		printf("[%d] ", ptr->key);
		inorderTraversal(ptr->right);
	}
}

void preorderTraversal(Node* ptr)
{
	if (ptr) {
		printf("[%d] ", ptr->key);
		preorderTraversal(ptr->left);
		preorderTraversal(ptr->right);
	}
}

void postorderTraversal(Node* ptr)
{
	if (ptr) {
		postorderTraversal(ptr->left);
		postorderTraversal(ptr->right);
		printf("[%d] ", ptr->key);
	}
}

int insert(Node* head, int key)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	
	if (head->left == head) //트리가 비어있다면
	{
		head->left = node; //헤드노드 왼쪽에 새 노드 삽입
		return 1;
	}
	Node* p = NULL;
	Node* tmp = head->left;
	while (tmp != NULL) { 
		p = tmp;

		if (p->key > key) { //입력한 key보다 크면 왼쪽 노드로 이동
			tmp = p->left;
		}
		else { //입력한 key보다 작으면 오른쪽 노드로 이동
			tmp = p->right;
		}
		if (p->key == key) { //입력한 key와 동일한 숫자라면
			printf("이미 존재하는 key입니다.\n"); //에러메세지 출력
			return 0;
		}
	}

	if (head->left != head) { //트리가 비어 있지 않으면
		if (p->key > key) { //입력한 key가 더 작으면
			p->left = node; //왼쪽 삽입
		}
		else { //입력한 key가 더 크면
			p->right = node; //오른쪽 삽입
		}
	}
	return 0;
}

int deleteLeafNode(Node* head, int key)
{
	Node* parent, * tmp;

	parent = NULL; // tmp의 부모노드
	tmp = head->left;

	// key를 갖는 노드 t를 탐색한다
	while (tmp != NULL && tmp->key != key)
	{
		parent = tmp; 
		if (key < parent->key) // 입력한 key가 더 작으면 왼쪽으로 이동
			tmp = parent->left;
		else //입력한 key가 더 크면 오른쪽으로 이동
			tmp= parent->right;
	}

	// 탐색 후 만약 키 값이 트리에 없었다면 tmp는 NULL
	if (tmp==NULL)
	{	printf("key is not in the tree");
		return; 
	}
	// 탐색 성공
	if (tmp->left == NULL && tmp->right == NULL) //단말노드였을 경우
	{
		if (parent!=NULL) // 부모 노드가 NULL이 아닐 때
		{
			if (parent->left == tmp)
				parent->left = NULL;
			else
				parent->right = NULL;
		}
		else // 부모 노드가 NULL 이라면, 삭제하려는 노드가 루트 노드다.
			head = NULL;
	}
	else // 그 외의 경우 삭제하지 않음
	{
		printf("the  node [%d] is not a leaf",key);
		return 0;
	}
	free(tmp);
}

Node* searchRecursive(Node* head, int key) //순환
{
	if (head==NULL) 
		return NULL;
	
	if (key == head->key) 
		return head;
	
	else if (key < head->key) 
		 searchRecursive(head->left, key);
	
	else
		 searchRecursive(head->right, key);

}


Node* searchIterative(Node* head, int key) //반복
{
	Node* tmp = head->left;
	while (tmp != NULL)
	{
		if (key == tmp->key)
			return tmp;
		else if (key < tmp->key)
			 tmp = tmp->left;
		else
			 tmp = tmp->right;
	}
	return NULL;
}

int freeBST(Node* head) //후위 순위로 해제
{
	if (head == NULL)
		return 1;
	else
	{
		freeBST(head->left);
		freeBST(head->right);
		free(head);
	}
}