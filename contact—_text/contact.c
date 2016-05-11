#define _CRT_SECURE_NO_WARNINGS 1

#include"contact.h"

//�����ϵ����Ϣ
void Add(struct A *con)
{
	printf("���������֣�");
	scanf("%s", con->arr[con->i].name);
	printf("�������Ա�");
	scanf("%s", con->arr[con->i].sex);
	printf("���������䣺");
	scanf("%d", &(con->arr[con->i].age));
	printf("������绰���룺");
	scanf("%s", con->arr[con->i].tele);
	printf("�������ַ��");
	scanf("%s", con->arr[con->i].address);
	con->i++;
	printf("�����ϡ�\n");

}
//��ӡ������ϵ����Ϣ
void print_contact(struct A *con)
{
	printf("��ӡ��ϵ����Ϣ\n");

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


//����ָ����ϵ������λ��
int find_position(struct A *pcon)
{
	int i = 0;
	char name[20];
	printf("����������Ҫ���ҵ����֣�");
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



//ɾ��������ϵ����Ϣ
int delete_contact(struct A *pcon)
{
	int i = 0;
	printf("ɾ����ϵ��\n");
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
		printf("û���ҵ�����ˣ��޷�ɾ����\n");
	return 0;



}

//���Ҳ����������ҵ�����Ϣ��
int find_contacts(struct A *pcon)
{
	printf("������ϵ��\n");
	int ret = find_position(pcon);
	if (ret != -1)
	{
		printf("������%s\n", pcon->arr[ret].name);
		printf("�Ա�%s\n", pcon->arr[ret].sex);
		printf("���䣺%d\n", pcon->arr[ret].age);
		printf("�绰���룺%s\n", pcon->arr[ret].tele);
		printf("��ַ��%s\n", pcon->arr[ret].address);
		return 1;
	}
	printf("û���ҵ�\n");
	return 0;
}

//�޸�ָ����ϵ�˵���Ϣ
int revise_contact(struct A *pcon)
{
	int ret = find_position(pcon);
	printf("�޸���ϵ��\n");
	if (ret != -1)
	{
		printf("������������Ҫ�޸ĵ����ݣ�");
		printf("���������֣�");
		scanf("%s", pcon->arr[ret].name);
		printf("�������Ա�");
		scanf("%s", pcon->arr[ret].sex);
		printf("���������䣺");
		scanf("%d", &(pcon->arr[ret].age));
		printf("������绰���룺");
		scanf("%s", pcon->arr[ret].tele);
		printf("�������ַ��");
		scanf("%s", pcon->arr[ret].address);
		return 1;
	}
	printf("û���ҵ�������Ҫ�޸ĵ���ϵ�ˡ�\n");
	return 0;
}

//���������ϵ��
void put_empty(struct A *pcon)
{
	printf("�����ϵ��\n");
	memset(pcon->arr, 0, 1000 * sizeof(struct contact));
	pcon->i = 0;
}

//����������������ϵ��

void sort_name(struct A *pcon)
{
	printf("����\n");
	char ch = 0;
	int i = 0;
	int j = 0;
	printf("��ѡ������ʽ����<��������z->a,'>'������a->z��:");
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
		printf("ѡ������뷵������ѡ��\n");
	printf("���������\n");


}


void _init_contact(struct A *pcon)
{
	pcon->i = 0;
	memset(pcon->arr, 0, MAX_SIZE*sizeof(struct contact));


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
