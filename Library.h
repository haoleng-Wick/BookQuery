#ifndef _LIBRARY_H_
#define _LIBRARY_H_
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#if defined (__linux__)
	#include <unistd.h>
#elif defined (_WIN32)
	#include <windows.h>
#endif


void wait();
// 用户
typedef struct 
{
	char name[32];
	char passwd[16];
	char major[32];
	char code[8];
} struct_user;

// 图书
typedef struct 
{
	char No[15];
	char Name[30];
	char Writer[30];
} struct_book;

// 登录模块
int load_userdata();
int sigin_up();
int login(struct_user user);
int user_page(struct_user user);
int change_userinfo(struct_user user);
int User_login();

extern struct_user USER;

extern unsigned int book_cnt;

//字符串匹配
int KMP(char *S, char *T);

//图书相关函数
void init_book();
void Welcome();
void add_book();
void delete_book();
void reset_book();
void select_book();
void list_book();

#endif
