/*
 * postfix.c
 *
 *  2020 Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

 /* stack 내에서 우선순위, lparen = 0 가장 낮음 */
typedef enum {
    lparen = 0,  /* (왼쪽 괄호 */
    rparen = 9,  /* )오른쪽 괄호*/
    times = 7,   /* * 곱셈 */
    divide = 6,  /* / 나눗셈 */
    plus = 5,    /* + 덧셈 */
    minus = 4,   /* - 뺄셈 */
    operand = 1 /* 피연산자 */
} precedence;


char infixExp[MAX_EXPRESSION_SIZE];      /* infix expression을 저장하는 배열 */
char postfixExp[MAX_EXPRESSION_SIZE];   /* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE];   /* postfix로 변환을 위해 필요한 스택 */
int evalStack[MAX_STACK_SIZE];      /* 계산을 위해 필요한 스택  */

int postfixStackTop = -1;  /* postfixStack top */
int evalStackTop = -1;      /* evalStack top */

int evalResult = 0;      /* 계산 결과 저장 */

void postfixPush(char x)//postfix 스택 삽입
{
    postfixStack[++postfixStackTop] = x;
}

char postfixPop()//postfix 스택  삭제
{
    char x;
    if (postfixStackTop == -1)
        return '\0';
    else {
        x = postfixStack[postfixStackTop--];
    }
    return x;
}

char postfixPeek()
{
    char x;
    if (postfixStackTop == -1)
        return '\0';
    else {
        x = postfixStack[postfixStackTop];
    }
    return x;

}

void evalPush(int x)  //eval 스택 삽입
{
    evalStack[++evalStackTop] = x;
}

int evalPop() //eval 스택  삭제
{
    if (evalStackTop == -1)
        return -1;
    else
        return evalStack[evalStackTop--];
}

void getInfix()
{
    printf("Type the expression >>> ");
    scanf("%s", infixExp);
}

precedence getToken(char symbol)
{
    switch (symbol) {
    case '(': return lparen;
    case ')': return rparen;
    case '+': return plus;
    case '-': return minus;
    case '/': return divide;
    case '*': return times;
    default: return operand; //에러검사는 하지 않고 기본 값은 피연산자
    }

}

precedence getPriority(char x)
{
    return getToken(x);
}

void charCat(char* c)
{
    if (postfixExp == '\0')
        strncpy(postfixExp, c, 1);
    else
        strncat(postfixExp, c, 1);
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 *변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()
{
    /* infixExp을 문자 하나씩 읽기위한 포인터 */
    char* exp = infixExp;
    char x = '0'; /*문자 하나를 임시로 저장하기 위한 변수*/
    int i, j;
    i = 0; j = 0;

    while (exp[i] != '\0')
    {
        x = exp[i];
        if (getPriority(x) == operand) { //피연산자일 경우 
            postfixExp[j++] = x;
        }
        else {  //연산자일 경우 
            char topOfStack = postfixPeek(); //스택에서 peek
            if (topOfStack == NULL) {
                postfixPush(x);
            }
            else if (x == '(') {  //(을 만나면 무조건 push 
                postfixPush(x);
            }
            else if (x == ')') { //)을 만나면  
                while (topOfStack != '(') {
                    topOfStack = postfixPop();
                    if (topOfStack == '(')
                        break;
                    postfixExp[j++] = topOfStack;
                }
                //스택 최상위보다 우선순위가 높은 연산자일 시 
            }
            else if (getPriority(x) > getPriority(topOfStack)) {
                postfixPush(x);
                //우선순위가 더 낮을 시 
            }
            else if (getPriority(x) <= getPriority(topOfStack)) {
                //우선순위가 높은 연산자를 만날때까지 스택에서 pop 
                while (getPriority(x) > getPriority(topOfStack)
                    || topOfStack != NULL) {
                    topOfStack = postfixPop();
                    postfixExp[j++] = topOfStack;
                }
                postfixPush(x);
            }
            else {
                postfixPush(x);
            }
        }
        i++;
    }

    char topOfStack;
    while (1) {
        topOfStack = postfixPop();
        if (topOfStack == NULL)
            break;
        postfixExp[j++] = topOfStack;
    }

    postfixExp[j] = '\0';   //마지막 

}
void debug()
{
    printf("\n---DEBUG\n");
    printf("infixExp =  %s\n", infixExp);//중위표기 프린트
    printf("postExp =  %s\n", postfixExp); //후위표기 프린트
    printf("eval result = %d\n", evalResult);//결과 프린트

    printf("postfixStack : ");
    for (int i = 0; i < MAX_STACK_SIZE; i++) //MAX_STACK_SIZE (10) 까지 반복
        printf("%c  ", postfixStack[i]);//postfix[i] 프린트

    printf("\n");

}

void reset()
{
    infixExp[0] = '\0';
    postfixExp[0] = '\0';

    for (int i = 0; i < MAX_STACK_SIZE; i++)
        postfixStack[i] = '\0';

    postfixStackTop = -1;//postfixstacktop을 -1로 초기화
    evalStackTop = -1;//evalstacktop을 -1로 초기화
    evalResult = 0;//evalresult 0으로 초기화
}

int evaluation()
{
    /* postfixExp, evalStack을 이용한 계산 */
    char* exp = postfixExp;
    precedence pr;
    int op1, op2;
    int i = 0;
    int n = 0;
    int top = -1;
    while (exp[i] != '\0') {
        pr = getPriority(exp[i]);
        if (pr == operand)
            evalPush(exp[i] - '0'); //스택 삽입
        else {
            op2 = evalPop();
            op1 = evalPop();
            switch (pr) {
            case plus:
                evalPush(op1 + op2);
                break;
            case minus:
                evalPush(op1 - op2);
                break;
            case times:
                evalPush(op1 * op2);
                break;
            case divide:
                evalPush(op1 / op2);
            }
        }
        i++;
    }
    evalResult = evalPop(); //결과를 반환
}


int main()
{
    printf("소프트웨어학과 2019038065 홍예림\n");
    char command;

    do {
        printf("----------------------------------------------------------------\n");
        printf("               Infix to Postfix, then Evaluation               \n");
        printf("----------------------------------------------------------------\n");
        printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

       switch (command) {
		case 'i': case 'I': //i 또는 I 입력
			getInfix(); //getInfix함수 호출
			break;
		case 'p': case 'P': //p 또는 P 입력
			toPostfix(); //toPostfix함수 호출
			break; 
		case 'e': case 'E': //e 또는 E입력
			evaluation(); //evauation 함수 호출
			break;
		case 'd': case 'D': //d 또는 D입력
			debug(); //debug함수 호출
			break;
		case 'r': case 'R': //r 또는 R입력
			reset(); //reset 함수 출력
			break;
		case 'q': case 'Q': //q또는 Q입력
			break; 
		default: //그 외 입력
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //경고 메세지 프린트
			break;
		}
    } while (command != 'q' && command != 'Q');// q 또는 Q입력 전까지 반복

    return 0;


}