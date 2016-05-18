#define _CRT_SECURE_NO_WARNINGS 1

#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_SECURE_NO_WARNINGS 1

#include"contact-text-3.h"

//检查容量
void check(struct A *con)
{
	if (con->i == con->capacity)
	{
		int sz = con->capacity + INC_NUM;
		con->capacity += INC_NUM;
		if (sz == 0)
		{
			printf("错误");
			return;
		}
		con->arr = (struct contact *)realloc(con->arr, sz*sizeof(struct contact));
	}

}
//添加联系人信息
void Add(struct A *con)
{
	check(con);
	printf("请输入名字：");
	scanf("%s", con->arr[con->i].name);
	printf("请输入性别：");
	scanf("%s", con->arr[con->i].sex);
	printf("请输入年龄：");
	scanf("%d", &(con->arr[con->i].age));
	printf("请输入电话号码：");
	scanf("%s", con->arr[con->i].tele);
	printf("请输入地址：");
	scanf("%s", con->arr[con->i].address);
	con->i++;
	printf("添加完毕。\n");

}
//打印所有联系人信息
void print_contact(struct A *con)
{
	printf("打印联系人信息\n");

	int i = 0;
	printf("%-10s%-5s%-5s%-15s%-20s\n", "name",
		"sex", "age", "tele",
		"ddress");
	for (i = 0; i < con->i; i++)
	{
		printf("%-10s%-5s%-5d%-15s%-20s\n", con->arr[i].name,
			con->arr[i].sex, con->arr[i].age, con->arr[i].tele,
			con->arr[i].address);
	}
	printf("\n");
}


//查找指定联系人所在位置
int find_position(struct A *pcon)
{
	int i = 0;
	char name[20];
	printf("请输入你所要查找的名字：");
	scanf("%s", name);
	for (i = 0; i < pcon->i; i++)
	{
		if (strcmp(pcon->arr[i].name, name) == 0)
		{
			return i;
		}
	}
	return -1;
}



//删除联系人信息
int delete_contact(struct A *pcon)
{
	int i = 0;
	printf("删除联系人\n");
	int ret = find_position(pcon);

	if (ret != -1)
	{
		for (i = ret; i < pcon->i - 1; i++)
		{
			pcon->arr[i] = pcon->arr[i + 1];
		}
		pcon->i--;
		return 1;
	}
	else
		printf("没有找到这个人，无法删除！\n");
	return 0;
}

//查找并且输出这个找到的信息。
int find_contacts(struct A *pcon)
{
	printf("查找联系人\n");
	int ret = find_position(pcon);
	if (ret != -1)
	{
		printf("姓名：%s\n", pcon->arr[ret].name);
		printf("性别：%s\n", pcon->arr[ret].sex);
		printf("年龄：%d\n", pcon->arr[ret].age);
		printf("电话号码：%s\n", pcon->arr[ret].tele);
		printf("地址：%s\n", pcon->arr[ret].address);
		return 1;
	}
	printf("没有找到\n");
	return 0;
}

//修改指定联系人的信息
int revise_contact(struct A *pcon)
{
	printf("**************\n");
	printf("**修改联系人**\n");
	printf("**************\n");

	int ret = find_position(pcon);
	if (ret != -1)
	{
		printf("请输入你所想要修改的数据：\n");
		printf("请输入修改后的名字：");
		scanf("%s", pcon->arr[ret].name);
		printf("请输入修改后的性别：");
		scanf("%s", pcon->arr[ret].sex);
		printf("请输入修改后的年龄：");
		scanf("%d", &(pcon->arr[ret].age));
		printf("请输入修改后的电话号码：");
		scanf("%s", pcon->arr[ret].tele);
		printf("请输入修改后的地址：");
		scanf("%s", pcon->arr[ret].address);
		return 1;
	}
	printf("没有找到你所需要修改的联系人。\n");
	return 0;
}

//清空所有联系人
void put_empty(struct A *pcon)
{
	printf("清空联系人\n");
	memset(pcon->arr, 0, (pcon->capacity)* sizeof(struct contact));
	pcon->i = 0;
}

//以名字排序所有联系人

void sort_name(struct A *pcon)
{
	printf("排序\n");
	char ch = 0;
	int i = 0;
	int j = 0;
	printf("请选择排序方式（‘<’代表由z->a,'>'代表由a->z）:");
	fflush(stdin);
	scanf("%c", &ch);
	int flag = 0;
	if (ch == '>')
	{

		for (i = 0; i < pcon->i; i++)
		{
			flag = 0;
			for (j = 0; j < pcon->i - i - 1; j++)
			{
				if (strcmp(pcon->arr[j].name, pcon->arr[j + 1].name)>0)
				{
					struct contact tmp = { 0 };
					tmp = pcon->arr[j];
					pcon->arr[j] = pcon->arr[j + 1];
					pcon->arr[j + 1] = tmp;
					flag = 1;
				}

			}
			if (flag == 0)
				break;
		}
	}
	else if (ch == '<')
	{
		for (i = 0; i < pcon->i; i++)
		{
			flag = 0;
			for (j = 0; j < pcon->i - i - 1; j++)
			{
				if (strcmp(pcon->arr[j].name, pcon->arr[j + 1].name)<0)
				{
					struct contact tmp = { 0 };
					tmp = pcon->arr[j];
					pcon->arr[j] = pcon->arr[j + 1];
					pcon->arr[j + 1] = tmp;
					flag = 1;
				}

			}
			if (flag == 0)
				break;
		}
	}
	else
		printf("选择错误，请返回重新选择：\n");
	printf("排序结束！\n");


}


void _init_contact(struct A *pcon)
{
	pcon->i = 0;
	pcon->arr = (struct contact*)malloc(sizeof(struct contact)*INIT_NUM);
	memset(pcon->arr, 0, INIT_NUM*sizeof(struct contact));
	pcon->capacity = INIT_NUM;
	load(pcon);
}


void print_menu()
{
	printf("$$$$$$$$CONTACT-TEXT$$$$$$$$\n");
	printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
	printf("$$$  1.add      2.del    $$$\n");
	printf("$$$  3.search   4.modify $$$\n");
	printf("$$$  5.show     6.clr    $$$\n");
	printf("$$$  7.sort     0.exit   $$$\n");
	printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
}




void load(struct A *pcon)
{
	int n = 0;
	struct contact tmp = {0};
	
	FILE *pRead = fopen(FILENAME, "r");

	if (pRead == NULL)
	{
		perror("open failed for read error");
		exit(EXIT_FAILURE);
	}
	while (fread(&tmp, sizeof(struct contact), 1, pRead))
	{
		check(pcon);
		pcon->arr[n] = tmp;
		n++;
		pcon->i++;

	}
	fclose(pRead);
}

void save(struct A *pcon)
{
	FILE *pWrite = fopen(FILENAME, "w");
	if (pWrite == NULL)
	{
		perror("open failed for write error");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < pcon->i; i++)
	{
		fwrite(&(pcon->arr[i]), sizeof(struct contact), 1,pWrite);
	}
	free(pcon->arr);
	fclose(pWrite);
}

