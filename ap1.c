#include <stdio.h>
#include <stdlib.h>

void main(){
    int list[5]; // 5���� ������ �����ϴ� �迭 ����
    int *plist[5]={NULL,}; // ������ ���� ������ 5�� NULL�� �ʱ�ȭ

    plist[0]=(int *)malloc(sizeof(int)); //4bytes�� �� �������� �Ҵ��ؼ� �� �޸��� �ּҸ� �Ѱ� �޾� plist[0]�� ����

    list[0]=1; //list[0]�� �� 1�� �ʱ�ȭ
    list[1]=100; //list[0]�� �� 100 ���� �ʱ�ȭ

    *plist[0]=200; //plist[0]�� ����Ű�� ���� ���� 200 ����

    printf("value of list[0]  =%d\n",list[0]); //list[0]�� �� ����Ʈ 
    printf("address of list[0]      =%p\n",&list[0]); //list[0]�� �ּ� ����Ʈ
    printf("value of list           =%p\n",list); // list[0]�� �� ����Ʈ
    printf("address of list (&list) =%p\n",&list); /* list[0]�� �ּ� ����Ʈ
                                                      �迭�� �̸��� �迭�� �����ּ��̴�*/
    printf("-----------------------------------------\n\n");
    printf("value of list[1]     =%d\n",list[1]); //list[1]�� �� ����Ʈ
    printf("address of list[1]   =%p\n",&list[1]); //lsit[1]�� �ּ� ����Ʈ
    printf("value of *(list+1)   =%d\n",*(list+1)); //list[1]�� �� ����Ʈ (*(list+1)==list[1])
    printf("address of list+1    =%p\n",list+1); // list[1]�� �ּ� ����Ʈ (list+1==&list[1])
    

    printf("------------------------------------------\n\n"); 

     printf("value of *plist[0] =%d\n",*plist[0]); // plist[0]�� ����Ű�� �ִ� ��(heap����)�� ��(==200) ����Ʈ
     printf("&plist[0]          =%p\n",&plist[0]); //plist[0]�� �ּ� ����Ʈ
     printf("&plist             =%p\n",&plist); //plist[0]�� �ּ� ����Ʈ
     printf("plist              =%p\n",plist); // plist[0]�� �ּ� ����Ʈ(�迭�� �̸��� �迭�� �����ּ��̴�.)
     printf("plist[0]           =%p\n",plist[0]); //plist[0]�� �� ����Ʈ(heap������ �ִ� malloc�� ���ؼ� ���� �ּ�)
     printf("plist[1]           =%p\n",plist[1]); //plist[1]�� �� ����Ʈ(malloc���� ������ �� plist[0]�� ������ �������� null���� ���´�.)
     printf("plist[2]           =%p\n",plist[2]); //plist[2]�� �� ����Ʈ(malloc���� ������ �� plist[0]�� ������ �������� null���� ���´�.)
     printf("plist[3]           =%p\n",plist[3]); //plist[3]�� �� ����Ʈ(malloc���� ������ �� plist[0]�� ������ �������� null���� ���´�.)
     printf("plist[4]           =%p\n",plist[4]); //plist[4]�� �� ����Ʈ(malloc���� ������ �� plist[0]�� ������ �������� null���� ���´�.)
 
     free(plist[0]); //plist[0]�� �Ҵ��� �޸� ����

     printf("\n\n----Software 2019038065 ȫ����----\n");
    }

