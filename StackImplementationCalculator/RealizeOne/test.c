#define _CRT_SECURE_NO_WARNINGS 1

#include"cal.h"


void Test()
{

	char infix[MAXSIZE] = { 0 };
	char postfix[MAXSIZE] = { 0 };
	int result = 0;
	printf("������һ����׺���ʽ��\n");
	scanf("%s", infix);
	fflush(stdin);
	To_PostFix(infix, postfix);
	printf("ת���õ��ĺ�׺���ʽ�ǣ�\n");
	printf("%s\n", postfix);
	Calculator(postfix, &result);
	printf("���õ��Ľ����\n");
	printf("%d\n", result);
	

}

int main()
{
	Test();
	system("pause");
	return 0;
}