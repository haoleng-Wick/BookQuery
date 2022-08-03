#ifndef _LOGIN_H_
#define _LOGIN_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *file;

typedef struct User {
	char name[32];
	char passwd[16];
	char major[32];
	char code[8];
}User;

int init_userdata();
int login(User user);
int sigin_up();
int User_login();

extern User user;

#endif
