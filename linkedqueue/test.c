#define _CRT_SECURE_NO_WARNINGS 1


#include"linkedqueue.h"


void Test()
{
	LinkQueue que;
	int input =1 ;
	int length = 0;
	datatype x = 0;
	InitQueue(&que);
	while (input)
	{
		menu();
		printf("请选择：");
		scanf("%d", &input);
		switch (input)
		{
		case EXIT:
			DestoryQueue(&que);
			break;
		case INIT:
			InitQueue(&que);
			break;
		case DESTORY:
			DestoryQueue(&que);
			break;
		case CLEAR:
			ClearQueue(&que);
			break;
		case LENGTH:
			length=QueueLength(&que);
			printf("%d\n", length);
			break;
		case ENQUEUE:
			printf("请输入你所要入队元素的值：");
			scanf("%d", &x);
			fflush(stdin);
			EnQueue(&que,x);
			break;
		case DEQUEUE:
			Dequeue(&que);
			break;
		case PRINTQUEUE:
			PrintQueue(&que);
			break;
		default:
			input = 1 ;
			break;
		}

	}



}

int main()
{
	Test();
	system("pause");
	return 0;
}