/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */

#include<stdio.h>
#include<stdlib.h>
 /* 필요한 헤더파일 추가 */

typedef struct Node {
    int key;
    struct Node* llink;
    struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
    char command;
    int key;
    listNode* headnode = NULL;

    printf("\n소프트웨어학과 2019038065 홍예림\n\n");
    do {
        printf("----------------------------------------------------------------\n");
        printf("                  Doubly Circular Linked List                   \n");
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


int initialize(listNode** h) {

    /* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
    if (*h != NULL)
        freeList(*h);

    /* headNode에 대한 메모리를 할당하여 리턴 */
    *h = (listNode*)malloc(sizeof(listNode));
    (*h)->rlink = *h;
    (*h)->llink = *h;
    (*h)->key = -9999;
    return 1;
}

/* 메모리 해제 */
int freeList(listNode* h) {
  //h와 연결된 listnode 메모리 해제
 //headnode도 해제되어야함
    if (h->rlink == h) {
        free(h);
        return 1;
    }
    listNode* p = h->rlink;
    listNode* prev = NULL;
    while (p != NULL && p !=h) {
        prev = p;
        p = p->llink;
        free(prev);
    }
    free(h);
    return 0;
}
void printList(listNode* h) {
    int i = 0;
    listNode* p;

    printf("\n---PRINT\n");

    if (h == NULL) {
        printf("Nothing to print....\n");
        return;
    }

    p = h->rlink;

    while (p != NULL && p != h) {
        printf("[ [%d]=%d ] ", i, p->key);
        p = p->rlink;
        i++;
    }
    printf("  items = %d\n", i);


    /* print addresses */
    printf("\n---checking addresses of links\n");
    printf("-------------------------------\n");
    printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

    i = 0;
    p = h->rlink;
    while (p != NULL && p != h) {
        printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
        p = p->rlink;
        i++;
    }

}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {
    listNode* node = (listNode*)malloc(sizeof(listNode));
    node->rlink = NULL;
    node->llink = NULL;
    node->key = key;

    if (h->rlink == h) { // List가 비어있으면 제일 처음에 삽입
        h->rlink = node; 
        h->llink = node;
        node->rlink = h;
        node->llink = h;
    }
    else { // 그 외 마지막에 삽입해서 h랑 연결
       
        h->llink->rlink = node;
        node->llink = h->llink;
        h->llink = node;
        node->rlink = h;
    }
    return 1;
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {
    listNode* tmp = h->llink;

    if (h->rlink == h) { 
        printf("nothing to delete\n");
        return 1;
    }
    tmp->llink->rlink = h; //tmp의 왼쪽 노드가 h를 가리키도톡 하고
    h->llink = tmp->llink; //h가 tmp의 왼쪽 노드를 가리카토록 하여 tmp 삭제

    free(tmp); //메모리 해제

    return 1;
}
/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {
    listNode* node = (listNode*)malloc(sizeof(listNode));
    node->key = key;
    node->rlink = NULL;
    node->llink = NULL;
    // h 다음에 삽입해서 h와 h 다음 노드와 연결
    node->rlink = h->rlink;  
    h->rlink->llink = node; 
    node->llink = h; 
    h->rlink = node;  

    return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {
    if (h->rlink==h) {
        printf("nothing to delete\n");
        return 0;
    }
    listNode* tmp = h->rlink; 
    tmp->rlink->llink = h; //tmp의 오른쪽 노드가 h를 가리키도록 하고
    h->rlink = tmp->rlink; //h의 오른쪽 노드가 tmp의 오른 쪽을 가리키도록 하여 tmp 삭제

    free(tmp); // 메모리 해제

    return 1;
}

/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {

    listNode* p = h->rlink;
    listNode* q = h; //뒤집힌 리스트의 첫 번째 노드를 가리킬 포인터
    listNode* r =h; //뒤집힌 리스트를 이어나갈 임시 포인터

    h->rlink = h->llink;

    while (p != h) {
        r = q; //뒤집힌 리스트를 임시 저장
        q = p; //그 다음으로 이어줘야 하는 노드를 받아옴
        p = p->rlink; //p는 다음 노드 저장
        q->rlink = r; //r에 q의 다음 노드 저장
        q->llink = p; //p에 q의 이전노드 저장
    }
    h->rlink = q; //원래 리스트의 헤드를 뒤집힌 리스트로 바꿔줌

    return 0;
}

/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {
    listNode* node = (listNode*)malloc(sizeof(listNode));
    node->key = key;
    node->llink = NULL;
    node->rlink = NULL;

    if (h->rlink == h) { //리스트가 비었으면 처음에 삽입
        insertFirst(h, key);
        return 1;
    }

    listNode* tmp = h->rlink;

    // key보다 큰 값이 나오는 노드가 나올 때까지 list탐색
    while (tmp != NULL && tmp != h && tmp->key <= key) {
        tmp = tmp->rlink; // while을 벗어나면 tmp가 가리키는 노드가 key보다 큰 값이 나오는 첫 번째 노드
    }
    if (tmp == h->rlink) {  //제일 첫 노드가 key보다 큰 값인 노드였으면 제일 앞에 삽입
        insertFirst(h, key);
    }
    else { 
        node->rlink = tmp;
        node->llink = tmp->llink; //key보다 큰값 바로 이전노드는 key를 담은 노드를 가리킴
        tmp->llink->rlink = node; //key보다 큰값이 왼쪽으로 가리킨 노드가 오른쪽으로 가리키는 노드가 node를 가리킴
    }
    return 0;
    insertLast(h, key); //마지막까지 key보다 큰 값 없으면 마지막에 삽입
    return 0;
}



/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {
    if (h->rlink == h) {
        printf("nothing to delete.\n");
        return 1;
    }
    listNode* tmp = h->rlink;
    while (tmp != NULL && tmp->key != key) {
        tmp = tmp->rlink; // while을 벗어나면 tmp가 가리키는 노드가 key와 같은 값인 노드
    }
    if (tmp == h->rlink) { // key와 같은 값을 갖는 노드가 첫 번째 노드
        deleteFirst(h);
    }
    else if (tmp->rlink == h) { //key와 같은 값이 마지막 노드
        deleteLast(h);
    }
    else { // key와 같은 값을 갖는 노드가 중간인 경우
        tmp->llink->rlink = tmp->rlink;
        tmp->rlink->llink = tmp->llink;
        free(tmp); // 메모리 해제
    }
    return 0;

    printf("cannot find the node for key = %d\n", key); //key가 없는 경우 에러메세지 출력
    return 0;
}
