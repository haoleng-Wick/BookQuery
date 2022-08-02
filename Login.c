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


int init_userdata()
{
	file = fopen("./userdata", "rb");
	if(file == NULL)
	{
		printf("No user registered, please sigin up an account.\n");
		sigin_up();
	}
	fclose(file);
	return 0;
}

int sigin_up()
{
	file = fopen("./userdata", "ab");
	User user;
	printf("\n\n\n\n\n");
	printf("\t\t\t\t\t*************************************\n");

	printf("\t\t\t\t\t     ***       用户注册    ***\n");
	printf("\t\t\t\t\t*************************************\n");

	printf("\t\t\t\tusername: ");	scanf("%s", user.name);
	printf("\n\t\t\t\tpasswd: ");	scanf("%s", user.passwd);
	printf("\n\t\t\t\tmajor: ");	scanf("%s", user.major);
	printf("\n\t\t\t\tcode: ");		scanf("%s", user.code);

	fwrite(&user, sizeof(user), 1, file);
	fclose(file);
	printf("done. \n");
	while(getchar() != '\n');
	return 0;
}

void change_userinfo(User user)
{
	file = fopen("./userdata", "rb+");
	User user_data;
	while((fread(&user_data, sizeof(user), 1, file)) != 0)
	{
		if(!strcmp(user.name, user_data.name))
		{
			printf("Please input the new information:\n");
			fseek(file, (long)-sizeof(user), SEEK_CUR);
			printf("new_username: ");	scanf("%s", user_data.name);
			printf("\nnew_passwd: ");	scanf("%s", user_data.passwd);
			printf("\nnew_major: ");	scanf("%s", user_data.major);
			printf("\nnew_code: ");		scanf("%s", user_data.code);
			
			fwrite(&user_data, sizeof(user_data), 1, file);
		}
	}
	while(getchar() != '\n');
	fclose(file);
}

int login(User user)
{
	system("clear");
	file = fopen("./userdata", "rb");
	User user_data;
	while((fread(&user_data, sizeof(user), 1, file)) != 0)
	{
		if(strcmp(user.name, user_data.name) == 0 && strcmp(user.passwd, user_data.passwd) == 0)
		{
			printf("login succesfully!\t");
			printf("\tWelcome %s\n", user_data.name);
			printf("Here is your information:\n");
			printf("Name: %s\t", user_data.name);
			printf("Major: %s\t", user_data.major);
			printf("Code: %s\n", user_data.code);
			printf("\n\n");
			printf("\t\t\t\t\t*************************************\n");

			printf("\t\t\t\t\t     ***1.       修改      ***\n");
			printf("\t\t\t\t\t     ***2.       退出      ***\n");
			printf("\t\t\t\t\t     ***0.     进入系统    ***\n");
			printf("\t\t\t\t\t*************************************\n");

			while(getchar() != '\n');

			int choice = 0;
			char c = getchar();
			choice = c - '0';
			while(getchar() != '\n');
//			printf("choice = %d\n", choice);
//			system("sleep 1");

			if(choice == 0)
				return 0;
			else if(choice == 1)
			{
				change_userinfo(user);
				return 1;
			} else
				return 1;
		} 
	}
	printf("account or password error!\n");
	fclose(file);
	return 1;
}

int User_login()
{
	system("clear");
	init_userdata();
	User user;
		printf("\t\t\t\t\t     ***       用户中心    ***\n");
		printf("\t\t\t\t\t*************************************\n");

		printf("\t\t\t\t\t     ***1.       登录      ***\n");
		printf("\t\t\t\t\t     ***2.       注册      ***\n");
		printf("\t\t\t\t\t     ***9.       退出      ***\n");
		printf("\t\t\t\t\t*************************************\n");

	int choice = 0;
	char c = getchar();
	choice = c - '0';
	while(getchar() != '\n');

	if(choice == 1)	{
		printf("\tUser name: ");
		scanf("%s", user.name);
		printf("\tpasswd: ");
		scanf("%s", user.passwd);
		int flag = login(user);
		printf("flag = %d\n", flag);
		system("sleep 1");
		return flag;
	} else if(choice == 2) {
		return sigin_up();
	} else if(choice == 9)
		return 1;
	return 1;
}
