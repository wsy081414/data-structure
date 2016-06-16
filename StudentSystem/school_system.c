#define _CRT_SECURE_NO_WARNINGS 1


#include"school_system.h"


void printf_menu()
{
	printf("**********************************************\n");
	printf("****  1.CREATE           2.FINDALLCHILD   ****\n");
	printf("****  3.FINDPARENT       4.FINDPERSON     ****\n");
	printf("****  5.FINDCOLLEGE      6.INIT           ****\n");
	printf("****  0.QUIT             7.SHOW           ****\n");
	printf("**********************************************\n");
}



void Quit()
{

	exit(EXIT_FAILURE);
}

//void InitTree(BITREE root)
//{
//	root->n = NULL;
//	printf("初始化成功\n");
//}
BITREE CreateTRee()
{
	char infor[MAX_SIZE] = { 0 };
	BITREE root;
	printf("请输入节点的信息：");
	scanf("%s", infor);
	fflush(stdin);
	if (strcmp(infor, "#")==0)
	{
		root = NULL;
	}
	else
	{
		root = (BITREE)malloc(sizeof(BITNODE));
		if (root == NULL)
		{
			printf("out of memory");
			exit(EXIT_FAILURE);
		}
		(root)->prev = NULL;
		strcpy((root)->data, infor);
		root->next=CreateTRee();
		if ((root)->next)
			(root)->next->prev = (root);
		root->child=CreateTRee();
		if ((root)->child)
			(root)->child->prev = (root);
	}
	return root;
}

BITREE find(BITREE root, char *FindAllchile)
{
	BITREE p = NULL;
	p = root;
 	assert(root);
	if (strcmp(FindAllchile, p->data) == 0)
		return p;
	if (root->next != NULL)
	{
		p = find(root->next, FindAllchile);
		if (p != NULL)
			return p;
	}
	if (root->child != NULL)
	{
		p = find(root->child, FindAllchile);
		if (p != NULL)
			return p;
	}
	return NULL;
}

void FindAllCHild(BITREE root)
{
	if (root == NULL)
	{
		printf("TREE IS EMPTY !!\n");
		return;
	}
	BITREE cur = NULL;
	char FindAllchile[MAX_SIZE] = { 0 };
	printf("请输入你所要查找的节点信息：");
	scanf("%s", FindAllchile);
	fflush(stdin);
	cur = find(root, FindAllchile);
	if (cur != NULL)
	{
		printf("下属单位：\n");
		pretraversal_binary_tree(cur->child);
		return;
	}
	printf("无匹配信息！");
	
}

void View_superior(BITREE node, char *FindAllchile)
{
	
	if (node != NULL)
	{
		
		if (node->next != NULL)
		{ 
			if (strcmp(node->data, FindAllchile) == 0)
				return;
			if (node->prev!=NULL)
				printf("%s\n", node->data);
			pretraversal_binary_tree(node->next);
		}
		if (node->child != NULL)
			pretraversal_binary_tree(node->child);
	}
}

void FindParent(BITREE root)
{
	if (root == NULL)
	{
		printf("tree is empty !!");
		return;
	}
	BITREE cur = NULL;
	BITREE p = NULL;
	char findparent[MAX_SIZE] = { 0 };
	printf("请输入一个节点的名称：\n");
	scanf("%s", findparent);
	fflush(stdin);
	cur = find(root, findparent);
	p = cur;
	if (cur != NULL)
	{
		printf("上级单位：\n");
		while (p->prev->next == p)
		{
			p = p->prev;
		}
		
		printf("%s\n", p->prev->data);
	}
	else
		printf("无匹配信息！");
}

void FindPerson(BITREE root)
{
	char findteacher[MAX_SIZE] = { 0 };
	BITREE cur = NULL;
	BITREE p = NULL;
	if (root == NULL)
	{
		printf("tree is empty !!");
		return;
	}
	
	printf("请输入一个教师的名称：");
	scanf("%s", findteacher);
	fflush(stdin);
	cur = find(root, findteacher);
	p = cur;
	if (cur != NULL)
	{
		printf("上级单位：\n");
		while (p->prev->next == p)
		{
			p = p->prev;
		}

		printf("%s在%s任职\n", findteacher, p->prev->data);
	}
	else
		printf("无匹配信息！");
}

void FindCollege(BITREE root)
{
	if (root == NULL)
	{
		printf("tree is empty !!");
		return;
	}
	BITREE cur = NULL;
	char findcollege[MAX_SIZE] = { 0 };
	printf("请输入一个院系或者专业：");
	scanf("%s", findcollege);
	fflush(stdin);
	cur = find(root, findcollege);
	if (cur != NULL)
	{
		printf("%s存在%s这一级单位!\n", root->data, findcollege);
		
	}
	else
	{
		printf("%s不存在%s这一级单位！！!\n", root->data, FindCollege);
	}
}



void pretraversal_binary_tree(BITREE node)//先序进行遍历
{
	if (node != NULL)
	{
		printf("%s\n", (node)->data);
	
		pretraversal_binary_tree(node->next);
		
		pretraversal_binary_tree(node->child);
	}
}

void intraversal_binary_tree(BITREE node)//中序进行遍历
{

	if (node != NULL)
	{
	
		intraversal_binary_tree(node->next);

		printf("%s\n", node->data);
		
		intraversal_binary_tree(node->child);
	}
}

void postraversal_binary_tree(BITREE node)//后序进行遍历
{
	if (node != NULL)
	{
		
		postraversal_binary_tree(node->next);
	
		postraversal_binary_tree(node->child);

		printf("%s\n", node->data);
	}
}