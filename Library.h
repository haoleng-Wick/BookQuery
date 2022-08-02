#ifndef _LIBRARY_H_
#define _LIBRARY_H_
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

typedef struct 
{
	char No[15];
	char Name[30];
	char Writer[30];
}struct_book;

unsigned int book_cnt;

//字符串匹配
int KMP(char *S, char *T);

//图书相关函数
void init_book();
void Welcome();
void add_book();
void delete_book();
void remake_book();
void select_book();
void list_book();

#endif

