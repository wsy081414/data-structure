#define _CRT_SECURE_NO_WARNINGS 1


#ifndef __CONTACT_TEXT_3_H__
#define __CONTACT_TEXT_3_H__

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

#define NAME_MAX 20
#define  SEX_MAX 5
#define TELE_MAX 20
#define ADD_MAX 50
#define FILENAME "contact.dat"


#define INIT_NUM 3//初始大小
#define INC_NUM 2//每次扩容大小
struct contact
{
	char name[NAME_MAX];
	char sex[SEX_MAX];
	int age;
	char tele[TELE_MAX];
	char address[ADD_MAX];
};

struct A
{
	struct contact *arr;
	int i;
	int capacity;
};


enum op
{
	EXIT,
	ADD,
	DEL,
	SEARCH,
	MODIFY,
	DISPLAY,
	CLEAR,
	SORT
};


void Add(struct A *con);

void print_contact(struct A *con);

int find_position(struct A *pcon);

int delete_contact(struct A *pcon);

int find_contacts(struct A *pcon);

int revise_contact(struct A *pcon);

void put_empty(struct A *pcon);

void sort_name(struct A *pcon);

void _init_contact(struct A *pcon);

void print_menu();

void load(struct A *pcon);

void save(struct A *pcon);

#endif //!__CONTACT_TEXT_3_H__