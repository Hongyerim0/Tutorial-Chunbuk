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

	printf("����Ʈ�����а� 2019038065 ȫ����");
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
	
	if (head->left == head) //Ʈ���� ����ִٸ�
	{
		head->left = node; //����� ���ʿ� �� ��� ����
		return 1;
	}
	Node* p = NULL;
	Node* tmp = head->left;
	while (tmp != NULL) { 
		p = tmp;

		if (p->key > key) { //�Է��� key���� ũ�� ���� ���� �̵�
			tmp = p->left;
		}
		else { //�Է��� key���� ������ ������ ���� �̵�
			tmp = p->right;
		}
		if (p->key == key) { //�Է��� key�� ������ ���ڶ��
			printf("�̹� �����ϴ� key�Դϴ�.\n"); //�����޼��� ���
			return 0;
		}
	}

	if (head->left != head) { //Ʈ���� ��� ���� ������
		if (p->key > key) { //�Է��� key�� �� ������
			p->left = node; //���� ����
		}
		else { //�Է��� key�� �� ũ��
			p->right = node; //������ ����
		}
	}
	return 0;
}

int deleteLeafNode(Node* head, int key)
{
	Node* parent, * tmp;

	parent = NULL; // tmp�� �θ���
	tmp = head->left;

	// key�� ���� ��� t�� Ž���Ѵ�
	while (tmp != NULL && tmp->key != key)
	{
		parent = tmp; 
		if (key < parent->key) // �Է��� key�� �� ������ �������� �̵�
			tmp = parent->left;
		else //�Է��� key�� �� ũ�� ���������� �̵�
			tmp= parent->right;
	}

	// Ž�� �� ���� Ű ���� Ʈ���� �����ٸ� tmp�� NULL
	if (tmp==NULL)
	{	printf("key is not in the tree");
		return; 
	}
	// Ž�� ����
	if (tmp->left == NULL && tmp->right == NULL) //�ܸ���忴�� ���
	{
		if (parent!=NULL) // �θ� ��尡 NULL�� �ƴ� ��
		{
			if (parent->left == tmp)
				parent->left = NULL;
			else
				parent->right = NULL;
		}
		else // �θ� ��尡 NULL �̶��, �����Ϸ��� ��尡 ��Ʈ ����.
			head = NULL;
	}
	else // �� ���� ��� �������� ����
	{
		printf("the  node [%d] is not a leaf",key);
		return 0;
	}
	free(tmp);
}

Node* searchRecursive(Node* head, int key) //��ȯ
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


Node* searchIterative(Node* head, int key) //�ݺ�
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

int freeBST(Node* head) //���� ������ ����
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