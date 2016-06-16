#define _CRT_SECURE_NO_WARNINGS 1
#include"school_system.h"


void Test()
{
	BITREE root=NULL;
	int input = 1;
	while (input)
	{
		printf_menu();
		printf("请选择：");
		scanf("%d", &input);
		fflush(stdin);
		switch (input)
		{
		case CREATE:
			root=CreateTRee();
			break;
		case INIT:
			break;
		case FINDALLCHILD:
			FindAllCHild(root);
			break;
		case FINDPARENT:
			FindParent(root);
			break;
		case FINDPERSON:
			FindPerson(root);
			break;
		case SHOW:
			printf("前序遍历：\n");
			pretraversal_binary_tree(root);
			printf("\n");
			printf("中序遍历：\n");
			intraversal_binary_tree(root);
			printf("\n");
			printf("后序遍历：\n");
			postraversal_binary_tree(root);
			printf("\n");
			break;
		case FINDCOLLEGE:
			FindCollege(root);
			break;
		case QUIT:
			break;
		default :
			input = 1;
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