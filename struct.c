#include<stdio.h>

struct student1 //typedef 쓰지않고 구조체 student1 생성 
{        
    char lastName;      
    int studentId;      
    char grade;        
};

typedef  struct // typedef 써서 구조체 student2 생성
{ 
    char lastName;
    int studentId;
    char grade;
}student2;

int main()
{
    struct student1 st1 = {'A', 100, 'A'}; /*typedef을 쓰지 않았기 때문에 struct 구조체 키워드를 
                                             사용해서 student1구조체 st1선언,각각 A, 100, A로 초기화*/          

    printf("st1.lastName    = %c\n"  , st1.lastName); //구조체 st1 안의 lastname 프린트
    printf("st1.studentId  = %d\n", st1.studentId ); //구조체 st1 안의 studentId 프린트
    printf("st1.grade      =%c\n",st1.grade); //구조체 st1 안의 grade 프린트

    student2 st2 = {'B', 200, 'B'}; /*typedef을 썼기 때문에 struct 구조체 키워드를 사용하지 않고 
                                       student2구조체 st2선언, 각각 A, 100, A로 초기화 */

    printf("\nst2.lastName = %c\n", st2.lastName); //구조체 st2 안의 lastname 프린트
    printf("st2.studentId  = %d\n", st2.studentId); //구조체 st2 안의 studentId 프린트
    printf("st2.grade      = %c\n",st2.grade); //구조체 st2 안의 grade 프린트

    student2 st3; //typedef을 썼기 때문에 struct 구조체 키워드를 사용하지 않고  student2구조체 st3 선언

    st3=st2; //st2를 st3에 대입

    printf("\nst3.lastName = %c\n", st3.lastName); //구조체 st3 안의 lastname 프린트(==st2.lastname)
    printf("st3.studentId  = %d\n",st3.studentId); //구조체 st3 안의 studentId 프린트(==st2.studentId)
    printf("st3.grade = %c\n",st3.grade); //구조체 st3 안의 grade 프린트(==st2.grade)

    printf("\n\n----Software 2019038065 홍예림----\n");

    /* equality test */

    /*if(st3==st2)  (비교할 수 없다. 각각 비교 가능)
        printf("equal\n");
    else 
        printf("not equal\n");

    return 0;*/
}
