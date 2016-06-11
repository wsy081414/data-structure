#define _CRT_SECURE_NO_WARNINGS 1

#include"cal.h"


void Test()
{

	char infix[MAXSIZE] = { 0 };
	char postfix[MAXSIZE] = { 0 };
	int result = 0;
	printf("请输入一个中缀表达式：\n");
	scanf("%s", infix);
	fflush(stdin);
	To_PostFix(infix, postfix);
	printf("转换得到的后缀表达式是：\n");
	printf("%s\n", postfix);
	Calculator(postfix, &result);
	printf("最后得到的结果：\n");
	printf("%d\n", result);
	

}

int main()
{
	Test();
	system("pause");
	return 0;
}