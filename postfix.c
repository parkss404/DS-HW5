/* postfix.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

/* stack 내에서 우선순위, lparen = 0 가장 낮음 */
typedef enum{
	lparen = 0,  // ( 왼쪽 괄호 
	rparen = 9,  // ) 오른쪽 괄호
	times = 7,   // * 곱셈 
	divide = 6,  // / 나눗셈
	plus = 5,    // + 덧셈 
	minus = 4,   // - 뺄셈 
	operand = 1 // 피연산자 
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];   	// infix expression을 저장하는 배열 
char postfixExp[MAX_EXPRESSION_SIZE] = {};	// postfix로 변경된 문자열을 저장하는 배열 
char postfixStack[MAX_STACK_SIZE];	// postfix로 변환을 위해 필요한 스택 
int evalStack[MAX_STACK_SIZE];		// 계산을 위해 필요한 스택 

int postfixStackTop = -1;  // postfixStack용 top 
int evalStackTop = -1;	   // evalStack용 top 

int evalResult = 0;	   // 계산 결과를 저장 

void postfixpush(char x);
char postfixPop();
void evalPush(int x);
int evalPop();
void getInfix();
precedence getToken(char symbol);
precedence getPriority(char x);
void charCat(char* c);
void toPostfix();
void debug();
void reset();
void evaluation();

int main()
{
	char command;

	do{
        printf("[----- [박성준]  [2021040026] ----]\n");//학번,이름
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I'://i입력 시 
			getInfix();//getInfix함수 실행
			break;
		case 'p': case 'P'://p입력 시
			toPostfix();//toPostfix함수 실행
			break;
		case 'e': case 'E'://p입력 시
			evaluation();//evaluation함수 실행
			break;
		case 'd': case 'D'://p입력 시
			debug();//debug함수 실행
			break;
		case 'r': case 'R'://p입력 시
			reset();//reset함수 실행
			break;
		case 'q': case 'Q'://q입력 시
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

void postfixPush(char x)
{
    postfixStack[++postfixStackTop] = x;
}//top + 1 하고 스택에 x값을 추가한다.

char postfixPop()
{
    char x;
    if(postfixStackTop == -1)//탑이 -1일 경우  
        return '\0';//널값 리턴
    else {
    	x = postfixStack[postfixStackTop--];//아니면, 스택에서 pop하여 x에 대입
    }
    return x;//x리턴
}

void evalPush(int x)
{
    evalStack[++evalStackTop] = x;//x값 stack에 push
}

int evalPop()
{
    if(evalStackTop == -1)//탑이 -1일 경우
        return -1;
    else
        return evalStack[evalStackTop--];//스택 pop값 리턴
}

/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */
void getInfix()
{
    printf("Type the expression >>> ");
    scanf("%s",infixExp);
} //그냥 값만 가져오기

precedence getToken(char symbol)
{
	switch(symbol) {
	case '(' : return lparen;
	case ')' : return rparen;
	case '+' : return plus;
	case '-' : return minus;
	case '/' : return divide;
	case '*' : return times;
	default : return operand;
	}
}//연산자를 받을 경우 각각에 맞는 값을 리턴하는 함수 (구조체)

precedence getPriority(char x)
{
	return getToken(x);
}//우선순위 가져오기 해당 구조체에서는 숫자로 표현되어있기에 리턴 시 수가 나옴

/**
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c)
{
	if (postfixExp == '\0') //배열 비어있을 시
		strncpy(postfixExp, c, 1); //postfixExp배열에서 c주소에서 1만큼을 복사하기
	else
		strncat(postfixExp, c, 1);//postfixExp배열 뒤에 c주소에서 1만큼을 붙이기
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()
{
	// infixExp의 문자 하나씩을 읽기위한 포인터 
	char *exp = infixExp;
	char x; // 문자하나를 임시로 저장하기 위한 변수

	//exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 
	while(*exp != '\0')//문자가 null값이 아닐때까지 반복
	{
		if(getPriority(*exp) == operand)// 문자가 피연산자인 경우에,
		{
			x = *exp;//문자 저장
        	charCat(&x);//문자 주소값 charCat전달
		}
        else if(getPriority(*exp) == lparen) {// 문자가 '('인 경우에,

        	postfixPush(*exp);//함수에 의해서 스택에 푸쉬하게 된다.
        }
        else if(getPriority(*exp) == rparen)// 문자가 ')'인 경우에,
        {
        	while((x = postfixPop()) != '(') {//'('가 나올 때까지
        		charCat(&x);//문자 주소값 charCat전달
        	}
	    }
        else
        {
            while(getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp))
            //후위연산 스택에서의 탑에 위치한 문자가 우선순위가 현재 문자의 우선순위보다 더 높을때 (일반사칙연산)
            {
            	x = postfixPop();//스택에서 팝을 한값을 x로 지정하고
            	charCat(&x);//charCat함수 실행
            }
            postfixPush(*exp);//반복문 종료 후 현재의 문자값을 함수에 의해 푸쉬 
        }
        exp++;
        }

    while(postfixStackTop != -1)//후위연산식 스택의 탑이 -1인 경우에 
    {
    	x = postfixPop(); //이 함수에서 리턴받은 '\0'을 x로
    	charCat(&x);//x의 주소를 charCat함수로 다시
    }

}
void debug()
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp); 
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult);
    //infix , postfix , evalResult 상태 값 출력
	printf("postfixStack : ");
	for(int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);//스택에 들어있는 연산자들 모두 프린트

	printf("\n");

}

void reset()
{
	infixExp[0] = '\0'; 
	postfixExp[0] = '\0';
    //값 초기화 

	for(int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';
    //연산자 초기화     
	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;
    //탑 상태,결과값 초기화
}

void evaluation()//연산
{
	int opr1, opr2, i;

	int length = strlen(postfixExp);//문자열 길이를 저장
	char symbol;
	evalStackTop = -1;

	for(i = 0; i < length; i++)//문자열 길이만큼 반복
	{
		symbol = postfixExp[i];//symbol에 문자 하나씩 저장
		if(getToken(symbol) == operand) {//symbol값이 피연산자라면,
			evalPush(symbol - '0');//symbol - '0'(문자 to 숫자로 변환한 값)를 스택 푸쉬
		}
		else {
			opr2 = evalPop();//피연산자들 pop
			opr1 = evalPop();//피연산자들 pop
			switch(getToken(symbol)) {//symbol값을 가져오는데, 
			case plus: evalPush(opr1 + opr2); break;//+이면, opr1 + opr2 푸쉬
			case minus: evalPush(opr1 - opr2); break;//-이면, opr1 - opr2 푸쉬
			case times: evalPush(opr1 * opr2); break;//*이면, opr1 * opr2 푸쉬
			case divide: evalPush(opr1 / opr2); break;///이면, opr1 / opr2푸쉬
			default: break;
			}
		}
	}
	evalResult = evalPop();//최종 값을 pop하면 계산값이 나오게된다.
}

