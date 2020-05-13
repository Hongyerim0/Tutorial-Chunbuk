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
 /* �ʿ��� ������� �߰� */

typedef struct Node {
    int key;
    struct Node* llink;
    struct Node* rlink;
} listNode;

/* �Լ� ����Ʈ */
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

    printf("\n����Ʈ�����а� 2019038065 ȫ����\n\n");
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

    /* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
    if (*h != NULL)
        freeList(*h);

    /* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
    *h = (listNode*)malloc(sizeof(listNode));
    (*h)->rlink = *h;
    (*h)->llink = *h;
    (*h)->key = -9999;
    return 1;
}

/* �޸� ���� */
int freeList(listNode* h) {
  //h�� ����� listnode �޸� ����
 //headnode�� �����Ǿ����
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
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(listNode* h, int key) {
    listNode* node = (listNode*)malloc(sizeof(listNode));
    node->rlink = NULL;
    node->llink = NULL;
    node->key = key;

    if (h->rlink == h) { // List�� ��������� ���� ó���� ����
        h->rlink = node; 
        h->llink = node;
        node->rlink = h;
        node->llink = h;
    }
    else { // �� �� �������� �����ؼ� h�� ����
       
        h->llink->rlink = node;
        node->llink = h->llink;
        h->llink = node;
        node->rlink = h;
    }
    return 1;
}

/**
 * list�� ������ ��� ����
 */
int deleteLast(listNode* h) {
    listNode* tmp = h->llink;

    if (h->rlink == h) { 
        printf("nothing to delete\n");
        return 1;
    }
    tmp->llink->rlink = h; //tmp�� ���� ��尡 h�� ����Ű���� �ϰ�
    h->llink = tmp->llink; //h�� tmp�� ���� ��带 ����ī��� �Ͽ� tmp ����

    free(tmp); //�޸� ����

    return 1;
}
/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(listNode* h, int key) {
    listNode* node = (listNode*)malloc(sizeof(listNode));
    node->key = key;
    node->rlink = NULL;
    node->llink = NULL;
    // h ������ �����ؼ� h�� h ���� ���� ����
    node->rlink = h->rlink;  
    h->rlink->llink = node; 
    node->llink = h; 
    h->rlink = node;  

    return 1;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(listNode* h) {
    if (h->rlink==h) {
        printf("nothing to delete\n");
        return 0;
    }
    listNode* tmp = h->rlink; 
    tmp->rlink->llink = h; //tmp�� ������ ��尡 h�� ����Ű���� �ϰ�
    h->rlink = tmp->rlink; //h�� ������ ��尡 tmp�� ���� ���� ����Ű���� �Ͽ� tmp ����

    free(tmp); // �޸� ����

    return 1;
}

/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(listNode* h) {

    listNode* p = h->rlink;
    listNode* q = h; //������ ����Ʈ�� ù ��° ��带 ����ų ������
    listNode* r =h; //������ ����Ʈ�� �̾�� �ӽ� ������

    h->rlink = h->llink;

    while (p != h) {
        r = q; //������ ����Ʈ�� �ӽ� ����
        q = p; //�� �������� �̾���� �ϴ� ��带 �޾ƿ�
        p = p->rlink; //p�� ���� ��� ����
        q->rlink = r; //r�� q�� ���� ��� ����
        q->llink = p; //p�� q�� ������� ����
    }
    h->rlink = q; //���� ����Ʈ�� ��带 ������ ����Ʈ�� �ٲ���

    return 0;
}

/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(listNode* h, int key) {
    listNode* node = (listNode*)malloc(sizeof(listNode));
    node->key = key;
    node->llink = NULL;
    node->rlink = NULL;

    if (h->rlink == h) { //����Ʈ�� ������� ó���� ����
        insertFirst(h, key);
        return 1;
    }

    listNode* tmp = h->rlink;

    // key���� ū ���� ������ ��尡 ���� ������ listŽ��
    while (tmp != NULL && tmp != h && tmp->key <= key) {
        tmp = tmp->rlink; // while�� ����� tmp�� ����Ű�� ��尡 key���� ū ���� ������ ù ��° ���
    }
    if (tmp == h->rlink) {  //���� ù ��尡 key���� ū ���� ��忴���� ���� �տ� ����
        insertFirst(h, key);
    }
    else { 
        node->rlink = tmp;
        node->llink = tmp->llink; //key���� ū�� �ٷ� �������� key�� ���� ��带 ����Ŵ
        tmp->llink->rlink = node; //key���� ū���� �������� ����Ų ��尡 ���������� ����Ű�� ��尡 node�� ����Ŵ
    }
    return 0;
    insertLast(h, key); //���������� key���� ū �� ������ �������� ����
    return 0;
}



/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(listNode* h, int key) {
    if (h->rlink == h) {
        printf("nothing to delete.\n");
        return 1;
    }
    listNode* tmp = h->rlink;
    while (tmp != NULL && tmp->key != key) {
        tmp = tmp->rlink; // while�� ����� tmp�� ����Ű�� ��尡 key�� ���� ���� ���
    }
    if (tmp == h->rlink) { // key�� ���� ���� ���� ��尡 ù ��° ���
        deleteFirst(h);
    }
    else if (tmp->rlink == h) { //key�� ���� ���� ������ ���
        deleteLast(h);
    }
    else { // key�� ���� ���� ���� ��尡 �߰��� ���
        tmp->llink->rlink = tmp->rlink;
        tmp->rlink->llink = tmp->llink;
        free(tmp); // �޸� ����
    }
    return 0;

    printf("cannot find the node for key = %d\n", key); //key�� ���� ��� �����޼��� ���
    return 0;
}
