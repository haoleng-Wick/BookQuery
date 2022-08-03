#ifndef _LIBRARY_H_
#define _LIBRARY_H_
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

// 用户
typedef struct User {
	char name[32];
	char passwd[16];
	char major[32];
	char code[8];
}User;

// 图书
typedef struct 
{
	char No[15];
	char Name[30];
	char Writer[30];
}struct_book;

// 登录模块
int load_userdata();
int sigin_up();
int login(User user);
int user_page(User user);
int change_userinfo(User user);
int User_login();

extern User USER;

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

