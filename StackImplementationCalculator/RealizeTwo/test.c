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
			printf("������һ����׺���ʽ\n");
			scanf("%s", NifixExpression);
			fflush(stdin);

			break;
		case 2:
			TransmitExpression(NifixExpression, PostfixExpression);

			printf("��׺���ʽ  %s  ����ת���õ���׺���ʽ  %s  \n", NifixExpression, PostfixExpression);       //����׺���ʽת��Ϊ��׺���ʽ 
			break;
		case 3:
			printf("���õ��Ľ����:\n"); //���ݺ�׺���ʽ������
			EvaluateExpression(PostfixExpression, &result);
			printf("%d\n", result);
			

			break;
		default:
			printf("ѡ����Ч\n");
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