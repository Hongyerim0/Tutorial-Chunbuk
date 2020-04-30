/*
 * singly linked list
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 */

#include<stdio.h>
#include<stdlib.h>

 //�ʿ��� ������� �߰� 
typedef struct Node {
    int key;
    struct Node* link;
} listNode;

typedef struct Head {
    struct Node* first;
}headNode;


//�Լ� ����Ʈ
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
    char command;
    int key;
    headNode* headnode = NULL;

    printf("����Ʈ�����а� 2019038065 ȫ����\n\n");

    do {
        printf("----------------------------------------------------------------\n");
        printf("                     Singly Linked List                         \n");
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
            headnode = initialize(headnode);
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

headNode* initialize(headNode* h) {

    //headnode�� null�� �ƴϸ� freenode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ����
    if (h != NULL)
        freeList(h);

    //headnode�� ���� �޸𸮸� �Ҵ��Ͽ� ����
    headNode* temp = (headNode*)malloc(sizeof(headNode));
    temp->first = NULL;
    return temp;
}

int freeList(headNode* h) {
    //h�� ����� listnode �޸� ����
    //headnode�� �����Ǿ����
    listNode* p = h->first;

    listNode* prev = NULL;
    while (p != NULL) {
        prev = p;
        p = p->link;
        free(prev);
    }
    free(h);
    return 0;
}

int insertFirst(headNode* h, int key) {
    //listó���� key�� ���� ��� �ϳ��� �߰�
    listNode* node = (listNode*)malloc(sizeof(listNode));
    node->key = key;

    node->link = h->first;
    h->first = node;

    return 0;
}


//����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ����
int insertNode(headNode* h, int key) {
    listNode* node = (listNode*)malloc(sizeof(listNode));
    listNode* tmp = h->first;
    listNode* prev = NULL;
    if (h->first == NULL) {
        insertFirst(h, key); // ����Ʈ�� ��������� ���� ó���� ����
        return 0;
    }

    // key���� ū ���� ������ ��尡 ���� ������ list Ž��
    while (tmp != NULL && tmp->key <= key) {
        prev = tmp; // while�� ����� prev�� ����Ű�� ��尡 key���� ū ���� ������ ��� �ٷ� �������
        tmp = tmp->link; // while�� ����� tmp�� ����Ű�� ��尡 key���� ū ���� ������ ù ��° ���
    }
    if (prev == NULL) { // ���� ù ��尡 key���� ū ���� ��忴���� ���� �տ� ����
        insertFirst(h, key);
    }
    else if (tmp == NULL) { // key���� ū ���� ���� ��尡 ������ ���� �ڿ� ����
        insertLast(h, key);
    }
    else {
        node->key = key;

        prev->link = node; // key���� ū�� �ٷ� �������� key�� ���� ��� ����Ŵ
        node->link = tmp; // key�� ���� ���� key���� ū�� ��� ����Ŵ
    }
    return 0;
}

//list�� �������� key�� ���� ��� �ϳ��� �߰�
int insertLast(headNode* h, int key) {
    listNode* node = (listNode*)malloc(sizeof(listNode));
    if (h->first == NULL) {
        node = key;     // ����Ʈ�� ��������� ���� ó���� ����
        return 0;
    }
    node->key = key;

    listNode* tmp = h->first;
    while (tmp->link != NULL) // �� ������ ���� �̵�
        tmp = tmp->link;

    tmp->link = node;  // �� ������ ��� ������ ����
    node->link = NULL;

    return 0;
}


//list�� ù��° ��� ����
int deleteFirst(headNode* h) {
    if (h->first == NULL) {
        printf("nothing to delete \n");
    }
    listNode* tmp = h->first;
    h->first = tmp->link; // head�� ����Ű�� ����� ���� ��带 head�� ����Ű�� ���� ����

    free(tmp); // �޸� ����

    return 0;
}


//list���� key �� ���� ��� ����
int deleteNode(headNode* h, int key) {
    listNode* node = h->first;
    listNode* prev = NULL;

    if (h->first == NULL) {
        printf("nothing to delete\n");
    }
    // key�� ���� ���� ���� ��带 ã�´�.
    while (node != NULL && node->key != key) {
        prev = node; // while�� ����� prev�� ����Ű�� ��尡 key�� �������� ��� �ٷ� ���� ���
        node = node->link; // while�� ����� tmp�� ����Ű�� ��尡 key�� ���� ���� ���
    }
    if (prev == NULL) { // key�� ���� ���� ���� ��尡 ù ��° ���
        deleteFirst(h);
    }
    else if (node == NULL) { // key�� ���� ���� ����. �׳� ����
        return 0;
    }
    else { // key�� ���� ���� ���� ��尡 ù ��° ��尡 �ƴ� ���(�߰��̳� ������)
        prev->link = node->link; // tmp ��������� ��ũ�� tmp �������� ���� 
        free(node); // �޸� ����
    }

    return 0;
}

//list�� ������ ��� ����
int deleteLast(headNode* h) {
    listNode* tmp = h->first;
    listNode* prev = NULL;

    if (h->first == NULL) {
        printf("nothing to delete");
        return 0;
    }
    // ������ ��带 Ž��
    while (tmp->link != NULL) {
        prev = tmp; // while�� ����� prev�� ����Ű�� ��尡 ���������� �� ��° ���
        tmp = tmp->link; // while�� ����� tmp�� ����Ű�� ��尡 ������ ���
    }

    if (prev == NULL) { // ����Ʈ�� ��尡 �� �� ���̸� ù ���� ����
        deleteFirst(h);
    }
    else {
        prev->link = tmp->link; // ���������� �� ��° ��尡 NULL�� ����Ű���� ��
        free(tmp); // �޸� ����
    }

    return 0;
}


//����Ʈ�� ��ũ�� �������� ���ġ
int invertList(headNode* h) {
    listNode* p = h->first;
    listNode* q = NULL; // ������ ����Ʈ�� ù ��° ��带 ����ų ������
    listNode* r = NULL; // ������ ����Ʈ�� �̾�� �ӽ� ������

    while (p != NULL) {
        r = q;  // ������ ����Ʈ�� �ӽ� ����
        q = p;  // �� �������� �̾���� �ϴ� ��带 �޾ƿ�
        p = p->link; // p�� �� ���� ��� ����
        q->link = r; // �̾�����ϴ� ����� ��ũ�� ������ ����Ʈ�� �̾���. q�� �Ǵٽ� ������ ����Ʈ�� ù ��° ��带 ����Ŵ
    }
    h->first = q; // ���� ����Ʈ�� ��带 ������ ����Ʈ�� �ٲ���

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
        p = p->link;
        i++;
    }

    printf("  items = %d\n", i);
}
