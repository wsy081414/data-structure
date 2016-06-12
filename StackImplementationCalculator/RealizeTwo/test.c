#define _CRT_SECURE_NO_WARNINGS 1

#include"cal.h"


void Test()
{

	char NifixExpression[MAXSIZE] = { 0 };
	char PostfixExpression[MAXSIZE] = { 0 };
	int result = 0;
	int n = 0;
	int input = 1;
	while (input)
	{
		Menu();
		scanf("%d", &n);
		fflush(stdin);
		switch (n)
		{
		case 0:
			exit(1);
			break;
		case 1:
			printf("请输入一个中缀表达式\n");
			scanf("%s", NifixExpression);
			fflush(stdin);

			break;
		case 2:
			TransmitExpression(NifixExpression, PostfixExpression);

			printf("中缀表达式  %s  经过转换得到后缀表达式  %s  \n", NifixExpression, PostfixExpression);       //将中缀表达式转换为后缀表达式 
			break;
		case 3:
			printf("最后得到的结果是:\n"); //根据后缀表达式计算结果
			EvaluateExpression(PostfixExpression, &result);
			printf("%d\n", result);
			

			break;
		default:
			printf("选择无效\n");
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