#define _CRT_SECURE_NO_WARNINGS 1

#include"contact.h"
void Test()
{
	struct A con;
	int input = 1;
	_init_contact(&con);
	while (input)
	{
		print_menu();
		printf("«Î—°‘Ò£∫");
		scanf("%d", &input);
		switch (input)
		{
		case ADD:
			Add(&con);
			break;
		case DEL:
			delete_contact(&con);
			break;
		case SEARCH:
			find_contacts(&con);
			break;
		case MODIFY:
			revise_contact(&con);
			break;
		case DISPLAY:
			print_contact(&con);
			break;
		case CLEAR:
			put_empty(&con);
			break;
		case SORT:
			sort_name(&con);
			break;
		case EXIT:
			break;
		default:
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