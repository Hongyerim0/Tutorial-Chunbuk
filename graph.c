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
int visited[MAX_VERTEX]; //탐색을 위한 배열 선언
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

	printf("소프트웨어학과 2019038065 홍예림");
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
	if (*h != NULL) { //NULL이 아니면
		destroyGraph(h); //할당된 메모리를 해제해줌
	}
	//VertexHead에 대한 메모리를 할당하여 리턴해줌
	*h = (VertexHead*)malloc(sizeof(VertexHead) * MAX_VERTEX);
	for (int i = 0; i < MAX_VERTEX; i++) { //배열이기 때문에 반복문을 사용
		(*h)[i].head = NULL;
	}
	return 1;
}
int destroyGraph(VertexHead** h) {
	//그래프 해제
	//연결된 노드도 다 해제 되어야 함
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
	if (num < 0 || num >= MAX_VERTEX) { //음수 또는 20보다 큰 숫자를 입력한 경우
		printf("정점입력 오류\n"); //에러 메세지 출력
		return 1;
	}
	tmp = (Vertex*)malloc(sizeof(Vertex)); //삽입할 정점의 메모리를 동적할당 받는다.
	tmp->num = -1; //-1로 표시
	tmp->link = NULL;
	if (v == NULL) { //NULL이라면, 정점이 없다면
		h[num].head = tmp; //그 자리에 tmp삽입
	}
	else //이미 존재하는 정점을 입력했을 경우
		printf("이미 존재하는 정점입니다.\n");
}
int deleteVertex(VertexHead* h, int num) {
	if (h[num].head == NULL) {
		printf("입력한 vertex %d는 존재하지 않습니다.\n", num);
	}
	for (int i = 0; i < MAX_VERTEX; i++) {
		//입력한 정점이 NULL이 아니라면
		//deleteEdge함수를 호출해 존재하는 간선 삭제
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

	if (!tmp) { //입력한 vertex가 존재하지 않는다면
		printf("입력한 vertex %d는 존재하지 않습니다.\n", u);
		return 1;
	}
	if (tmp->num == -1) { //연결된 노드가 없는경우
		h[u].head = node; //head에 직접 연결
		return 1;
	}
	else { //연결된 노드가 있으면
		while (tmp->link != NULL) {
			if (tmp->num == v) { //이미 연결된 정점들을 또 입력한다면 연결 X
				break;
			}
			tmp = tmp->link; //마지막 노드로 이동해서
		}
	}
	if (tmp->num != v)
		tmp->link = node; //그 뒤에연결
}
int deleteEdge(VertexHead* h, int u, int v) {
	if (h[u].head == NULL) {
		printf("입력한 vertex %d는 존재하지 않습니다.\n", u);
		return 0;
	}
	Vertex* node = h[u].head;
	Vertex* prev = NULL;
	// v와 같은 값을 갖는 노드를 찾는다.
	while (node != NULL && node->num != v) {
		prev = node; // while을 벗어나면 prev가 가리키는 노드가 v와 같은값인 노드 바로 이전 노드
		node = node->link; // while을 벗어나면 node가 가리키는 노드가 v와 같은 값인 노드
	}
	if (prev == NULL) { //v와 같은 값을 갖는 노드가 첫 번째 노드
		h[u].head = node->link;
	}
	else if (node == NULL) { // v와 같은 값이 없음. 그냥 리턴
		return 0;
	}
	else { // v와 같은 값을 갖는 노드가 첫 번째 노드가 아닌 경우(중간이나 마지막)
		prev->link = node->link;  // node의 이전노드의 링크를 prev 다음노드로 연결 
	}
	free(node); //메모리해제
}
void depthFS(VertexHead* g, int num) {
	if (g[num].head == NULL) {
		printf("입력한 vertex %d는 존재하지 않습니다.\n", num);
		return 0;
	}
	Vertex* V;
	top = NULL; //스택 top 설정
	push(num); //시작 정점 스택에 저장
	printf("%2d", num); //처음 전달된 노드 출력
	visited[num] = TRUE; //출력된 노드 방문으로 표시
	while (top != NULL) {
		V = g[num].head; //스택이 공백이 아닌동안 탐색 반복
		while (V) {
			if (!visited[V->num]) { //방문이 안되었다면
				push(V->num); //해당 정점 스택에 삽입
				visited[V->num] = TRUE; //방문으로 표시
				printf("%2d", V->num); //정점 출력
				num = V->num;
				V = g[num].head;
			}
			else
				V = V->link; //현재 정점 w가 이미 방문한 정점인 경우
		}
		num = pop(); //더 이상 순회할 정점이 없는 경우 pop
	}
    //탐색 종료
	for (int i = 0; i < MAX_VERTEX; i++) { //방문표시 초기화
		visited[i] = FALSE;
	}
}
void breadthFS(VertexHead* g, int num) {
	if (g[num].head == NULL) {
		printf("입력한 vertex %d는 존재하지 않습니다.\n", num);
		return 0;
	}
	Vertex* V;
	printf("%2d", num); //처음 전달된 노드 출력
	visited[num] = TRUE; //출력된 노드 방문으로 표시
	enQueue(num); //시작정점 큐에 저장
	while (front != rear) {
		num = deQueue();
		for (V = g[num].head; V; V = V->link) {
			if (!visited[V->num]) { //방문이 안되었다면
				printf("%2d", V->num); //정점출력
				enQueue(V->num); //해당 정점 큐에 삽입
				visited[V->num] = TRUE; //방문으로 표시
			}
		}
	}
    //탐색 종료
	for (int i = 0; i < MAX_VERTEX; i++) { //방문표시 초기화
		visited[i] = FALSE;
	}
}

void printGraph(VertexHead* h) {
	printf("\n--PRINT\n");
	for (int i = 0; i < MAX_VERTEX; i++) {
		Vertex* tmp = h[i].head;
		if (tmp != NULL) { //tmp가 NULL이 아닌경우만 프린트
			printf("\n%d의 인접리스트:", i);
		}
		while (tmp != NULL) {
			if (tmp->num != -1) {//tmp의 num이 -1이 아닐경우 프린트
				printf("%d -> ", tmp->num);
			}
			tmp = tmp->link; //다음노드로 이동
		}
	}
	return 0;
}

void push(int item) { //스택삽입
	stackNode* temp = (stackNode*)malloc(sizeof(stackNode));
	temp->data = item;
	temp->link = top;
	top = temp;
}
int  pop() { //스택 삭제
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
void enQueue(int item) { //큐 삽입
	q[++rear] = item;
}
int deQueue() { //큐 삭제
	return q[++front];
}
