#include <stdio.h>

int what()
{
	int choice = 0;
	char c = getchar();
	choice = c - '0';
	while (1)
	{
		if(choice == 1)
			return 1;
		else if(choice == 2)
			return 2;
		else
			return 0;
	}

	return 0;
}

int main ()
{
	printf("what = %d", what());
	return 0;
}
