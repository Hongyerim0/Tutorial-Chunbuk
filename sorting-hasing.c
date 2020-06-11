/*
 * hw5-sorting.c
 *
 *  Created on: May 22, 2019
 *
 *  Homework 5: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE                  13      /* prime number */
#define MAX_HASH_TABLE_SIZE     MAX_ARRAY_SIZE

 /* 필요에 따라 함수 추가 가능 */
int initialize(int** a);
int freeArray(int* a);
void printArray(int* a);

int selectionSort(int* a);
int insertionSort(int* a);
int bubbleSort(int* a);
int shellSort(int* a);
/* recursive function으로 구현 */
int quickSort(int* a, int n);

/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int* a, int** ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int* ht, int key);


int main()
{
    char command;
    int* array = NULL;
    int* hashtable = NULL;
    int key = -1;
    int index = -1;

    srand(time(NULL));
    printf("소프트웨어학과 2019038065 홍예림\n");

    do {
        printf("----------------------------------------------------------------\n");
        printf("                        Sorting & Hashing                       \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize       = z           Quit             = q\n");
        printf(" Selection Sort   = s           Insertion Sort   = i\n");
        printf(" Bubble Sort      = b           Shell Sort       = l\n");
        printf(" Quick Sort       = k           Print Array      = p\n");
        printf(" Hashing          = h           Search(for Hash) = e\n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch (command) {
        case 'z': case 'Z':
            initialize(&array);
            break;
        case 'q': case 'Q':
            freeArray(array);
            break;
        case 's': case 'S':
            selectionSort(array);
            break;
        case 'i': case 'I':
            insertionSort(array);
            break;
        case 'b': case 'B':
            bubbleSort(array);
            break;
        case 'l': case 'L':
            shellSort(array);
            break;
        case 'k': case 'K':
            printf("Quick Sort: \n");
            printf("----------------------------------------------------------------\n");
            printArray(array);
            quickSort(array, MAX_ARRAY_SIZE);
            printf("----------------------------------------------------------------\n");
            printArray(array);

            break;

        case 'h': case 'H':
            printf("Hashing: \n");
            printf("----------------------------------------------------------------\n");
            printArray(array);
            hashing(array, &hashtable);
            printArray(hashtable);
            break;

        case 'e': case 'E':
            printf("Your Key = ");
            scanf("%d", &key);
            printArray(hashtable);
            index = search(hashtable, key);
            printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
            break;

        case 'p': case 'P':
            printArray(array);
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    } while (command != 'q' && command != 'Q');

    return 1;
}

int initialize(int** a)
{
    int* temp = NULL;

    /* array가 NULL인 경우 메모리 할당 */
    if (*a == NULL) {
        temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
        *a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
    }
    else
        temp = *a;

    /* 랜덤값을 배열의 값으로 저장 */
    for (int i = 0; i < MAX_ARRAY_SIZE; i++)
        temp[i] = rand() % MAX_ARRAY_SIZE;

    return 0;
}

int freeArray(int* a) //메모리 해제
{
    if (a != NULL)
        free(a); 
    return 0;
}

void printArray(int* a) //배열 출력
{
    if (a == NULL) { //배열이 비어있으면
        printf("nothing to print.\n"); //에러메세지 출력
        return;
    }
    for (int i = 0; i < MAX_ARRAY_SIZE; i++)
        printf("a[%02d] ", i);
    printf("\n");
    for (int i = 0; i < MAX_ARRAY_SIZE; i++)
        printf("%5d ", a[i]);
    printf("\n");
}


int selectionSort(int* a) //선택정렬
{
    int min; //최소값 저장할 변수
    int minindex; // 최소값 인덱스
    int i, j;

    printf("Selection Sort: \n");
    printf("----------------------------------------------------------------\n");

    printArray(a); //정렬 전 프린트

    for (i = 0; i < MAX_ARRAY_SIZE; i++)
    {  //첫번째 원소부터 교체 시작
        minindex = i; 
        min = a[i];
        for (j = i + 1; j < MAX_ARRAY_SIZE; j++)
        {//주어진 배열 중 최소값을 찾고
            if (min > a[j])
            {  
                min = a[j]; //최소값을 저장
                minindex = j; //최소값 인덱스 저장
            }
        }
        //최솟값을 제일 앞으로 보냄
        a[minindex] = a[i]; 
        a[i] = min;
    }
    printf("----------------------------------------------------------------\n");
    printArray(a);
    return 0;
}

int insertionSort(int* a) //삽입정렬
{
    int i, j, t;

    printf("Insertion Sort: \n");
    printf("----------------------------------------------------------------\n");
    printArray(a); //정렬 전 프린트

    for (i = 1; i < MAX_ARRAY_SIZE; i++) 
    {
        t = a[i]; //임시저장공간 t에 list[i]값 저장 (배열의 두번째 원소부터 비교시작)
        j = i;  
        while (a[j - 1] > t && j > 0) //t의 값보다 t의 왼쪽 값이 더 크고 j가 0보다 크면
        {
            a[j] = a[j - 1]; // 오른쪽으로 한칸 이동(list[j-1]값을 빈자리로 이동)
            j--; // j값 1만큼 감소
        }
        a[j] = t; //a[j-1]가 t보다 작거나 j가 0보다 작으면 a[j]자리에 t삽입
    }
    printf("----------------------------------------------------------------\n");
    printArray(a); //정렬 후 프린트

    return 0;
}

int bubbleSort(int* a) //버블 정렬
{
    int i, j, t;

    printf("Bubble Sort: \n");
    printf("----------------------------------------------------------------\n");

    printArray(a); //정렬 전 프린트

    for (i = 0; i < MAX_ARRAY_SIZE; i++) 
    {
        for (j = 1; j < MAX_ARRAY_SIZE; j++)
        {   // 최댓값을 제일 뒤로 보내는 것을 반복
            if (a[j-1] > a[j]) 
            {  //j-1번째의 요소가 j번째의 요소보다 크면 교환
                t = a[j-1]; 
                a[j-1] = a[j];
                a[j] = t;
            }
        }
    }
    printf("----------------------------------------------------------------\n");
    printArray(a); //정렬 후 프린트

    return 0;
}

int shellSort(int* a) //셸 정렬
{
    int i, j, k, h, v;

    printf("Shell Sort: \n");
    printf("----------------------------------------------------------------\n");
     
    printArray(a); //정렬 전 프린트

    for (h = MAX_ARRAY_SIZE / 2; h > 0; h /= 2) //2로 나눈 값부터 0보다 클 때까지 반복
                                                               // 2로 나눠주면서 비교 간격 설정
    {
        for (i = 0; i < h; i++) // h간격에 있는 원소들을 삽입정렬한다.
        {
            for (j = i + h; j < MAX_ARRAY_SIZE; j += h) //간격만큼 떨어진 원소들을 그룹으로 묶는다.
            {
                v = a[j];
                k = j;
                while (k > h - 1 && a[k - h] > v) 
                { //묶인 그룹 내에서 정렬
                    a[k] = a[k - h];
                    k -= h;
                }
                a[k] = v;
            }
        }
    }
    printf("----------------------------------------------------------------\n");
    printArray(a); //정렬 후 프린트

    return 0;
}

int quickSort(int* a, int n) //퀵 정렬
{
    int v, t; //v: 피봇(기준값), t: temp
    int i, j;
    // i: 피봇보다 작은 부분,  v: 피봇보다 큰 부분
    if (n > 1) //원소의 개수가 1보다 크면
    {
        v = a[n - 1]; //v에 마지막원소 저장
        i = -1; //i에 -1저장
        j = n - 1; // j에 마지막 인덱스 저장

        while (1)
        {
            while (a[++i] < v); // a[i]가 v보다 더 작으면 한칸증가
            while (a[--j] > v); // a[j]가 v보다 더 크면 한칸감소

            if (i >= j)
                break;
          //a[i]와 a[j]의 값 교환
            t = a[i];
            a[i] = a[j];
            a[j] = t; 
        }
        //a[i]와 v의 값 교환
        t = a[i];
        a[i] = a[n - 1];
        a[n - 1] = t;

        //분할 정렬해준다.
        quickSort(a, i); 
        quickSort(a + i + 1, n - i - 1);
    }


    return 0;
}

int hashCode(int key) {
    return key % MAX_HASH_TABLE_SIZE; //key값을 %연산자 이용하여 hashcode로 사용
}

int hashing(int* a, int** ht) //
{
    int* hashtable = NULL;

    /* hash table이 NULL인 경우 메모리 할당 */
    if (*ht == NULL) {
        hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
        *ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
    }
    else {
        hashtable = *ht; /* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
    }

    for (int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
        hashtable[i] = -1;  //hashtable 원소 전부 -1로 초기화

    /*
    for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
            printf("hashtable[%d] = %d\n", i, hashtable[i]);
    */

    int key = -1; //key값 -1로 초기화
    int hashcode = -1; //hashcode -1로 초기화
    int index = -1; //index -1로 초기화
    for (int i = 0; i < MAX_ARRAY_SIZE; i++)
    {
        key = a[i];
        hashcode = hashCode(key); //key값 hashcode로 변환
        /*
        printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
        */
        if (hashtable[hashcode] == -1) 
        {
            hashtable[hashcode] = key; //hashtable 에 key값 저장
        }
        else {

            index = hashcode; 

            while (hashtable[index] != -1)  //hashtable 값이 -1이 아닐때까지 반복
            {
                index = (++index) % MAX_HASH_TABLE_SIZE; 
                /*
                printf("index = %d\n", index);
                */
            }
            hashtable[index] = key; //hashtable[index]에 key값을 저장해준다.
        }
    }

    return 0;
}

int search(int* ht, int key) 
{
    int index = hashCode(key); //index에 hashcode저장

    if (ht[index] == key) // 같다면
        return index; //index를 리턴

    while (ht[++index] != key)
    {
        index = index % MAX_HASH_TABLE_SIZE; //index를 13으로 나눈 나머지를 index에 저장
    }
    return index; //index값 리턴
}
