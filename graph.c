#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 21 /* you can change value 20 */
typedef struct Vertex {
	int num; /* vertex number */
	struct Vertex* link; /* link to a next adjacent vertext */
} Vertex;
typedef struct VertexHead {
	Vertex* head; /* linked list of all adjacent vertices */
} VertexHead;
typedef struct Graph {
	VertexHead* vlist; /* list of all vertices: vlist[MAX_VERTEX] */
} Graph;

/*FOR SEARCH*/
#define FALSE 0
#define TRUE 1
int visited[MAX_VERTEX]; //Ž���� ���� �迭 ����
/* for queue */
Vertex* q[MAX_VERTEX];
int front = -1;
int rear = -1;
int deQueue();
void enQueue(int item);

/* for stack */
typedef struct stackNode
{
	int data;
	struct stackNode* link;
}stackNode;
stackNode* top;
int pop();
void push(int item);

void createGraph(VertexHead** h); /* empty graph creation */
int destroyGraph(VertexHead** h); /* deallocating all allocated memory */
int insertVertex(VertexHead* head, int num); /* vertex insertion */
int deleteVertex(VertexHead* head, int num); /* vertex deletion */
int insertEdge(VertexHead* head, int u, int v); /* new edge creation between two vertices */
int deleteEdge(VertexHead* head, int u, int v); /* edge removal */
void depthFS(VertexHead* g, int num); /* depth firt search using stack */
void breadthFS(VertexHead* g, int num); /* breadth first search using queue */
void printGraph(VertexHead* head); /* printing graph with vertices and edges */

int main() {
	char command;
	int num;
	int u, v;
	Graph* head = NULL;

	printf("����Ʈ�����а� 2019038065 ȫ����");
	do {
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                                Graph                                  \n");
		printf("----------------------------------------------------------------\n");
		printf(" create Graph         = z												\n");
		printf(" Depth firt search    = f       Breadth first search      = b   \n");
		printf(" Insert  Vertex       = i       Delete Vertex             = d \n");
		printf(" Insert Edge          = e       Delete Edge               = t \n");
		printf(" Print Graph          = p       Quit                      = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			createGraph(&head);
			break;
		case 'q': case 'Q':
			destroyGraph(&head);
			break;
		case 'i': case 'I':
			printf("Your Num(0~20) = ");
			scanf("%d", &num);
			insertVertex(head, num);
			break;
		case 'd': case 'D':
			printf("Your Num = ");
			scanf("%d", &num);
			deleteVertex(head, num);
			break;
		case 'f': case 'F':
			printf("Your Num = ");
			scanf("%d", &num);
			depthFS(head, num);
			break;
		case 'b': case 'B':
			printf("Your Num = ");
			scanf("%d", &num);
			breadthFS(head, num);
			break;
		case 'e': case 'E':
			printf("Your Num=");
			scanf("%d %d", &u, &v);
			insertEdge(head, u, v);
			insertEdge(head, v, u);
			break;
		case 't': case 'T':
			printf("Your Num=");
			scanf("%d %d", &u, &v);
			deleteEdge(head, u, v);
			deleteEdge(head, v, u);
			break;
		case 'p': case 'P':
			printGraph(head);
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}
void createGraph(VertexHead** h) {
	if (*h != NULL) { //NULL�� �ƴϸ�
		destroyGraph(h); //�Ҵ�� �޸𸮸� ��������
	}
	//VertexHead�� ���� �޸𸮸� �Ҵ��Ͽ� ��������
	*h = (VertexHead*)malloc(sizeof(VertexHead) * MAX_VERTEX);
	for (int i = 0; i < MAX_VERTEX; i++) { //�迭�̱� ������ �ݺ����� ���
		(*h)[i].head = NULL;
	}
	return 1;
}
int destroyGraph(VertexHead** h) {
	//�׷��� ����
	//����� ��嵵 �� ���� �Ǿ�� ��
	for (int i = 0; i < MAX_VERTEX; i++) {
		Vertex* vertex = (*h)[i].head;
		Vertex* v;
		while (vertex != NULL) {
			v = vertex;
			vertex = vertex->link;
			v->link = NULL;
			free(v);
		}
		(*h)[i].head = NULL;
	}
	free(*h);
	(*h) = NULL;
}

int insertVertex(VertexHead* h, int num) {
	Vertex* v = h[num].head;
	Vertex* tmp = NULL;
	if (num < 0 || num >= MAX_VERTEX) { //���� �Ǵ� 20���� ū ���ڸ� �Է��� ���
		printf("�����Է� ����\n"); //���� �޼��� ���
		return 1;
	}
	tmp = (Vertex*)malloc(sizeof(Vertex)); //������ ������ �޸𸮸� �����Ҵ� �޴´�.
	tmp->num = -1; //-1�� ǥ��
	tmp->link = NULL;
	if (v == NULL) { //NULL�̶��, ������ ���ٸ�
		h[num].head = tmp; //�� �ڸ��� tmp����
	}
	else //�̹� �����ϴ� ������ �Է����� ���
		printf("�̹� �����ϴ� �����Դϴ�.\n");
}
int deleteVertex(VertexHead* h, int num) {
	if (h[num].head == NULL) {
		printf("�Է��� vertex %d�� �������� �ʽ��ϴ�.\n", num);
	}
	for (int i = 0; i < MAX_VERTEX; i++) {
		//�Է��� ������ NULL�� �ƴ϶��
		//deleteEdge�Լ��� ȣ���� �����ϴ� ���� ����
		if (h[num].head != NULL) {
			deleteEdge(h, num, i);
		}
		if (h[i].head != NULL)
			deleteEdge(h, i, num);
	}
	h[num].head = NULL;
}

int insertEdge(VertexHead* h, int u, int v) {
	Vertex* tmp = h[u].head;
	Vertex* node = (Vertex*)malloc(sizeof(Vertex));
	node->num = v;
	node->link = NULL;
	int a = 0;

	if (!tmp) { //�Է��� vertex�� �������� �ʴ´ٸ�
		printf("�Է��� vertex %d�� �������� �ʽ��ϴ�.\n", u);
		return 1;
	}
	if (tmp->num == -1) { //����� ��尡 ���°��
		h[u].head = node; //head�� ���� ����
		return 1;
	}
	else { //����� ��尡 ������
		while (tmp->link != NULL) {
			if (tmp->num == v) { //�̹� ����� �������� �� �Է��Ѵٸ� ���� X
				break;
			}
			tmp = tmp->link; //������ ���� �̵��ؼ�
		}
	}
	if (tmp->num != v)
		tmp->link = node; //�� �ڿ�����
}
int deleteEdge(VertexHead* h, int u, int v) {
	if (h[u].head == NULL) {
		printf("�Է��� vertex %d�� �������� �ʽ��ϴ�.\n", u);
		return 0;
	}
	Vertex* node = h[u].head;
	Vertex* prev = NULL;
	// v�� ���� ���� ���� ��带 ã�´�.
	while (node != NULL && node->num != v) {
		prev = node; // while�� ����� prev�� ����Ű�� ��尡 v�� �������� ��� �ٷ� ���� ���
		node = node->link; // while�� ����� node�� ����Ű�� ��尡 v�� ���� ���� ���
	}
	if (prev == NULL) { //v�� ���� ���� ���� ��尡 ù ��° ���
		h[u].head = node->link;
	}
	else if (node == NULL) { // v�� ���� ���� ����. �׳� ����
		return 0;
	}
	else { // v�� ���� ���� ���� ��尡 ù ��° ��尡 �ƴ� ���(�߰��̳� ������)
		prev->link = node->link;  // node�� ��������� ��ũ�� prev �������� ���� 
	}
	free(node); //�޸�����
}
void depthFS(VertexHead* g, int num) {
	if (g[num].head == NULL) {
		printf("�Է��� vertex %d�� �������� �ʽ��ϴ�.\n", num);
		return 0;
	}
	Vertex* V;
	top = NULL; //���� top ����
	push(num); //���� ���� ���ÿ� ����
	printf("%2d", num); //ó�� ���޵� ��� ���
	visited[num] = TRUE; //��µ� ��� �湮���� ǥ��
	while (top != NULL) {
		V = g[num].head; //������ ������ �ƴѵ��� Ž�� �ݺ�
		while (V) {
			if (!visited[V->num]) { //�湮�� �ȵǾ��ٸ�
				push(V->num); //�ش� ���� ���ÿ� ����
				visited[V->num] = TRUE; //�湮���� ǥ��
				printf("%2d", V->num); //���� ���
				num = V->num;
				V = g[num].head;
			}
			else
				V = V->link; //���� ���� w�� �̹� �湮�� ������ ���
		}
		num = pop(); //�� �̻� ��ȸ�� ������ ���� ��� pop
	}
    //Ž�� ����
	for (int i = 0; i < MAX_VERTEX; i++) { //�湮ǥ�� �ʱ�ȭ
		visited[i] = FALSE;
	}
}
void breadthFS(VertexHead* g, int num) {
	if (g[num].head == NULL) {
		printf("�Է��� vertex %d�� �������� �ʽ��ϴ�.\n", num);
		return 0;
	}
	Vertex* V;
	printf("%2d", num); //ó�� ���޵� ��� ���
	visited[num] = TRUE; //��µ� ��� �湮���� ǥ��
	enQueue(num); //�������� ť�� ����
	while (front != rear) {
		num = deQueue();
		for (V = g[num].head; V; V = V->link) {
			if (!visited[V->num]) { //�湮�� �ȵǾ��ٸ�
				printf("%2d", V->num); //�������
				enQueue(V->num); //�ش� ���� ť�� ����
				visited[V->num] = TRUE; //�湮���� ǥ��
			}
		}
	}
    //Ž�� ����
	for (int i = 0; i < MAX_VERTEX; i++) { //�湮ǥ�� �ʱ�ȭ
		visited[i] = FALSE;
	}
}

void printGraph(VertexHead* h) {
	printf("\n--PRINT\n");
	for (int i = 0; i < MAX_VERTEX; i++) {
		Vertex* tmp = h[i].head;
		if (tmp != NULL) { //tmp�� NULL�� �ƴѰ�츸 ����Ʈ
			printf("\n%d�� ��������Ʈ:", i);
		}
		while (tmp != NULL) {
			if (tmp->num != -1) {//tmp�� num�� -1�� �ƴҰ�� ����Ʈ
				printf("%d -> ", tmp->num);
			}
			tmp = tmp->link; //�������� �̵�
		}
	}
	return 0;
}

void push(int item) { //���û���
	stackNode* temp = (stackNode*)malloc(sizeof(stackNode));
	temp->data = item;
	temp->link = top;
	top = temp;
}
int  pop() { //���� ����
	int item;
	stackNode* temp = top;
	if (top == NULL) {
		printf("\n\n Stack is empty !\n");
		return 0;
	}
	else {
		item = temp->data;
		top = temp->link;
		free(temp);
		return item;
	}
}
void enQueue(int item) { //ť ����
	q[++rear] = item;
}
int deQueue() { //ť ����
	return q[++front];
}
