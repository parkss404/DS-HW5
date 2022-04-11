/* circularQ.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4 

typedef char element; 

typedef struct {//구조체 선언 queue이니까, front,rear,queue
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;


QueueType *createQueue();
int freeQueue(QueueType *cQ);
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ, element* item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);
element getElement();

int main(void)
{
	QueueType *cQ = createQueue();
	element data;
	char command;

	do{
        printf("[----- [박성준]  [2021040026] ----]\n");//학번,이름
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I'://i 시행시, 
			data = getElement();//입력받고 data 저장
			enQueue(cQ, data);//enQueue함수
			break;
		case 'd': case 'D'://d 시행시, 
			deQueue(cQ, &data);//deQueue함수
			break;
		case 'p': case 'P'://p 시행시, 
			printQ(cQ);//printQ함수
			break;
		case 'b': case 'B'://b 시행시, 
			debugQ(cQ);//debugQ함수
			break;
		case 'q': case 'Q'://q 시행시, 
   	        freeQueue(cQ);//freeQueue함수
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');


	return 1;
}

QueueType *createQueue() //큐 만들기
{
	QueueType *cQ; //구조체 가져오기 
	cQ = (QueueType *)malloc(sizeof(QueueType)); //malloc이용해서 struct값 동적할당하기 
	cQ->front = 0; 
	cQ->rear = 0; //초기값은 queue 와 rear값 동일하게
	return cQ; 
} //큐 초기화 

int freeQueue(QueueType *cQ) //큐 초기화 
{
    if(cQ == NULL) return 1;//cQ가 비었을경우,
    free(cQ);// 큐 메모리 해제
    return 1;
}

element getElement()
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);//item값 받기
	return item;//item값을 리턴하는 함수
}


int isEmpty(QueueType *cQ) //비어있는지 확인함수
{

    if(cQ -> front == cQ -> rear){ //rear + 1 값이 front 값과 동일할 시  
        printf("Circular Queue is empty!");
        return 1;
    }

    else return 0;
}


int isFull(QueueType *cQ)//꽉 차있는지 확인함수
{
   
    if(((cQ -> rear+1)%MAX_QUEUE_SIZE) == cQ -> front){ //rear + 1 값이 front 값과 동일할 시  
        printf("Circular Queue is full!\n");//Queue값이 가득 차 있다.
        return 1;
    }

    else return 0;
}


void enQueue(QueueType *cQ, element item)//큐 삽입
{
    if(isFull(cQ)) return; //꽉 차있으면 넘어감 
    else{
        cQ->rear = (cQ -> rear + 1 ) % MAX_QUEUE_SIZE;  //cQ의 rear값을 1늘린다. 이때 나머지를 출력함으로써 rear값을 순환하도록 지정한다. 
        cQ->queue[cQ->rear] = item; //받아온 item값을 queue의 배열의 rear이 가르키는 삽입한다. 
    }
}


void deQueue(QueueType *cQ, element *item)//큐 삭제
{
    if(isEmpty(cQ)) return; //비어있으면 넘어감
	else {
		cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE;//cQ의 front값을 1늘린다. 이때 나머지를 출력함으로써 front값을 순환하도록 지정한다. 
		*item = cQ->queue[cQ->front];//item을 역참조한 값이 해당 큐에서 front가 나타내는 index의 큐값임을 나타낸다.     
		return;
	}

}


void printQ(QueueType *cQ)
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE; //first = front + 1 
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE; //last = rear + 1

	printf("Circular Queue : [");

	i = first; 
	while(i != last){
		printf("%3c", cQ->queue[i]); //while문을 통해서 배열 출력
		i = (i+1)%MAX_QUEUE_SIZE; //i 증가 to last까지

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)// 리스트 생성
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i);//front 위치값 출력
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);//리스트 인덱스와 큐값 출력

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);//front와 rear값 출력 
}

