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

 /* stack ������ �켱����, lparen = 0 ���� ���� */
typedef enum {
    lparen = 0,  /* (���� ��ȣ */
    rparen = 9,  /* )������ ��ȣ*/
    times = 7,   /* * ���� */
    divide = 6,  /* / ������ */
    plus = 5,    /* + ���� */
    minus = 4,   /* - ���� */
    operand = 1 /* �ǿ����� */
} precedence;


char infixExp[MAX_EXPRESSION_SIZE];      /* infix expression�� �����ϴ� �迭 */
char postfixExp[MAX_EXPRESSION_SIZE];   /* postfix�� ����� ���ڿ��� �����ϴ� �迭 */
char postfixStack[MAX_STACK_SIZE];   /* postfix�� ��ȯ�� ���� �ʿ��� ���� */
int evalStack[MAX_STACK_SIZE];      /* ����� ���� �ʿ��� ����  */

int postfixStackTop = -1;  /* postfixStack top */
int evalStackTop = -1;      /* evalStack top */

int evalResult = 0;      /* ��� ��� ���� */

void postfixPush(char x)//postfix ���� ����
{
    postfixStack[++postfixStackTop] = x;
}

char postfixPop()//postfix ����  ����
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

void evalPush(int x)  //eval ���� ����
{
    evalStack[++evalStackTop] = x;
}

int evalPop() //eval ����  ����
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
    default: return operand; //�����˻�� ���� �ʰ� �⺻ ���� �ǿ�����
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
 * infixExp�� ���ڸ� �ϳ��� �о�鼭 stack�� �̿��Ͽ� postfix�� �����Ѵ�.
 *����� postfix�� postFixExp�� ����ȴ�.
 */
void toPostfix()
{
    /* infixExp�� ���� �ϳ��� �б����� ������ */
    char* exp = infixExp;
    char x = '0'; /*���� �ϳ��� �ӽ÷� �����ϱ� ���� ����*/
    int i, j;
    i = 0; j = 0;

    while (exp[i] != '\0')
    {
        x = exp[i];
        if (getPriority(x) == operand) { //�ǿ������� ��� 
            postfixExp[j++] = x;
        }
        else {  //�������� ��� 
            char topOfStack = postfixPeek(); //���ÿ��� peek
            if (topOfStack == NULL) {
                postfixPush(x);
            }
            else if (x == '(') {  //(�� ������ ������ push 
                postfixPush(x);
            }
            else if (x == ')') { //)�� ������  
                while (topOfStack != '(') {
                    topOfStack = postfixPop();
                    if (topOfStack == '(')
                        break;
                    postfixExp[j++] = topOfStack;
                }
                //���� �ֻ������� �켱������ ���� �������� �� 
            }
            else if (getPriority(x) > getPriority(topOfStack)) {
                postfixPush(x);
                //�켱������ �� ���� �� 
            }
            else if (getPriority(x) <= getPriority(topOfStack)) {
                //�켱������ ���� �����ڸ� ���������� ���ÿ��� pop 
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

    postfixExp[j] = '\0';   //������ 

}
void debug()
{
    printf("\n---DEBUG\n");
    printf("infixExp =  %s\n", infixExp);//����ǥ�� ����Ʈ
    printf("postExp =  %s\n", postfixExp); //����ǥ�� ����Ʈ
    printf("eval result = %d\n", evalResult);//��� ����Ʈ

    printf("postfixStack : ");
    for (int i = 0; i < MAX_STACK_SIZE; i++) //MAX_STACK_SIZE (10) ���� �ݺ�
        printf("%c  ", postfixStack[i]);//postfix[i] ����Ʈ

    printf("\n");

}

void reset()
{
    infixExp[0] = '\0';
    postfixExp[0] = '\0';

    for (int i = 0; i < MAX_STACK_SIZE; i++)
        postfixStack[i] = '\0';

    postfixStackTop = -1;//postfixstacktop�� -1�� �ʱ�ȭ
    evalStackTop = -1;//evalstacktop�� -1�� �ʱ�ȭ
    evalResult = 0;//evalresult 0���� �ʱ�ȭ
}

int evaluation()
{
    /* postfixExp, evalStack�� �̿��� ��� */
    char* exp = postfixExp;
    precedence pr;
    int op1, op2;
    int i = 0;
    int n = 0;
    int top = -1;
    while (exp[i] != '\0') {
        pr = getPriority(exp[i]);
        if (pr == operand)
            evalPush(exp[i] - '0'); //���� ����
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
    evalResult = evalPop(); //����� ��ȯ
}


int main()
{
    printf("����Ʈ�����а� 2019038065 ȫ����\n");
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
		case 'i': case 'I': //i �Ǵ� I �Է�
			getInfix(); //getInfix�Լ� ȣ��
			break;
		case 'p': case 'P': //p �Ǵ� P �Է�
			toPostfix(); //toPostfix�Լ� ȣ��
			break; 
		case 'e': case 'E': //e �Ǵ� E�Է�
			evaluation(); //evauation �Լ� ȣ��
			break;
		case 'd': case 'D': //d �Ǵ� D�Է�
			debug(); //debug�Լ� ȣ��
			break;
		case 'r': case 'R': //r �Ǵ� R�Է�
			reset(); //reset �Լ� ���
			break;
		case 'q': case 'Q': //q�Ǵ� Q�Է�
			break; 
		default: //�� �� �Է�
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //��� �޼��� ����Ʈ
			break;
		}
    } while (command != 'q' && command != 'Q');// q �Ǵ� Q�Է� ������ �ݺ�

    return 0;


}