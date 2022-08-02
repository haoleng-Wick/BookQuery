#include "Library.h"
#include "./Login.c"

// KMP字符串匹配算法
int KMP(char *S, char *T)
{
	int next[64] = {0};

	next[2] = 1;
	int i = 2; int j = 1;
	while(i < strlen(T))
	{
		if(j == 0 || T[i-1] == T[j-1]) {
			i++;
			j++;
			if(T[i-1] != T[j-1]) {
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
		if(j == 0 || S[i-1] == T[j-1]) {
			i++;j++;
		} else {
			j = next[j];
		}
	}
	if(j > strlen(T)) {
		return i-(int)strlen(T);
	}
	return -1;
}

// 初始化加载文件
void init_book()
{
	FILE * fp;
	system("clear");
	printf("\n\n\n\n\n");
	printf("\t\t\t\t file loading ,please wait....\n");
	if ( (fp = fopen("./bookbase.txt","rb")) == NULL )
	{
		printf("\t\t\t\t No such file here , so creat it...\n");
		fp = fopen("./bookbase.txt","wb");
		fwrite(&book_cnt,sizeof(book_cnt),1,fp);

		printf("\t\t\t\t creat done!\n");
		fclose(fp);
	}
	fp = fopen("./bookbase.txt","rb");
	fseek(fp, 0, SEEK_SET);
	fread(&book_cnt,sizeof(book_cnt),1,fp);
	fclose(fp);

	printf("\n\n\n\n\n\n\n\n\n\t\t\t\t\t Everything is complete\n");
	system("sleep 1");
}

// 添加新书
void add_book()
{
	system("clear");
	printf("\n\n\n\n\n");

	struct_book book;
	FILE* fp;
	int nmb;

	system("clear");
	printf("\t\t\t\t please intput the number(1~9) of books you will add:\n");
	scanf("%d",&nmb);
	if(nmb <= 0 || nmb >= 10)
	{
		printf("\t\t\t\tInput error number, will return soon!\n");
		while(getchar() != '\n');
		system("sleep 1");
		return;
	} 
	else
	{
		book_cnt += nmb;

		if ( ( fp = fopen("./bookbase.txt","ab")) == NULL )
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
		fp = fopen("./bookbase.txt","rb+");
		fseek(fp, 0, SEEK_SET);
		fwrite(&book_cnt,sizeof(book_cnt),1,fp);
		fclose(fp);
		printf("\t\t\t\t number update, the number now is : %d\n",book_cnt);

		printf("\t\t\t\t Done! will return soon\n");
		while(getchar() != '\n');
		system("sleep 1");
	}
}

// 删除书籍信息
void delete_book()
{
	system("clear");

	FILE * fp;
	struct_book book1,book2;
	int number = book_cnt;
	int i, j, flag = 0;
	if ( ( fp = fopen("./bookbase.txt","rb+")) == NULL )
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
		if(!strcmp(book1.Name,str_name))
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

	if(flag == 1)
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

		system("rm bookbase.txt");
		system("mv tmp.txt bookbase.txt");

		printf("\t\t\tDelete complete, will return soon!\n");
	}
	else
	{
		printf("\t\t\tNo such book here, will return soon!\n");
	}
		while(getchar() != '\n');
		system("sleep 1");
}

// 修改书籍信息
void remake_book()
{
	system("clear");

	FILE * fp;
	struct_book book;
	int number = book_cnt;
	int flag = 0;
	if ( ( fp = fopen("./bookbase.txt","rb+")) == NULL )
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
			printf("\t\t\t\t\t    编号 \t   \t     书名 \t\t  作者 \n");
			printf("\t\t\t\t\t %s \t\t 《%s》 \t\t %s \n", book.No,book.Name,book.Writer);
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
	system("sleep 1");
}

// 查询书籍
void select_book()
{
	system("clear");

	FILE * fp;
	struct_book book;
	int number = book_cnt;
	if ( ( fp = fopen("./bookbase.txt","rb")) == NULL )
	{
		printf("error in func: %s line: %d %s: \n", __func__,__LINE__,strerror(errno));
		exit(EXIT_FAILURE);
	}

	char str_name[30] = {0};
	printf("\t\t\t\t please input the name of the book which you will found: ");
	scanf("%s",str_name);
	
	printf("\t\t\t\t\t    编号 \t   \t     书名 \t\t  作者 \n");
	fseek(fp, (long)sizeof(book_cnt), SEEK_SET);
	while( number-- && (fread(&book,sizeof(struct_book),1,fp)) != 0)
	{
		//if (!strcmp(str_name,book.Name))
		if(KMP(book.Name,str_name) != -1)
			printf("\t\t\t\t\t %s \t\t 《%s》 \t\t %s \n", book.No,book.Name,book.Writer);
	}

	fclose(fp);

	printf("\t\t\t\t press any key to continue!\n");
	getchar();
	while(getchar() != '\n'); 
}

// 列出书籍
void list_book()
{
	system("clear");
	FILE * fp;
	struct_book book;
	int nmb = book_cnt;

	if ( ( fp = fopen("./bookbase.txt","rb")) == NULL )
	{
		printf("error in func: %s line: %d %s: \n", __func__,__LINE__,strerror(errno));
		exit(EXIT_FAILURE);
	}

	fseek(fp, 0, SEEK_SET);
	fread(&book_cnt,sizeof(book_cnt),1,fp);
	printf("\t书籍的总数%d\n",book_cnt);
	printf("\t\t\t\t\t    编号 \t   \t     书名 \t\t  作者 \n");

	fseek(fp, (long)sizeof(book_cnt), SEEK_SET);
	while( nmb-- && (fread(&book,sizeof(struct_book),1,fp) != 0) )
	{
			printf("\t\t\t\t\t %s \t\t 《%s》 \t\t %s \n", book.No,book.Name,book.Writer);
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
		system("clear");
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
				User_login();
				break;
			case 9:
				system("clear");
				exit(0);
			default:
				break;
		}
	}while(choice != 9);
}


// main函数负责调用
int main (void)
{
	if (User_login() == 0)
	{
		book_cnt = 0;
		init_book();
		Welcome();
	}
	system("clear");
	return 0;
}

