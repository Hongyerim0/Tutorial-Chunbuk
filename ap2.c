#include<stdio.h>
#include<stdlib.h>
void main(){
    int list[5]; //5���� ������ �����ϴ� �迭 ����
    int *plist[5]; //������ ���� ������ 5�� ����

    list[0]=10; //list[0]�� �� 10���� �ʱ�ȭ
    list[1]=11; //list[1]�� �� 11���� �ʱ�ȭ

    plist[0]=(int*)malloc(sizeof(int)); //4bytes�� �� �������� �Ҵ��ؼ� �� �޸��� �ּҸ� �Ѱ� �޾� plist[0]�� ����
    
    printf("list[0] \t=%d\n",list[0]); //list[0]�� �� ����Ʈ(������ �ʱ�ȭ ���� �� 10)
    printf("address of list \t=%p\n",list); //list�� ���� �ּ� ����Ʈ(==&list[0])
    printf("address of list[0] \t=%p\n", &list[0]); //list[0]�� �ּ� ����Ʈ
    printf("address of list+0 \t=%p\n", list+0); //list[0]�� �ּ� ����Ʈ
    printf("address of list+1 \t=%p\n", list+1); //list[1]�� �ּ� ����Ʈ,&list[0]���� 4���� (list+1 == &list[1])
    printf("address of list+2 \t=%p\n", list+2); //list[2]�� �ּ� ����Ʈ,&list[1]���� 4����(list+2 == &list[2])
    printf("address of list+3 \t=%p\n", list+3); //list[3]�� �ּ� ����Ʈ,&list[2]���� 4����(list+3 == &list[3])
    printf("address of list+4 \t=%p\n", list+4); //list[4]�� �ּ� ����Ʈ,&list[3]���� 4����(list+4 == &list[4])
    printf("address of list[4] \t=%p\n", &list[4]); //list[4]�� �ּ� ����Ʈ

    free(plist[0]); // plist[0]�� �Ҵ��� �޸� ����

    printf("\n\n----Software 2019038065 ȫ����----\n");

}