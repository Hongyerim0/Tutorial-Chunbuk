#include<stdio.h>

struct student1 //typedef �����ʰ� ����ü student1 ���� 
{        
    char lastName;      
    int studentId;      
    char grade;        
};

typedef  struct // typedef �Ἥ ����ü student2 ����
{ 
    char lastName;
    int studentId;
    char grade;
}student2;

int main()
{
    struct student1 st1 = {'A', 100, 'A'}; /*typedef�� ���� �ʾұ� ������ struct ����ü Ű���带 
                                             ����ؼ� student1����ü st1����,���� A, 100, A�� �ʱ�ȭ*/          

    printf("st1.lastName    = %c\n"  , st1.lastName); //����ü st1 ���� lastname ����Ʈ
    printf("st1.studentId  = %d\n", st1.studentId ); //����ü st1 ���� studentId ����Ʈ
    printf("st1.grade      =%c\n",st1.grade); //����ü st1 ���� grade ����Ʈ

    student2 st2 = {'B', 200, 'B'}; /*typedef�� ��� ������ struct ����ü Ű���带 ������� �ʰ� 
                                       student2����ü st2����, ���� A, 100, A�� �ʱ�ȭ */

    printf("\nst2.lastName = %c\n", st2.lastName); //����ü st2 ���� lastname ����Ʈ
    printf("st2.studentId  = %d\n", st2.studentId); //����ü st2 ���� studentId ����Ʈ
    printf("st2.grade      = %c\n",st2.grade); //����ü st2 ���� grade ����Ʈ

    student2 st3; //typedef�� ��� ������ struct ����ü Ű���带 ������� �ʰ�  student2����ü st3 ����

    st3=st2; //st2�� st3�� ����

    printf("\nst3.lastName = %c\n", st3.lastName); //����ü st3 ���� lastname ����Ʈ(==st2.lastname)
    printf("st3.studentId  = %d\n",st3.studentId); //����ü st3 ���� studentId ����Ʈ(==st2.studentId)
    printf("st3.grade = %c\n",st3.grade); //����ü st3 ���� grade ����Ʈ(==st2.grade)

    printf("\n\n----Software 2019038065 ȫ����----\n");

    /* equality test */

    /*if(st3==st2)  (���� �� ����. ���� �� ����)
        printf("equal\n");
    else 
        printf("not equal\n");

    return 0;*/
}
