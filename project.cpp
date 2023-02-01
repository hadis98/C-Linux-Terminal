#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <process.h>
#include <dir.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>
#include <sys/stat.h>
struct user
{
	char name[100];
	char username[100];
	char passwd[100];
	int strength;
	int access;
	int mistakes;
	char time[10];
} s[1000], x, presentuser;
void hello();
int pwd();
int list();
int enter();
void makedir(char dirname[]);
int strength_pass(char pass[]);
void creatfile(char name[]);
void wc(char name[]);
void cat(char name[]);
void createuser(char name[]);
void diff(char name1[], char name2[]);
void printdir(struct user presentuser);
void copy(char name[], char name2[]);
void move(char name[], char name2[]);
void operand(char name1[], char name2[]);
void operand2(char name1[], char name2[]);
void increse(char username[]);
void su(char username[]);
void intro();
void intromkdir();
void help();
void update();
void showtime();
void showtime2();
void level();
void pass(char p[]);
void pass2();
void printFileProperties(struct stat stats);
void exif(char name[]);
void show(char name[]);
void hide(char name[]);
void search(char name[]);
void search2(char name[]);
void setcolor(int colorcode)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, colorcode % 255);
}
void Cyan()
{
	printf("\033[0;36m");
}
void Boldcyan()
{
	printf("\033[1;36m");
}
void boldred()
{
	printf("\033[1;31m");
}

int z, levelofaccess = 1, numberofusers = 0, currentuser = 0;
int main() // main
{
	char username[100];
	char password[100];
	hello();
	Boldcyan();
	printf("\n\n\n\t\t\tPLEASE ENTER YOUR USERNAME: ");
	gets(username);
	Boldcyan(); // please enter your password:
	printf("\n\n\n\t\t\tPLEASE ENTER YOUR PASSWORD: ");
	gets(password);
	FILE *fptr = fopen("usersinfo.txt", "rb");
	struct user x;
	fread(&x, sizeof(struct user), 1, fptr);
	s[numberofusers] = x;
	presentuser = x;
	if (strcmp(password, x.passwd) == 0 && strcmp(username, x.username) == 0)
	{

		Cyan();
		printf("\n\n\n\n\t\t\t\t\tWELCOME USER %s", username);
		getchar();
	}
	else // permission denied..
	{
		boldred();
		printf("PERMISSION DENIED:(\n");
		do
		{ // try again to enter
			boldred();
			printf("\n\nTRY AGAIN TO ENTER:)\n");
			Boldcyan();
			printf("\n\n\n\t\t\tPLEASE ENTER YOUR USERNAME: ");
			gets(username);
			Boldcyan();
			printf("\n\n\n\t\t\tPLEASE ENTER YOUR PASSWORD: ");
			gets(password);

		} while (strcmp(password, x.passwd) != 0 || strcmp(username, x.username) != 0);

		Cyan();
		printf("\n\n\n\n\t\t\t\t\t\\WELCOME USER %s", x.username);
		getchar();
	}
	system("cls");
	char s[1000];
	while (1)
	{
		printdir(presentuser);
		scanf("%s", s);
		if (strcmp(s, "ls") == 0)
		{
			setcolor(11);
			system("dir /b");
			printf("\n");
		}
		else if (strcmp(s, "mkdir") == 0)
		{
			char name[100];

			getchar();
			gets(name);

			CreateDirectory(name, NULL);
			setcolor(12);
			printf("Directory created");
			printf("\n");
		}
		else if (strcmp(s, "EXIT") == 0)
		{
			getchar();
			system("cls");
			boldred();
			printf("END OF PROGRAM..\nGOOD BYE:)");
			break;
		}
		else if (strcmp(s, "pwd") == 0)
		{
			setcolor(12);
			pwd();
			printf("\n");
		}
		else if (strcmp(s, "chgr") == 0)
		{
			char name[100];
			scanf("%s", name);
			increse(name);
		}
		else if (strcmp(s, "create") == 0)
		{
			char *name;
			name = (char *)malloc(sizeof(char));
			scanf("%s", name);
			if (levelofaccess == 1)
			{
				createuser(name);
				printf("\n");
			}
			else
			{
				boldred();
				printf("permission denied\n");
			}
		}
		else if (strcmp(s, "su") == 0)
		{
			char name[100];
			scanf("%s", name);
			getchar();
			su(name);
		}
		else if (strcmp(s, "diff") == 0)
		{
			char name3[100];
			char name4[100];
			scanf("%s%s", name3, name4);
			//	diff(name3,name4);

			char temp[100] = "fc ";
			strcat(temp, name3);
			strcat(temp, " ");
			strcat(temp, name4);
			system(temp);

			printf("\n");
		}
		else if (strcmp(s, "cd") == 0)
		{
			char name[1000]; // name=address
			getchar();
			gets(name);
			chdir(name);
			printf("\n");
		}
		else if (strcmp(s, "cat") == 0)
		{
			char name[1000];
			scanf("%s", name);
			cat(name);
			printf("\n");
		}
		else if (strcmp(s, "wc") == 0)
		{
			char name[1000];
			scanf("%s", name);
			wc(name);
			printf("\n");
		}
		else if (strcmp(s, "rm") == 0)
		{
			char name[100];
			scanf("%s", name);
			if (remove(name) == 0)
			{
				setcolor(12);
				printf("deleted successfully\n");
			}
			else
			{
				boldred();
				printf("file cannot be deleted or doesnt exist\n");
			}
		}
		else if (strcmp(s, "rm-r") == 0)
		{
			char name[100];
			scanf("%s", name);
			if (rmdir(name) == 0)
			{
				setcolor(12);
				printf("deleted successfully\n");
			}
			else
			{
				boldred();
				printf("directory cannot be deleted or doesnt exist\n");
			}
		}
		else if (strcmp(s, "cp") == 0)
		{
			char name1[100];
			char name2[100];
			scanf("%s%s", name1, name2);
			copy(name1, name2);
			printf("\n");
		}
		else if (strcmp(s, "mv") == 0)
		{
			char name1[100];
			char name2[100];
			scanf("%s%s", name1, name2);
			move(name1, name2);
			printf("\n");
		}
		/*
		else if(strcmp(s,"myeditor")==0)
		{
			myeditor();
		}
		*/
		else if (strcmp(s, "help") == 0)
			help();

		else if (strcmp(s, "time") == 0)
			showtime();
		else if (strcmp(s, "time-a") == 0)
			showtime2();
		else if (strcmp(s, "level") == 0)
			level();
		else if (strcmp(s, "passwd") == 0)
		{
			char p[100];
			getchar();
			setcolor(9);
			printf("please enter your current password: ");
			gets(p);
			pass(p);
		}
		else if (strcmp(s, "passwd-l") == 0)
		{
			getchar();
			if (levelofaccess == 1)
				pass2();
			else
			{
				boldred();
				printf("permission denied:(\n");
			}
		}
		else if (strcmp(s, "hide") == 0)
		{
			getchar();
			char name[100];
			gets(name);
			hide(name);
		}
		else if (strcmp(s, "hide-r") == 0)
		{
			getchar();
			char name[100];
			gets(name);
			show(name);
		}
		else if (strcmp(s, "exif") == 0)
		{
			getchar();
			char name[100];
			gets(name);
			exif(name);
			printf("\n");
		}
		else if (strcmp(s, "search") == 0)
		{
			getchar();
			char name[100];
			gets(name);
			FILE *fptr = fopen(name, "rb");
			if (fptr == NULL)
			{
				search2(name);
				fclose(fptr);
			}
			else
				search(name);
		}

		else
		{
			char s2[3];
			scanf("%s", s2);
			if (strcmp(s2, ">>") == 0)
			{
				char name[100];
				scanf("%s", name);
				operand2(s, name);
			}
			else if (strcmp(s2, ">") == 0)
			{
				char name[100];
				scanf("%s", name);
				operand(s, name);
			}
			else
			{
				boldred();
				printf("incorrect command\n");
				presentuser.mistakes++;
				update();
			}
		}
	}

	return 0;
}
void hello()
{
	setcolor(11);
	printf("\n\n\n\n\n\n\n\n\t\t\t\t\t**********************************\n");
	printf("\t\t\t\t\t\t******************\n");
	printf("\t\t\t\t\t\tWELCOME \n\t\t\t\t\t\tTO\n\t\t\t\t\t        MY TERMINAL:)   \n\t\t\t\t\t\tHOPE TO ENGOY\n");
	printf("\t\t\t\t\t\t******************\n");
	printf("\t\t\t\t\t**********************************\n\n\n\n");
	printf("\t\t\tpress EXIT to close the terminal\n\t\t\tpress help to see a introduction of commands\n");
	printf("\t\t\tpress the enter key");
	getchar();
	system("cls");
}

int pwd()
{
	char cwd[PATH_MAX];
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		setcolor(11);
		printf("\nCurrent working dir: %s\n", cwd);
		return 0;
	}
	else
	{
		perror("getcwd() error");
		return 1;
	}
}

void makedir(char dirname[])
{
	int check;
	check = mkdir(dirname);
	if (!check)
		return;
	else
	{
		boldred();
		printf("Unable to create directory:(\n");
		exit(1);
	}
}
void increse(char username[])
{
	int i, j;
	char cwd[PATH_MAX];
	getcwd(cwd, sizeof(cwd));
	char now[1000];
	strcpy(now, cwd);
	chdir("C:/Users/Win 10/Desktop/root/hadis80/");
	FILE *fptr = fopen("usersinfo.txt", "wb");
	for (j = 0; j < numberofusers + 1; j++)
	{
		fwrite(&s[j], sizeof(struct user), 1, fptr);
	}
	fclose(fptr);
	fptr = fopen("usersinfo.txt", "rb");

	if (levelofaccess == 1) // presentuser.access==1
	{
		for (i = 0; i < numberofusers + 1; i++)
		{
			fread(&s[i], sizeof(struct user), 1, fptr);
			if (strcmp(s[i].username, username) == 0)
			{
				if (s[i].access == 0 && s[i].mistakes < 11 && s[i].strength > 75)
				{
					s[i].access = 1;
					levelofaccess = 1;
					setcolor(11);
					printf("user with %s  username became admin:)\n", s[i].username);
					fclose(fptr);
					fptr = fopen("usersinfo.txt", "wb");
					for (i = 0; i < numberofusers + 1; i++)
					{
						fwrite(&s[i], sizeof(struct user), 1, fptr);
					}
					fclose(fptr);
					chdir(now);
					return;
				}
			}
		}
		if (i == numberofusers + 1)
		{
			setcolor(12);
			printf("user %s cannot be admin:(\n", username);
			fclose(fptr);
			chdir(now);
			return;
		}
	}
	else
	{
		setcolor(12);
		printf("permission denied:(\n");
	}
	fclose(fptr);
	chdir(now);
	return;
}
void su(char username[100])
{
	char cwd[PATH_MAX];
	getcwd(cwd, sizeof(cwd));
	char now2[1000];
	strcpy(now2, cwd);
	chdir("C:/Users/Win 10/Desktop/root/hadis80/");
	char time3[100], pass[100];
	time_t now;
	struct tm *ts;
	now = time(NULL);
	ts = localtime(&now);
	setcolor(10);
	strftime(time3, sizeof(time3), "%Y/%m/%d %H:%M:%S", ts); // time now
	FILE *fptr = fopen("usersinfo.txt", "wb");
	for (int j = 0; j < numberofusers + 1; j++)
	{
		fwrite(&s[j], sizeof(struct user), 1, fptr);
	}
	fclose(fptr);
	fptr = fopen("usersinfo.txt", "rb");
	int i;
	if (levelofaccess == 1)
	{
		for (i = 0; i < numberofusers + 1; i++)
		{
			fread(&s[i], sizeof(struct user), 1, fptr);
			if (strcmp(s[i].username, username) == 0)
			{
				if (strcmp(s[i].time, time3) <= 0)
				{
					setcolor(12);
					printf("the time for user %s has finished:(\nso suer %s cannot access to terminal any more:(\n", username, username);
					fclose(fptr);
					chdir(now2);
					return;
				}
				levelofaccess = s[i].access;
				presentuser = s[i];
				break;
			}
		}
		if (i == numberofusers + 1)
		{
			setcolor(12);
			printf("permission denied:(\n");
		}
		else
		{

			char add[1000] = "C:/Users/Win 10/Desktop/root/";
			strcat(add, username);

			setcolor(9);
			printf("WELCOME %s USER:)", username);
			chdir(add);
			getchar();
			system("cls");
		}
	}
	else
	{
		setcolor(11);
		printf("\nuser %s please enter your pass: ", username);
		gets(pass);
		for (i = 0; i < numberofusers + 1; i++)
		{
			fread(&s[i], sizeof(struct user), 1, fptr);
			if (strcmp(s[i].username, username) == 0 && strcmp(s[i].passwd, pass) == 0)
			{
				if (strcmp(s[i].time, time3) <= 0)
				{
					setcolor(12);
					printf("the time for user %s has finished:(\nso suer %s cannot access to terminal any more:(\n", username, username);
					fclose(fptr);
					chdir(now2);
					return;
				}
				levelofaccess = s[i].access;
				presentuser = s[i];
				break;
			}
		}
		if (i == numberofusers + 1)
		{
			setcolor(12);
			printf("permission denied:(\n");
			fclose(fptr);
			chdir(now2);
			return;
		}
		else
		{

			char add[1000] = "C:/Users/Win 10/Desktop/root/";
			strcat(add, username);
			chdir(add);
			setcolor(9);
			printf("WELCOME %s USER:)", username);
			getchar();
			system("cls");
			return;
		}
	}
}
void createuser(char name[])
{
	setcolor(11);
	numberofusers++;
	char add[1000];
	// strcat()
	char cwd[PATH_MAX];
	getcwd(cwd, sizeof(cwd));
	char now[1000];
	strcpy(now, cwd);
	chdir("C:/Users/Win 10/Desktop/root/");
	makedir(name);
	chdir("C:/Users/Win 10/Desktop/root/hadis80/");
	creatfile(name);
	chdir(now);
}
void creatfile(char name[])
{
	setcolor(11);
	FILE *fptr2 = fopen("usersinfo.txt", "ab+");
	// FILE *fptr=fopen(name,"wb");
	printf("enter name: ");
	scanf("%s", s[numberofusers].name);
	printf("enter username: ");
	scanf("%s", s[numberofusers].username);
	printf("choose password: ");
	gets(s[numberofusers].passwd);
	int s2, n, i = 0;
	n = strength_pass(s[numberofusers].passwd);
	if (n > 34)
	{
		setcolor(12);
		printf("your password saved:)\n");
		s2 = n;
	}
	else
	{
		// printf("the password is too weak enter another password: ");
		while (n < 34)
		{
			gets(s[numberofusers].passwd);
			n = strength_pass(s[numberofusers].passwd);
			if (n > 33)
			{
				setcolor(12);
				printf("your password saved:)\n");
				s2 = n;
				break;
			}
			setcolor(12);
			printf("the password is too weak enter another password: ");
			i++;
		}
	}
	setcolor(11);
	printf("please enter the time : ");
	gets(s[numberofusers].time);
	s[numberofusers].strength = s2;
	s[numberofusers].access = 0;
	s[numberofusers].mistakes = 0;

	fwrite(&s[numberofusers], sizeof(struct user), 1, fptr2);
	//	fwrite(&s,sizeof(struct user),1,fptr2);
	if (fwrite != 0)
	{
		setcolor(11);
		printf("information of new user saved successfully:)\nuser created;)\n");
	}

	else
	{
		setcolor(12);
		printf("error saving data:(\n");
	}
	//	fclose(fptr);
	fclose(fptr2);
}
int strength_pass(char pass[])
{
	int i, n = 0, j = 0;
	for (i = 0; i < strlen(pass); i++)
	{
		char c;
		c = pass[i];
		if (ispunct(c))
			n += 8;
		if (isdigit(c))
			n += 3;
		if (isalpha(c))
		{
			if (isupper(c))
				n += 4;
			else
				n += 2;
		}
		if (c == ' ')
			n += 1;
	}
	return n;
}
void wc(char name[])
{
	FILE *fptr = fopen(name, "rb");
	if (fptr == NULL)
	{
		setcolor(12);
		printf("no such file:(");
		return;
	}
	int m = 1, k = 0, w = 1;
	char c;
	while ((c = fgetc(fptr)) != EOF)
	{
		if (c == '\n')
			m++;
		if (c == ' ' || c == '\n')
			w++;
		k++;
	}
	fclose(fptr);
	setcolor(11);
	printf("the number of lines and words and characters in the %s file : %d  %d  %d", name, m, w, k);

	return;
}
void cat(char name[])
{
	setcolor(11);
	FILE *fptr = fopen(name, "rb");
	if (fptr == NULL)
	{
		printf("no such file:(");
		return;
	}
	char c;
	while ((c = fgetc(fptr)) != EOF)
	{
		printf("%c", c);
	}
	fclose(fptr);
	return;
}
void diff(char name1[], char name2[]) //
{
	FILE *fp1 = fopen(name1, "rb");
	FILE *fp2 = fopen(name2, "rb");
	if (fp1 == NULL || fp2 == NULL)
	{
		printf("no such file:(");
		return;
	}
	char ch1 = getc(fp1);
	char ch2 = getc(fp2);
	int error = 0, pos = 0, line = 1;
	while (ch1 != EOF && ch2 != EOF)
	{
		pos++;
		if (ch1 == '\n' && ch2 == '\n')
		{
			line++;
			pos = 0;
		}
		if (ch1 != ch2)
		{
			error++;
			printf("Line Number : %d \tError Position : %d \n", line, pos);
		}
		ch1 = getc(fp1);
		ch2 = getc(fp2);
	}
	printf("Total Errors : %d\t", error);
	fclose(fp1);
	fclose(fp2);
	return;
}
void printdir(struct user presentuser)
{
	char cwd[1024];
	getcwd(cwd, sizeof(cwd));
	if (presentuser.access == 0)
	{
		setcolor(11);
		printf("%s@%s:", presentuser.name, presentuser.username);
		setcolor(9);
		printf("Dir: %s", cwd);
		setcolor(11);
		printf("$");
	}
	else
	{
		setcolor(9);
		printf("[adminstrator]");
		setcolor(3);
		printf("%s@%s:", presentuser.name, presentuser.username);
		printf("Dir:%s", cwd);
		setcolor(1);
		printf("#");
	}
}
void copy(char name[], char name2[])
{
	setcolor(11);
	FILE *fptr1 = fopen(name, "rb");
	FILE *fptr2 = fopen(name2, "rb");
	if (fptr1 == NULL)
	{
		printf("file %s doesnt exist:(", name);
		return;
	}
	if (fptr2 != NULL)
	{
		printf("the %s already exist\ndo you want to overwrite it:y/n ?\n", name2);
		int c;
		c = getch();
		if (c == 'y')
		{
			fclose(fptr2);
			fptr2 = fopen(name2, "wb"); // overwrite
			char ch;
			ch = fgetc(fptr1);
			while (!feof(fptr1))
			{
				fputc(ch, fptr2);
				ch = fgetc(fptr1);
			}
			printf("file copied successfully:)");
			fclose(fptr1);
			fclose(fptr2);
			return;
		}
		else
		{
			fclose(fptr2);
			fptr2 = fopen(name2, "ab+"); // append
			char ch;
			ch = fgetc(fptr1);
			while (!feof(fptr1))
			{
				fputc(ch, fptr2);
				ch = fgetc(fptr1);
			}

			printf("file copied successfully:)");
			fclose(fptr1);
			fclose(fptr2);
			return;
		}
	}
	else
	{
		fclose(fptr2);
		fptr2 = fopen(name2, "wb");
		char ch;
		ch = fgetc(fptr1);
		while (!feof(fptr1))
		{
			fputc(ch, fptr2);
			ch = fgetc(fptr1);
		}
		printf("file copied successfully:)");
		fclose(fptr1);
		fclose(fptr2);
		return;
	}
}

void move(char name[], char name2[])
{
	setcolor(11);
	FILE *fptr1 = fopen(name, "rb");
	FILE *fptr2 = fopen(name2, "rb");
	if (fptr1 == NULL)
	{
		printf("file %s doesnt exist:(", name);
		return;
	}
	if (fptr2 != NULL)
	{
		printf("the %s already exist\ndo you want to overwrite it:y/n ?\n", name2);
		int c;
		c = getch();
		if (c == 'y')
		{
			fclose(fptr2);
			fptr2 = fopen(name2, "wb"); // overwrite
			char ch;
			ch = fgetc(fptr1);
			while (!feof(fptr1))
			{
				fputc(ch, fptr2);
				ch = fgetc(fptr1);
			}
			fclose(fptr1);
			if (remove(name) == 0)
				printf("file moved successfully:)\n");
			else
				printf("cannot move:(\n");
			fclose(fptr2);
			return;
		}
		else
		{
			fclose(fptr2);
			fptr2 = fopen(name2, "ab+"); // append
			char ch;
			ch = fgetc(fptr1);
			while (!feof(fptr1))
			{
				fputc(ch, fptr2);
				ch = fgetc(fptr1);
			}
			fclose(fptr1);
			if (remove(name) == 0)
				printf("file moved successfully:)\n");
			else
				printf("cannot move:(\n");
			fclose(fptr2);
			return;
		}
	}
	else
	{
		fclose(fptr2);
		fptr2 = fopen(name2, "wb");
		char ch;
		ch = fgetc(fptr1);
		while (!feof(fptr1))
		{
			fputc(ch, fptr2);
			ch = fgetc(fptr1);
		}
		fclose(fptr1);
		if (remove(name) == 0)
			printf("file moved successfully:)\n");
		else
			printf("cannot move:(\n");
		fclose(fptr2);
		return;
	}
}

void operand(char name1[], char name2[]) //>
{
	setcolor(11);
	FILE *fptr1 = fopen(name1, "rb");
	FILE *fptr2 = fopen(name2, "wb");
	if (fptr1 == NULL)
	{

		fprintf(fptr2, "%s", name1);
		fclose(fptr2);
		return;
	}
	else
	{
		printf("keep file %s? y/n\n", name1);
		int n = getch();
		if (n == 'y')
		{

			char ch;
			ch = fgetc(fptr1);
			while (!feof(fptr1))
			{
				fputc(ch, fptr2);
				ch = fgetc(fptr1);
			}
			fclose(fptr1);
			fclose(fptr2);
		}
		else
		{
			char ch;
			ch = fgetc(fptr1);
			while (!feof(fptr1))
			{
				fputc(ch, fptr2);
				ch = fgetc(fptr1);
			}
			fclose(fptr1);
			fclose(fptr2);
			remove(name1);
		}
	}
	return;
}

void operand2(char name1[], char name2[]) //>>
{
	setcolor(11);
	FILE *fptr1 = fopen(name1, "rb");
	FILE *fptr2 = fopen(name2, "ab+");
	if (fptr1 == NULL)
	{
		fprintf(fptr2, "%s", name1);
		fclose(fptr2);
		return;
	}
	if (fptr2 == NULL)
	{
		printf("doesnt exist:(");
		return;
	}
	else
	{
		printf("keep file %s? y/n\n", name1);
		int n = getch();
		if (n == 'y')
		{
			char ch;
			ch = fgetc(fptr1);
			while (!feof(fptr1))
			{
				fputc(ch, fptr2);
				ch = fgetc(fptr1);
			}
			fclose(fptr1);
			fclose(fptr2);
		}
		else
		{
			char ch;
			ch = fgetc(fptr1);
			while (!feof(fptr1))
			{
				fputc(ch, fptr2);
				ch = fgetc(fptr1);
			}
			fclose(fptr1);
			fclose(fptr2);
			remove(name1);
		}
	}
	return;
}
void help()
{
	do
	{
		system("cls");
		setcolor(6);
		printf("\n\t\t\t\t*********   HELP   *********");
		printf("\n\n\t\t\tMENU-----:\n ");
		printf("\t\there are commands and a short introduction\n");
		printf("\t\tenter one of below numbers\n");
		setcolor(14);
		printf("\t\t1.cd directoryname\n\t\t2.pwd\n\t\t3.mkdir directoryname\n\t\t4.wc filename\n\t\t5.cat filename\n\t\t6.rm and rm-r filename"
			   "\n\t\t7.cp filename1 filename2\n\t\t8.mv filename1 filename2\n\t\t"
			   "9.ls\n\t\t10.>> or >\n\t\t11.create username\n\t\t12.su username\n\t\t13.passwd\n\t\t"
			   "14.diff filename1 filename2\n\t\t15.exif filename\n\t\t16.chgr username\n\t\t17.time\n\t\t18.time-a\n\t\t19.hide/hide-r\n\t\t"
			   "20.search filename or directory\n\t\t21.EXIT\n");
		int y;
		printf("\t\tenter your choice :");
		scanf("%d", &y);
		printf("\n");
		setcolor(14);
		switch (y)
		{
			setcolor(14);
		case 1:
			printf("command cd : it changes the directory.\nnote that you can use it with  absolute or relative address.\n"
				   "an example for relative address : cd ../root/filename\nan example for absolute address : cd C:/Users/Win 10/Desktop/root/");
			getch();
			break;
		case 2:
			printf("command pwd : it will show the address of where you are:)");
			getch();
			break;
		case 3:
			intromkdir();
			break;
		case 4:
			printf("command wc filename :it will show the number of lines and words and characters of a file.");
			getch();
			break;
		case 5:
			printf("command cat filename : it will show the contents of a file.");
			getch();
			break;
		case 6:
			printf("commad rm filename : it will delete a file\ncommand rm-r filename : it will delete a directory. ");
			getch();
			break;
		case 7:
			printf("command cp filename1 filename2 : it will copy the contents of file1 to file2.\n"
				   "note that it will ask you to choose wethere you want to delete the contents of  file2 or not:)");
			getch();
			break;
		case 8:
			printf("command mv filename1 filename2 : it will move the contents of file1 to file2.so file1 will remove:-)\n"
				   "note that it will ask you to choose wethere you want to delete the contents of  file2 or not:)");
			getch();
			break;
		case 9:
			printf("command ls : it will show you the files and directories in the situation that you are.");
			getch();
			break;
		case 10:
			intro();
			getch();
			break;
		case 11:
			printf("command create username : it will create a user and a directory for user with his/her username.");
			getch();
			break;
		case 12:
			printf("command su username : it will change the current user to the username you inserted.");
			getch();
			break;
		case 13:
			printf("command passwd : it will change the password of the current user and"
				   " if the current user is admin then with command (passwd -l time username) admin can change the password of a user and set a time for user.");
			getch();
			break;
		case 14:
			printf("command diff filename1 filename2 : it will show the places of where two files are differents and show how many different they have.");
			getch();
			break;
		case 15:
			printf("command exif filename : it will show you some information about"
				   "a file like the time it was created and the last time it has changed");
			getch();
			break;
		case 16:
			printf("command chgr username : it will change the normal user to admin in 3conditions:\n1."
				   "first: the users`mistakes should be less than 11\n2.second: the users`password should have strength more than 75"
				   "\n3.the time for user should be okay:)");
			getch();
			break;
		case 17:
			printf("command time :it will show the systems`time:)");
			getch();
			break;
		case 18:
			printf("command time-a :it will show the time more accurate:)");
			getch();
			break;
		case 19:
			printf("command hide filename :it will disappeare the file.\n"
				   "so when you print (ls) it will not be displayed.\ncommand hide-r filename: it acts as opposite of hide."
				   "\nit will  show the file or directory:)");
			getch();
			break;
		case 20:
			printf("command search filename or directoryname:\nit will show the address of file or directory:)");
			getch();
			break;
		case 21:
			getchar();
			system("cls");
			return;
		default:
			printf("error!!");
			getch();
		}
	} while (1);

	return;
}
void intromkdir()
{
	printf("command mkdir : it will make a directory.\n"
		   "note that you can use address and say where you want to make the directory"
		   "\nan example for relative address : mkdir ../root/filename\nan example for absolute address : cd C:/Users/Win 10/Desktop/root/");
	getch();
}
void intro()
{
	printf("command > : if you write a word then put (>) and then enter the name of file"
		   " like(hello > filename) it will append the word(hello) to the file.\nnote that using (>) will delete your file.\n"
		   "also you can say : filename1 > filename2.\nit will copy or move the file1 to file2"
		   " and the contents of file2 will remove.\n\ncommand >> : if you write a word then put"
		   "(>>) and then enter the name of file like (hello >> filename) it will append the word(hello) to the file."
		   "\nnote that using (>>) will not delete your file\n"
		   "also you can say : filename1 >> filename2.\nit will copy or move the file1 to file2"
		   " and the contents of file2 will not remove.");
	getch();
}
void update()
{
	FILE *fptr = fopen("usersinfo.txt", "rb");
	int i;
	for (i = 0; i < numberofusers + 1; i++)
	{
		fread(&s[i], sizeof(struct user), 1, fptr);
		if (strcmp(s[i].username, presentuser.username) == 0)
		{

			break;
		}
	}
	s[i] = presentuser;
	fclose(fptr);
	fptr = fopen("usersinfo.txt", "wb");
	for (int j = 0; j < numberofusers + 1; j++)
	{
		fwrite(&s[j], sizeof(struct user), 1, fptr);
	}
	fclose(fptr);
	return;
}
void showtime()
{
	setcolor(11);
	time_t s3, val = 1;
	struct tm *current_time;
	s3 = time(NULL);
	current_time = localtime(&s3);
	printf("%02d:%02d:%02d\n",
		   current_time->tm_hour,
		   current_time->tm_min,
		   current_time->tm_sec);
}
void showtime2()
{
	setcolor(11);
	time_t now;
	struct tm *ts;
	char buf[80], buf2[80];
	now = time(NULL);

	ts = localtime(&now);
	strftime(buf, sizeof(buf), "%B %A %Y-%m-%d %H:%M:%S %p %Z", ts);
	puts(buf);
	printf("\n");
}
void level()
{
	printf("%d\n", levelofaccess);
}
void pass(char p[])
{
	char cwd[PATH_MAX];
	getcwd(cwd, sizeof(cwd));
	char now[1000];
	strcpy(now, cwd);
	chdir("C:/Users/Win 10/Desktop/root/hadis80/");
	char pass2[100];
	if (strcmp(p, presentuser.passwd) == 0)
	{
		setcolor(11);
		printf("please enter your new password: ");
		gets(pass2);

		int s2, n, i = 0;
		n = strength_pass(pass2);
		if (n > 34)
		{
			strcpy(presentuser.passwd, pass2);
			presentuser.strength = n;
			update();
			FILE *fptr = fopen("usersinfo.txt", "rb");
			for (int i = 0; i < numberofusers + 1; i++)
			{
				fread(&s[i], sizeof(struct user), 1, fptr);
				if (strcmp(s[i].username, presentuser.username) == 0)
				{
					fclose(fptr);
					fptr = fopen("usersinfo.txt", "wb");
					for (int j = 0; j < numberofusers + 1; j++)
					{
						fwrite(&s[j], sizeof(struct user), 1, fptr);
					}
					fclose(fptr);
					setcolor(12);
					printf("your new password saved:)\n");
					chdir(now);
					return;
				}
			}
		}
		else
		{
			setcolor(4);
			printf("the password is too weak enter another password: ");
			while (n < 34)
			{
				gets(pass2);
				n = strength_pass(pass2);
				if (n > 33)
				{
					strcpy(presentuser.passwd, pass2);
					presentuser.strength = n;
					update();
					FILE *fptr = fopen("usersinfo.txt", "rb");
					for (int i = 0; i < numberofusers + 1; i++)
					{
						fread(&s[i], sizeof(struct user), 1, fptr);
						if (strcmp(s[i].username, presentuser.username) == 0)
						{
							fclose(fptr);
							fptr = fopen("usersinfo.txt", "wb");
							for (int j = 0; j < numberofusers + 1; j++)
							{
								fwrite(&s[j], sizeof(struct user), 1, fptr);
							}
							fclose(fptr);
							setcolor(12);
							printf("your new password saved:)\n");
							chdir(now);
							return;
						}
					}
				}
				setcolor(4);
				printf("the password is too weak:(enter another password: ");
				i++;
			}
		}
		setcolor(12);
		printf("user not found:(");
	}
	else
	{
		setcolor(12);
		printf("incorrect password:(\n");
	}
	chdir(now);
	return;
}
void pass2()
{
	char time4[20], time5[20], username[100], pass2[100];
	scanf("%s", time4);
	scanf("%s", time5);
	scanf("%s", username);
	strcat(time4, " ");
	strcat(time4, time5);
	setcolor(11);
	printf("please enter your new password: ");
	gets(pass2);
	int s2, n, i = 0;
	n = strength_pass(pass2);
	if (n > 34)
	{

		FILE *fptr = fopen("usersinfo.txt", "rb");
		for (int i = 0; i < numberofusers + 1; i++)
		{
			fread(&s[i], sizeof(struct user), 1, fptr);
			if (strcmp(s[i].username, username) == 0)
			{
				s[i].strength = n;
				strcpy(s[i].passwd, pass2);
				strcpy(s[i].time, time4);
				fclose(fptr);
				fptr = fopen("usersinfo.txt", "wb");
				for (int j = 0; j < numberofusers + 1; j++)
				{
					fwrite(&s[j], sizeof(struct user), 1, fptr);
				}
				fclose(fptr);
				setcolor(12);
				printf("the new password of user %s saved:)\n", username);
				return;
			}
		}
		setcolor(12);
		printf("user not found:(\n");
		return;
	}
	else
	{
		// printf("the password is too weak enter another password: ");
		while (n < 34)
		{
			gets(pass2);
			n = strength_pass(pass2);
			if (n > 33)
			{

				FILE *fptr = fopen("usersinfo.txt", "rb");
				for (int i = 0; i < numberofusers + 1; i++)
				{
					fread(&s[i], sizeof(struct user), 1, fptr);
					if (strcmp(s[i].username, username) == 0)
					{
						s[i].strength = n;
						strcpy(s[i].passwd, pass2);
						strcpy(s[i].time, time4);
						fclose(fptr);
						fptr = fopen("usersinfo.txt", "wb");
						for (int j = 0; j < numberofusers + 1; j++)
						{
							fwrite(&s[j], sizeof(struct user), 1, fptr);
						}
						fclose(fptr);
						setcolor(12);
						printf("the new password of user %s saved:)\n", username);
						return;
					}
				}
				setcolor(12);
				printf("user not found:(\n");
				return;
			}
			setcolor(4);
			printf("the password is too weak:( enter another password: ");
			i++;
		}
	}
}

void exif(char name[])
{
	struct stat stats;
	// stat() returns 0 on successful operation,
	// otherwise returns -1 if unable to get file properties.
	if (stat(name, &stats) == 0)
	{
		printFileProperties(stats);
	}
	else
	{
		boldred();
		printf("Unable to get file properties:(\n");
		printf("Please check whether '%s' file exists.\n", name);
	}
}

void printFileProperties(struct stat stats)
{
	setcolor(11);
	struct tm dt;
	// File permissions
	printf("\nFile access: ");
	if (stats.st_mode & R_OK)
		printf("read ");
	if (stats.st_mode & W_OK)
		printf("write ");
	if (stats.st_mode & X_OK)
		printf("execute");

	// File size
	printf("\nFile size: %d", stats.st_size);

	// Get file creation time in seconds and
	// convert seconds to date and time format
	dt = *(gmtime(&stats.st_ctime));
	printf("\nCreated on: %d-%d-%d %d:%d:%d", dt.tm_mday, dt.tm_mon + 1, dt.tm_year + 1900,
		   dt.tm_hour + 1, dt.tm_min + 1, dt.tm_sec + 1);

	// File modification time
	dt = *(gmtime(&stats.st_mtime));
	printf("\nModified on: %d-%d-%d %d:%d:%d", dt.tm_mday, dt.tm_mon + 1, dt.tm_year + 1 + 1900,
		   dt.tm_hour + 1, dt.tm_min + 1, dt.tm_sec);
}
void hide(char name[])
{
	char buffer[100];
	sprintf(buffer, "attrib +h %s", name);
	system(buffer);
	//	rmdir()
}
void show(char name[])
{
	char buffer[100];
	sprintf(buffer, "attrib -h %s", name);
	system(buffer);
}
void search(char name[])
{
	setcolor(11);
	char buffer[100];
	sprintf(buffer, "dir /s /b %s", name); // search file
	system(buffer);
}
void search2(char name[])
{
	setcolor(11);
	char buffer[100];
	sprintf(buffer, "dir %s /AD /s", name); // search directory
	system(buffer);
}
