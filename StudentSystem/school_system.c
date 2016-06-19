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
	
	exit(0);
}
void BTreeSetNull(BITREE tree)
{
	 if (tree == NULL)
	 {	
		 return;
	 }
	BTreeSetNull(tree->child);
	BTreeSetNull(tree->next);
	free(tree);
}

BITREE CreateTRee()
{
	char infor[MAX_INF] = { 0 };
	char name[MAX_INF] = { 0 };
	BITREE root;
	printf("请输入节点的名字：");
	scanf("%s", name);
	fflush(stdin);
	printf("请输入节点的内容：");
	scanf("%s", infor);
	printf("下一个节点：\n");
	fflush(stdin);
	if (strcmp(name, "#")==0)
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
		strcpy((root)->data, name);
		strcpy((root)->infor, infor);
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
	
	BITREE cur = NULL;
	char FindAllchile[MAX_SIZE] = { 0 };
	if (root == NULL)
	{
		printf("TREE IS EMPTY !!\n");
		return;
	}
	printf("请输入你所要查找的节点名字：");
	scanf("%s", FindAllchile);
	fflush(stdin);
	cur = find(root, FindAllchile);
	if (cur != NULL)
	{
		printf("下属单位：\n");
		pretraversal_binary_tree(cur->child);
		return;
	}
	printf("无匹配信息！\n");
	
}



void FindParent(BITREE root)
{
	if (root == NULL)
	{
		printf("tree is empty !!\n");
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
		
		printf("节点信息为：%s\n", p->prev->data);
		printf("节点内容为：%s\n", p->prev->infor);
	}
	else
		printf("无匹配信息！\n");
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
		printf("当前你所查找的节点内容为：%s\n", cur->infor);
		
		
		while (p->prev->next == p)
		{
			p = p->prev;
		}

		printf("%s在%s任职\n", findteacher, p->prev->data);
		printf("上级单位%s信息为：%s\n", p->prev->data,p->prev->infor);
	}
	else
		printf("无匹配信息！\n");
}

void FindCollege(BITREE root)
{

	BITREE cur = NULL;
	char findcollege[MAX_SIZE] = { 0 };
	if (root == NULL)
	{
		printf("tree is empty !!");
		return;
	}
	printf("请输入一个院系或者专业：");
	scanf("%s", findcollege);
	fflush(stdin);
	cur = find(root, findcollege);
	if (cur != NULL)
	{
		printf("%s存在%s这一级单位!\n", root->data, findcollege);
		printf("学院下属信息：\n");
		pretraversal_binary_tree(cur->child);
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
		printf("单位名称为：%s\n", node->data);
		printf("单位信息为：%s\n", node->infor);
	
		pretraversal_binary_tree(node->next);
		
		pretraversal_binary_tree(node->child);
	}
}

void intraversal_binary_tree(BITREE node)//中序进行遍历
{

	if (node != NULL)
	{
	
		intraversal_binary_tree(node->next);

		printf("单位名称为：%s\n", node->data);
		printf("单位信息为：%s\n", node->infor);
		
		intraversal_binary_tree(node->child);
	}
}

void postraversal_binary_tree(BITREE node)//后序进行遍历
{
	if (node != NULL)
	{
		
		postraversal_binary_tree(node->next);
	
		postraversal_binary_tree(node->child);
		
		printf("单位名称为：%s\n", node->data);
		
		printf("单位信息为：%s\n", node->infor);
	}
}