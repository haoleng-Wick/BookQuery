#include "Library.h"

// 清屏函数
void clear_screen()
{
#if defined (__linux__)
	system("clear");
#elif defined (_WIN32)
	system("cls");
#endif
}

// 延时函数
void wait()
{
#if defined (__linux__)
	sleep(1);
#elif defined (_WIN32)
	Sleep(1000);
#endif
}

FILE *file;
struct_user USER;

// KMP字符串匹配算法
int KMP(char *S, char *T)
{
	int next[64] = {0};

	next[2] = 1;
	int i = 2; int j = 1;
	while(i < strlen(T))
	{
		if (j == 0 || T[i-1] == T[j-1]) {
			i++;
			j++;
			if (T[i-1] != T[j-1]) {
				next[i] = j;
			} else {
				next[i] = next[j];
			}
		} else {
			j = next[j];
		}
	}

	i = 1; j = 1;
	while(i <= strlen(S) && j <= strlen(T)) {
		if (j == 0 || S[i-1] == T[j-1]) {
			i++;j++;
		} else {
			j = next[j];
		}
	}
	if (j > strlen(T)) {
		return i-(int)strlen(T);
	}
	return -1;
}

// 加载用户文件
// 若没有该文件则创建一个并且注册一个用户
int load_userdata()
{
	file = fopen("./userdata", "rb");
	if (file == NULL)
	{
		printf("No user registered, please sigin up an account.\n");
		sigin_up();
	} else {
		fclose(file);
	}
	return 0;
}

// 用户注册函数
int sigin_up()
{
	clear_screen();
	file = fopen("./userdata", "ab");
	struct_user user;
	printf("\n\n\n\n\n");
	printf("\t\t\t\t\t*************************************\n");

	printf("\t\t\t\t\t     ***       用户注册    ***\n");
	printf("\t\t\t\t\t*************************************\n");

	printf("\t\t\t\tusername: ");	scanf("%s", user.name);
	printf("\n\t\t\t\tpasswd: ");	scanf("%s", user.passwd);
	printf("\n\t\t\t\tmajor: ");	scanf("%s", user.major);
	printf("\n\t\t\t\tcode: ");		scanf("%s", user.code);

	strcpy(USER.name, user.name);
	strcpy(USER.passwd, user.passwd);
	strcpy(USER.major, user.major);
	strcpy(USER.code, user.code);

	fwrite(&user, sizeof(user), 1, file);
	fclose(file);
	printf("done. \n");
	while(getchar() != '\n');
	return 0;
}

// 登录函数
int login(struct_user user)
{
	clear_screen();
	file = fopen("./userdata", "rb");
	struct_user user_data;
	while((fread(&user_data, sizeof(user), 1, file)) != 0)
	{
		if (strcmp(user.name, user_data.name) == 0 
			&& strcmp(user.passwd, user_data.passwd) == 0)
		{
			while(getchar() != '\n');
			strcpy(USER.major, user_data.major);
			strcpy(USER.code, user_data.code);
			printf("\n\n\n\n\n\t\t\tlogin succesfully! Loading...\n");
			wait();
			return user_page(user_data);
		} 
	}
	printf("account or password error!\n");
	fclose(file);
	return 1;
}

// 用户界面
int user_page(struct_user user)
{
	clear_screen();
	printf("\tWelcome \"%s\"\n", user.name);
	printf("Here is your information:\n");
	printf("Name: %s\t", user.name);
	printf("\tMajor: %s\t", user.major);
	printf("\tCode: %s\n", user.code);
	printf("\n\n");
	printf("\t\t\t\t\t*************************************\n");

	printf("\t\t\t\t\t     ***1.       修改      ***\n");
	printf("\t\t\t\t\t     ***2.       退出      ***\n");
	printf("\t\t\t\t\t     ***9.     进入系统    ***\n");
	printf("\t\t\t\t\t*************************************\n");


	int choice = 0;
	char c = getchar();
	choice = c - '0';
	while(getchar() != '\n');

	if (choice == 9)
		return 0;
	else if (choice == 1)
	{
		return change_userinfo(user);
	} else
		return 1;
}

// 修改用户数据
int change_userinfo(struct_user user)
{
	file = fopen("./userdata", "rb+");
	struct_user user_data;
	while((fread(&user_data, sizeof(user), 1, file)) != 0)
	{
		if (!strcmp(user.name, user_data.name))
		{
			printf("Please input the new information:\n");
			fseek(file, (long)-sizeof(user), SEEK_CUR);
			printf("new_username: ");	scanf("%s", user_data.name);
			printf("\nnew_passwd: ");	scanf("%s", user_data.passwd);
			printf("\nnew_major: ");	scanf("%s", user_data.major);
			printf("\nnew_code: ");		scanf("%s", user_data.code);
			
			fwrite(&user_data, sizeof(user_data), 1, file);
			strcpy(USER.name, user_data.name);
			strcpy(USER.passwd, user_data.passwd);
			strcpy(USER.major, user_data.major);
			strcpy(USER.code, user_data.code);
		}
	}
	while(getchar() != '\n');
	fclose(file);
	return 0;
}

// 用户登录注册界面
int User_login()
{
	clear_screen();
	load_userdata();
	clear_screen();
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

	if (choice == 1)	{
		printf("\t\t\t\tUser name: ");
		scanf("%s", USER.name);
		printf("\t\t\t\tpasswd: ");
		scanf("%s", USER.passwd);
		int flag = login(USER);
		return flag;
	} else if (choice == 2) {
		return sigin_up();
	} else if (choice == 9)
		return 1;
	return 1;
}

// 初始化加载文件
void init_book()
{
	FILE * fp;
	clear_screen();
	printf("\n\n\n\n\n");
	printf("\t\t\t\t file loading ,please wait....\n");
	if ( (fp = fopen("./bookbase","rb")) == NULL )
	{
		printf("\t\t\t\t No such file here , so creat it...\n");
		fp = fopen("./bookbase","wb");
		fwrite(&book_cnt,sizeof(book_cnt),1,fp);

		printf("\t\t\t\t creat done!\n");
		fclose(fp);
	}
	fp = fopen("./bookbase","rb");
	fseek(fp, 0, SEEK_SET);
	fread(&book_cnt,sizeof(book_cnt),1,fp);
	fclose(fp);

	printf("\n\n\n\n\n\n\n\n\n\t\t\t\t\t Everything is complete\n");
	wait();
}

// 添加新书
void add_book()
{
	clear_screen();
	printf("\n\n\n\n\n");

	struct_book book;
	FILE* fp;
	int nmb;

	clear_screen();
	printf("\t\t\t\t please intput the number(1~9) of books you will add:\n");
	scanf("%d",&nmb);
	if (nmb <= 0 || nmb >= 10)
	{
		printf("\t\t\t\tInput error number, will return soon!\n");
		while(getchar() != '\n');
		wait();
		return;
	} 
	else
	{
		book_cnt += nmb;

		if ( ( fp = fopen("./bookbase","ab")) == NULL )
		{
			printf("error in func: %s line: %d %s: \n", __func__,__LINE__,strerror(errno));
			exit(EXIT_FAILURE);
		}
		for(int i = 0; i < nmb; i++)
		{
			printf("\t\t\t\t Please input the numbering code of the book%d: ",i+1);
			scanf("%s",book.No);
			printf("\t\t\t\t Please input the name of the book%d: ",i+1);
			scanf("%s",book.Name);
			printf("\t\t\t\t Please input the writer of the book%d: ",i+1);
			scanf("%s",book.Writer);
			fwrite(&book,sizeof(struct_book),1,fp);
		}
		fclose(fp);

		//更新书籍数目
		fp = fopen("./bookbase","rb+");
		fseek(fp, 0, SEEK_SET);
		fwrite(&book_cnt,sizeof(book_cnt),1,fp);
		fclose(fp);
		printf("\t\t\t\t number update, the number now is : %d\n",book_cnt);

		printf("\t\t\t\t Done! will return soon\n");
		while(getchar() != '\n');
		wait();
	}
}

// 删除书籍信息
void delete_book()
{
	clear_screen();

	FILE * fp;
	struct_book book1,book2;
	int number = book_cnt;
	int i, j, flag = 0;
	if ( ( fp = fopen("./bookbase","rb+")) == NULL )
	{
		printf("error in func: %s line: %d %s: \n", __func__,__LINE__,strerror(errno));
		exit(EXIT_FAILURE);
	}

	char str_name[30] = {0};
	printf("\t\t\t\t please input the name of the book which you will delete: ");
	scanf("%s",str_name);
	
	fseek(fp, (long)sizeof(book_cnt), SEEK_SET);
	for (i = 0; i < number; i++)
	{
		fread(&book1,sizeof(struct_book),1,fp);
		if (!strcmp(book1.Name,str_name))
		{
			flag = 1;
			//将后面的书籍信息前移
			for(j = i; j < number-1; j++)
			{
				fread(&book2,sizeof(struct_book),1,fp);
				strcpy(book1.No,book2.No);
				strcpy(book1.Name,book2.Name);
				strcpy(book1.Writer,book2.Writer);
				fseek(fp, (long)-2*sizeof(struct_book), SEEK_CUR);
				fwrite(&book1,sizeof(struct_book),1,fp);
				fseek(fp, (long)sizeof(struct_book), SEEK_CUR);
			}

			book_cnt--;
			fseek(fp, 0, SEEK_SET);
			fwrite(&book_cnt,sizeof(book_cnt),1,fp);
			printf("\t\t\t\t books\' information and number has updated, the number now is : %d\n",book_cnt);

			break;
		}
	}

	if (flag == 1)
	{
		FILE * n_fp;
		n_fp = fopen("./tmp.txt","wb");
		fseek(fp, 0, SEEK_SET);
		fread(&j,sizeof(j),1,fp);
		fwrite(&j,sizeof(j),1,n_fp);
		for(i = 0; i < book_cnt; i++)
		{
			fread(&book1,sizeof(struct_book),1,fp);
			fwrite(&book1,sizeof(struct_book),1,n_fp);
		}

		fclose(n_fp);
		fclose(fp);

		system("rm bookbase");
		system("mv tmp.txt bookbase");

		printf("\t\t\tDelete complete, will return soon!\n");
	}
	else
	{
		printf("\t\t\tNo such book here, will return soon!\n");
	}
		while(getchar() != '\n');
	wait();
}

// 修改书籍信息
void remake_book()
{
	clear_screen();

	FILE * fp;
	struct_book book;
	int number = book_cnt;
	int flag = 0;
	if ( ( fp = fopen("./bookbase","rb+")) == NULL )
	{
		printf("error in func: %s line: %d %s: \n", __func__,__LINE__,strerror(errno));
		exit(EXIT_FAILURE);
	}

	char str_name[30] = {0};
	printf("\t\t\t\t please input the name of the book that you will update: ");
	scanf("%s",str_name);
	
	fseek(fp, (long)sizeof(book_cnt), SEEK_SET);
	while(number-- && (fread(&book,sizeof(struct_book),1,fp)) != 0)
	{
		if (!strcmp(str_name,book.Name))
		{
			flag = 1;
			printf("\t\t\t\t the book\'s information is listed :\n");
			printf("\t\t\t\t\t编号\t\t\t\t书名\t\t\t\t作者\n");
			printf("\t\t\t\t\t %s \t\t\t《%s》\t\t\t %s\n", book.No,book.Name,book.Writer);
			printf("\t\t\t\t Please input the new numbering code of the book: ");
			scanf("%s",book.No);
			printf("\t\t\t\t Please input the new name of the book: ");
			scanf("%s",book.Name);
			printf("\t\t\t\t Please input the new writer of the book: ");
			scanf("%s",book.Writer);

			fseek(fp, (long)-sizeof(struct_book), SEEK_CUR);
			fwrite(&book,sizeof(struct_book),1,fp);
		}
	}

	fclose(fp);
	if (flag == 1)
		printf("\t\t\tRemake complete, will return soon!\n");
	else
		printf("\t\t\tNo such book here, will return soon!\n");

	while(getchar() != '\n');
	wait();
}

// 查询书籍
void select_book()
{
	clear_screen();

	FILE * fp;
	struct_book book;
	int number = book_cnt;
	if ( ( fp = fopen("./bookbase","rb")) == NULL )
	{
		printf("error in func: %s line: %d %s: \n", __func__,__LINE__,strerror(errno));
		exit(EXIT_FAILURE);
	}

	char str_name[30] = {0};
	printf("\t\t\t\t please input the name of the book which you will found: ");
	scanf("%s",str_name);
	
	printf("\t\t\t\t\t编号\t\t\t\t书名\t\t\t\t作者\n");
	fseek(fp, (long)sizeof(book_cnt), SEEK_SET);
	while( number-- && (fread(&book,sizeof(struct_book),1,fp)) != 0)
	{
		//if (!strcmp(str_name,book.Name))
		if (KMP(book.Name,str_name) != -1)
			printf("\t\t\t\t\t %s \t\t\t《%s》\t\t\t %s\n", book.No,book.Name,book.Writer);
	}

	fclose(fp);

	printf("\t\t\t\t press any key to continue!\n");
	getchar();
	while(getchar() != '\n'); 
}

// 列出书籍
void list_book()
{
	clear_screen();
	FILE * fp;
	struct_book book;
	int nmb = book_cnt;

	if ( ( fp = fopen("./bookbase","rb")) == NULL )
	{
		printf("error in func: %s line: %d %s: \n", __func__,__LINE__,strerror(errno));
		exit(EXIT_FAILURE);
	}

	fseek(fp, 0, SEEK_SET);
	fread(&book_cnt,sizeof(book_cnt),1,fp);
	printf("\t书籍的总数%d\n",book_cnt);
	printf("\t\t\t\t\t编号\t\t\t\t书名\t\t\t\t作者\n");

	fseek(fp, (long)sizeof(book_cnt), SEEK_SET);
	while( nmb-- && (fread(&book,sizeof(struct_book),1,fp) != 0) )
	{
			printf("\t\t\t\t\t %s \t\t\t《%s》\t\t\t %s\n", book.No,book.Name,book.Writer);
	}
	fclose(fp);

	printf("\tpress any key to continue\n");
	getchar();
	while(getchar() != '\n'); 
}

// 主界面 由while循环控制刷新
void Welcome()
{
	int choice = 0;
	int count = 0;
	do{
		count++;
		clear_screen();
		printf("\n\n\n\n\n\t\t\t\t\t   Library Books Management System\n");
		printf("\t\t\t\t\t*************************************\n");

		printf("\t\t\t\t\t     ***1.为书库添加一些新书 ***\n");
		printf("\t\t\t\t\t     ***2.删除书库中现有的书 ***\n");
		printf("\t\t\t\t\t     ***3.修改库中书籍的信息 ***\n");
		printf("\t\t\t\t\t     ***4.查询书库中的某书籍 ***\n");
		printf("\t\t\t\t\t     ***5.列出书库中所有书籍 ***\n");
		printf("\t\t\t\t\t     ***6.     用户中心      ***\n");
		printf("\t\t\t\t\t     ***9.     退出系统      ***\n");
		printf("\t\t\t\t\t*************************************\n");

		//只从输入缓冲区提取第一个字符并将其转化为int型
		//然后清除之后输入缓冲区的字符
		char c = getchar();
		choice = c - '0';
		while(getchar() != '\n');

		switch(choice)
		{
			case 1:
				add_book();
				break;
			case 2:
				delete_book();
				break;
			case 3:
				remake_book();
				break;
			case 4:
				select_book();
				break;
			case 5:
				list_book();
				break;
			case 6:
				user_page(USER);
				break;
			case 9:
				clear_screen();
				exit(0);
			default:
				break;
		}
	}while(choice != 9);
}


// main函数负责调用
int main ()
{
	if (User_login() == 0)
	{
		book_cnt = 0;
		init_book();
		Welcome();
	}
	clear_screen();
	return 0;
}

