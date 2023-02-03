#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <process.h>
#include <io.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>
#include <sys/stat.h>
#include <stdbool.h>

#define PROGRAM_DIRECTORY "C:/Users/Win 10/Desktop/root/hadis80/"
#define MIN_PASSWORD_STRENGTH 34
#define USERSINFO_FILE "usersinfo.txt"
struct user
{
	char name[100];
	char username[100];
	char passwd[100];
	int strength;
	int access;
	int mistakes;
	char time[10];
} users[1000], x, current_user;

void execute_ls_command();
void create_directory_command();
void execute_chgr_command();
void execute_create_command();
void execute_su_command();
void execute_diff_command();
void execute_cd_command();
void execute_cat_command();
void execute_wc_command();
void execute_rm_command();
void execute_rm_dash_r_command();
void execute_cp_command();
void execute_mv_command();
void execute_time_command();
void execute_time_dash_a_command();
void execute_passwd_command();
void execute_passwd_dash_l_command();
void execute_hide_command();
void execute_hide_dash_r_command();
void execute_exif_command();
void execute_search_command();
void execute_greater_equal_command(char[]);
void execute_greater_command(char[]);
void handle_incorrect_command();
void diff_files_command(char[], char[]);
void copy_file_command(char[], char[]);
void move_file_command(char[], char[]);
void make_directory(char[]);

int get_password_strength(char[]);
void create_new_user_file(char[]);
void word_count_command(char[]);
void cat_file_command(char[]);
void create_new_user_command(char[]);
void show_file_command(char[]);
void hide_file_command(char[]);
void exif_file_command(char[]);
void create_directory_command();
void execute_help_command();
void execute_exit_command();
void execute_ls_command();
void execute_su_command();
void help_command_summery();
void redirection_greater_operand(char[], char[]);
void redirection_greater_equal_operand(char[], char[]);
void print_user_directory_details(struct user);
void print_welcome_messages();
int execute_pwd_command();
void increse_user_access_level(char[]);
void switch_user_command(char[]);
void redirection_command_help();
void mkdir_command_help();
bool is_password_valid(char[], char[]);
bool is_username_valid(char[], char[]);
bool is_strings_equal(char[], const char[]);

void print_enter_new_password();
void print_weak_password_error();
void print_successfully_update_password();
void print_user_not_found_error();
void print_incorrect_password_error();

bool update_new_user_password_file(char new_password[], int entered_password_strength);

bool update_usersinfo_file();
bool read_usersinfo_file();
void write_usersinfo_file();
void execute_level_command();
void change_current_password(char[]);
void pass2();
void print_file_properties(struct stat);
void search_file(char[]);
void search_directory(char[]);
void handle_user_enter();
void handle_user_commands();
int get_user_commands();
void enter_user_successfully(char[]);
void print_normal_user_directory_info(struct user, char[]);
void print_admin_user_directory_info(struct user, char[]);
int get_help_selected_choice();
int handle_help_command_selection(int);

/*
//*The different color codes are

//*0   BLACK
//*1   BLUE
//*2   GREEN
//*3   CYAN
//*4   RED
//*5   MAGENTA
//*6   BROWN
//*7   LIGHTGRAY
//*8   DARKGRAY
//*9   LIGHTBLUE
//*10  LIGHTGREEN
//*11  LIGHTCYAN
//*12  LIGHTRED
//*13  LIGHTMAGENTA
//*14  YELLOW
//*15  WHITE
*/

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

int level_of_access = 1, NUMBER_OF_USERS = 0;

int main()
{

	print_welcome_messages();
	handle_user_enter();
	handle_user_commands();

	return 0;
}

void print_welcome_messages()
{
	setcolor(2);
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

void handle_user_enter()
{
	char username[100];
	char password[100];

	system("cls");
	Boldcyan();
	printf("\n\n\n\t\t\tPLEASE ENTER YOUR USERNAME: ");
	gets(username);

	Boldcyan();
	printf("\n\n\n\t\t\tPLEASE ENTER YOUR PASSWORD: ");
	gets(password);

	FILE *fptr = fopen(USERSINFO_FILE, "rb");

	struct user selected_user;
	fread(&selected_user, sizeof(struct user), 1, fptr);

	users[NUMBER_OF_USERS] = selected_user;
	current_user = selected_user;

	if (is_password_valid(password, selected_user.passwd) && is_username_valid(username, selected_user.username))
	{

		enter_user_successfully(username);
	}
	else
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

		} while (!is_password_valid(password, selected_user.passwd) || !is_username_valid(username, selected_user.username));
		enter_user_successfully(username);
	}
}

void enter_user_successfully(char username[])
{
	system("cls");
	Cyan();
	printf("\n\n\n\n\t\t\t\t\t\\WELCOME USER %s", username);
	getchar();
}

bool is_password_valid(char entered_password[], char valid_password[])
{
	return strcmp(entered_password, valid_password) == 0;
}

bool is_username_valid(char entered_username[], char valid_username[])
{
	return strcmp(entered_username, valid_username) == 0;
}

void handle_user_commands()
{

	while (1)
	{
		print_user_directory_details(current_user);

		if (get_user_commands() == -1)
		{
			break;
		}
	}
}

int get_user_commands()
{
	char user_command[1000];

	scanf("%s", user_command);
	if (is_strings_equal(user_command, "ls"))
	{
		execute_ls_command();
	}

	else if (is_strings_equal(user_command, "mkdir"))
	{
		create_directory_command();
	}

	else if (is_strings_equal(user_command, "EXIT"))
	{
		execute_exit_command();
		return -1;
	}

	else if (is_strings_equal(user_command, "pwd"))
	{

		execute_pwd_command();
	}

	else if (is_strings_equal(user_command, "chgr"))
	{
		execute_chgr_command();
	}

	else if (is_strings_equal(user_command, "create"))
	{

		execute_create_command();
	}

	else if (is_strings_equal(user_command, "su"))
	{
		execute_su_command();
	}

	else if (is_strings_equal(user_command, "diff"))
	{
		execute_diff_command();
	}

	else if (is_strings_equal(user_command, "cd"))
	{
		execute_cd_command();
	}

	else if (is_strings_equal(user_command, "cat"))
	{
		execute_cat_command();
	}

	else if (is_strings_equal(user_command, "wc"))
	{
		execute_wc_command();
	}

	else if (is_strings_equal(user_command, "rm"))
	{
		execute_rm_command();
	}

	else if (is_strings_equal(user_command, "rm-r"))
	{
		execute_rm_dash_r_command();
	}

	else if (is_strings_equal(user_command, "cp"))
	{
		execute_cp_command();
	}

	else if (is_strings_equal(user_command, "mv"))
	{
		execute_mv_command();
	}
	/*
	else if(strcmp(s,"myeditor")==0)
	{
		myeditor();
	}
	*/
	else if (is_strings_equal(user_command, "help"))
	{
		execute_help_command();
	}

	else if (is_strings_equal(user_command, "time"))
	{
		execute_time_command();
	}

	else if (is_strings_equal(user_command, "time-a"))
	{
		execute_time_dash_a_command();
	}

	else if (is_strings_equal(user_command, "level"))
	{
		execute_level_command();
	}

	else if (is_strings_equal(user_command, "passwd"))
	{
		execute_passwd_command();
	}

	else if (is_strings_equal(user_command, "passwd-l"))
	{
		execute_passwd_dash_l_command();
	}

	else if (is_strings_equal(user_command, "hide"))
	{
		execute_hide_command();
	}

	else if (is_strings_equal(user_command, "hide-r"))
	{
		execute_hide_dash_r_command();
	}

	else if (is_strings_equal(user_command, "exif"))
	{
		execute_exif_command();
	}

	else if (is_strings_equal(user_command, "search"))
	{
		execute_search_command();
	}

	else
	{
		char redirection_command[3];
		scanf("%s", redirection_command);

		if (is_strings_equal(redirection_command, ">>"))
		{
			execute_greater_equal_command(user_command);
		}
		else if (is_strings_equal(redirection_command, ">"))
		{
			execute_greater_command(user_command);
		}
		else
		{
			handle_incorrect_command();
		}
	}
}

void handle_incorrect_command()
{
	boldred();
	printf("incorrect command\n");
	current_user.mistakes++;
	update_usersinfo_file();
}

void execute_greater_equal_command(char file_name1[])
{
	char file_name2[100];
	scanf("%s", file_name2);
	redirection_greater_equal_operand(file_name1, file_name2);
}

void execute_greater_command(char file_name1[])
{
	char file_name2[100];
	scanf("%s", file_name2);
	redirection_greater_operand(file_name1, file_name2);
}

void execute_search_command()
{
	char entered_name[100];
	getchar();
	gets(entered_name);

	FILE *fptr = fopen(entered_name, "rb");

	if (fptr == NULL)
	{
		search_directory(entered_name);
		fclose(fptr);
	}
	else
	{
		search_file(entered_name);
	}
}

void execute_exif_command()
{
	getchar();
	char file_name[100];
	gets(file_name);
	exif_file_command(file_name);
	printf("\n");
}

void execute_hide_dash_r_command()
{
	getchar();
	char file_name[100];
	gets(file_name);
	show_file_command(file_name);
}

void execute_hide_command()
{
	getchar();
	char file_name[100];
	gets(file_name);
	hide_file_command(file_name);
}

void execute_passwd_dash_l_command()
{
	getchar();
	if (level_of_access == 1)
		pass2();
	else
	{
		boldred();
		printf("permission denied:(\n");
	}
}

void execute_passwd_command()
{
	char entered_password[100];
	getchar();
	setcolor(9);
	printf("please enter your current password: ");
	gets(entered_password);

	change_current_password(entered_password);
}

void execute_mv_command()
{
	char file_name1[100];
	char file_name2[100];

	scanf("%s%s", file_name1, file_name2);
	move_file_command(file_name1, file_name2);
	printf("\n");
}

void execute_cp_command()
{
	char file_name1[100];
	char file_name2[100];

	scanf("%s%s", file_name1, file_name2);
	copy_file_command(file_name1, file_name2);
	printf("\n");
}

void execute_rm_dash_r_command()
{

	char directory_name[100];
	scanf("%s", directory_name);

	if (rmdir(directory_name) == 0)
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

void execute_rm_command()
{

	char file_name[100];
	scanf("%s", file_name);

	if (remove(file_name) == 0)
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

void execute_wc_command()
{
	char file_name[1000];
	scanf("%s", file_name);

	word_count_command(file_name);
	printf("\n");
}

void execute_cat_command()
{
	char file_name[1000];
	scanf("%s", file_name);

	cat_file_command(file_name);
	printf("\n");
}

void execute_cd_command()
{
	char directory_address[1000];
	getchar();
	gets(directory_address);
	chdir(directory_address);
	printf("\n");
}

void execute_diff_command()
{
	char file_name1[100];
	char file_name2[100];
	scanf("%s%s", file_name1, file_name2);
	// diff_files_command(file_name1, file_name2);

	char diff_command[100] = "fc ";
	strcat(diff_command, file_name1);
	strcat(diff_command, " ");
	strcat(diff_command, file_name2);
	system(diff_command);

	printf("\n");
}

void execute_create_command()
{
	char *user_name;
	user_name = (char *)malloc(sizeof(char));
	scanf("%s", user_name);

	if (level_of_access == 1)
	{
		create_new_user_command(user_name);
	}
	else
	{
		boldred();
		printf("permission denied\n");
	}
}

void execute_ls_command()
{
	setcolor(14);
	system("dir /b");
	printf("\n");
}

void execute_exit_command()
{
	getchar();
	system("cls");
	boldred();
	printf("END OF PROGRAM..\nGOOD BYE:)");
}

void create_directory_command()
{
	char directory_name[100];

	getchar();
	gets(directory_name);

	CreateDirectory(directory_name, NULL);
	setcolor(5);
	printf("Directory created");
	printf("\n");
}

bool is_strings_equal(char str1[], const char str2[])
{
	return strcmp(str1, str2) == 0;
}

int execute_pwd_command()
{
	char cwd[PATH_MAX];

	// setcolor(12);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		setcolor(11);
		printf("\nCurrent working dir: %s\n", cwd);
		return 0;
	}
	else
	{
		perror("getcwd() error\n");
		return 1;
	}
}

void make_directory(char directory_name[])
{
	int check;
	check = mkdir(directory_name);

	if (!check)
		return;

	boldred();
	printf("Unable to create directory:(\n");
	exit(1);
}

void execute_chgr_command()
{
	char username[100];
	scanf("%s", username);
	increse_user_access_level(username);
}

void increse_user_access_level(char username[])
{
	int i, j;
	char cwd[PATH_MAX];
	char now[1000];

	getcwd(cwd, sizeof(cwd));
	strcpy(now, cwd);
	chdir(PROGRAM_DIRECTORY);

	FILE *fptr = fopen(USERSINFO_FILE, "wb");

	for (j = 0; j < NUMBER_OF_USERS + 1; j++)
	{
		fwrite(&users[j], sizeof(struct user), 1, fptr);
	}

	fclose(fptr);

	fptr = fopen(USERSINFO_FILE, "rb");

	if (level_of_access == 1) // current_user.access==1
	{
		for (i = 0; i < NUMBER_OF_USERS + 1; i++)
		{
			fread(&users[i], sizeof(struct user), 1, fptr);

			if (strcmp(users[i].username, username) == 0)
			{
				if (users[i].access == 0 && users[i].mistakes < 11 && users[i].strength > 75)
				{
					users[i].access = 1;
					level_of_access = 1;
					setcolor(11);
					printf("user with %s  username became admin:)\n", users[i].username);
					fclose(fptr);
					fptr = fopen(USERSINFO_FILE, "wb");
					for (i = 0; i < NUMBER_OF_USERS + 1; i++)
					{
						fwrite(&users[i], sizeof(struct user), 1, fptr);
					}
					fclose(fptr);
					chdir(now);
					return;
				}
			}
		}

		if (i == NUMBER_OF_USERS + 1)
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

void execute_su_command()
{
	char username[100];
	scanf("%s", username);
	getchar();
	switch_user_command(username);
}

void switch_user_command(char username[100])
{
	char cwd[PATH_MAX];
	char now2[1000];
	char time3[100], pass[100];

	getcwd(cwd, sizeof(cwd));
	strcpy(now2, cwd);

	chdir(PROGRAM_DIRECTORY);

	time_t now;
	struct tm *ts;

	now = time(NULL);
	ts = localtime(&now);

	setcolor(10);
	strftime(time3, sizeof(time3), "%Y/%m/%d %H:%M:%S", ts); // time now
	FILE *fptr = fopen(USERSINFO_FILE, "wb");

	for (int j = 0; j < NUMBER_OF_USERS + 1; j++)
	{
		fwrite(&users[j], sizeof(struct user), 1, fptr);
	}

	fclose(fptr);

	fptr = fopen(USERSINFO_FILE, "rb");

	int i;

	if (level_of_access == 1)
	{
		for (i = 0; i < NUMBER_OF_USERS + 1; i++)
		{
			fread(&users[i], sizeof(struct user), 1, fptr);

			if (strcmp(users[i].username, username) == 0)
			{
				if (strcmp(users[i].time, time3) <= 0)
				{
					setcolor(12);
					printf("the time for user %s has finished:(\nso suer %s cannot access to terminal any more:(\n", username, username);
					fclose(fptr);
					chdir(now2);
					return;
				}
				level_of_access = users[i].access;
				current_user = users[i];
				break;
			}
		}

		if (i == NUMBER_OF_USERS + 1)
		{
			setcolor(12);
			printf("permission denied:(\n");
		}

		else
		{

			char address[1000] = "C:/Users/Win 10/Desktop/root/";
			strcat(address, username);

			setcolor(9);
			printf("WELCOME %s USER:)", username);
			chdir(address);
			getchar();
			system("cls");
		}
	}
	else
	{
		setcolor(11);
		printf("\nuser %s please enter your pass: ", username);
		gets(pass);

		for (i = 0; i < NUMBER_OF_USERS + 1; i++)
		{
			fread(&users[i], sizeof(struct user), 1, fptr);

			if (strcmp(users[i].username, username) == 0 && strcmp(users[i].passwd, pass) == 0)
			{
				if (strcmp(users[i].time, time3) <= 0)
				{
					setcolor(12);
					printf("the time for user %s has finished:(\nso suer %s cannot access to terminal any more:(\n", username, username);
					fclose(fptr);
					chdir(now2);
					return;
				}
				level_of_access = users[i].access;
				current_user = users[i];
				break;
			}
		}
		if (i == NUMBER_OF_USERS + 1)
		{
			setcolor(12);
			printf("permission denied:(\n");
			fclose(fptr);
			chdir(now2);
			return;
		}
		else
		{

			char address[1000] = "C:/Users/Win 10/Desktop/root/";
			strcat(address, username);
			chdir(address);
			setcolor(9);
			printf("WELCOME %s USER:)", username);
			getchar();
			system("cls");
			return;
		}
	}
}

void create_new_user_command(char user_name[])
{
	char cwd[PATH_MAX];
	char current_working_directory_copy[1000];

	NUMBER_OF_USERS++;

	setcolor(11);
	getcwd(cwd, sizeof(cwd));
	strcpy(current_working_directory_copy, cwd);

	chdir(PROGRAM_DIRECTORY);
	chdir("..");
	make_directory(user_name);

	chdir(PROGRAM_DIRECTORY);
	create_new_user_file(user_name);

	chdir(current_working_directory_copy);
	printf("\n");
}

void create_new_user_file(char file_name[])
{
	setcolor(11);
	FILE *file = fopen(USERSINFO_FILE, "ab+");

	printf("enter name: ");
	scanf("%s", users[NUMBER_OF_USERS].name);

	printf("enter username: ");
	scanf("%s", users[NUMBER_OF_USERS].username);

	printf("choose password: ");
	gets(users[NUMBER_OF_USERS].passwd);

	int s2, n, i = 0;
	n = get_password_strength(users[NUMBER_OF_USERS].passwd);

	if (n > 34)
	{
		setcolor(12);
		printf("your password saved:)\n");
		s2 = n;
	}
	else
	{
		while (n < 34)
		{
			gets(users[NUMBER_OF_USERS].passwd);
			n = get_password_strength(users[NUMBER_OF_USERS].passwd);
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
	gets(users[NUMBER_OF_USERS].time);

	users[NUMBER_OF_USERS].strength = s2;
	users[NUMBER_OF_USERS].access = 0;
	users[NUMBER_OF_USERS].mistakes = 0;

	fwrite(&users[NUMBER_OF_USERS], sizeof(struct user), 1, file);

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

	fclose(file);
}

int get_password_strength(char entered_password[])
{
	int i, password_strength = 0;
	char character;

	for (i = 0; i < strlen(entered_password); i++)
	{
		character = entered_password[i];

		if (ispunct(character))
		{
			password_strength += 8;
		}

		if (isdigit(character))
		{
			password_strength += 3;
		}

		if (isalpha(character))
		{
			if (isupper(character))
				password_strength += 4;
			else
				password_strength += 2;
		}

		if (character == ' ')
		{
			password_strength += 1;
		}
	}

	return password_strength;
}

void word_count_command(char file_name[])
{
	FILE *fptr = fopen(file_name, "rb");

	if (fptr == NULL)
	{
		setcolor(12);
		printf("file does not exist:(");
		return;
	}

	int line_counter = 1, character_counter = 0, words_counter = 1;
	char file_character;

	while ((file_character = fgetc(fptr)) != EOF)
	{
		if (file_character == '\n')
		{
			line_counter++;
		}

		if (file_character == ' ' || file_character == '\n')
		{

			words_counter++;
		}

		character_counter++;
	}

	fclose(fptr);
	setcolor(11);

	printf("in the %s file \nnumber of lines:%d \nnumber of words: %d \nnumber of characters : %d", file_name, line_counter, words_counter, character_counter);
	return;
}

void cat_file_command(char file_name[])
{
	setcolor(11);
	FILE *fptr = fopen(file_name, "rb");

	if (fptr == NULL)
	{
		printf("file does not exist:(");
		return;
	}

	char file_character;

	while ((file_character = fgetc(fptr)) != EOF)
	{
		printf("%c", file_character);
	}

	fclose(fptr);
	return;
}

void diff_files_command(char file_name1[], char file_name2[])
{
	printf("\nname1: %s name2: %s\n", file_name1, file_name2);
	FILE *fp1 = fopen(file_name1, "rb");
	FILE *fp2 = fopen(file_name2, "rb");

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

void print_user_directory_details(struct user current_user)
{
	char cwd[1024];
	getcwd(cwd, sizeof(cwd));

	if (current_user.access == 0)
	{
		print_normal_user_directory_info(current_user, cwd);
	}
	else
	{
		print_admin_user_directory_info(current_user, cwd);
	}
}

void print_normal_user_directory_info(struct user current_user, char cwd[])
{
	setcolor(11);
	printf("%s@%s:", current_user.name, current_user.username);
	setcolor(9);
	printf("Dir: %s", cwd);
	setcolor(11);
	printf("$");
}

void print_admin_user_directory_info(struct user current_user, char cwd[])
{
	setcolor(5);
	printf("[adminstrator]");
	setcolor(3);
	printf("%s@%s:", current_user.name, current_user.username);
	printf("Dir:%s", cwd);
	setcolor(5);
	printf("#");
}

void copy_file_command(char name[], char name2[])
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

void move_file_command(char file_name1[], char file_name2[])
{
	setcolor(11);
	FILE *fptr1 = fopen(file_name1, "rb");
	FILE *fptr2 = fopen(file_name2, "rb");

	if (fptr1 == NULL)
	{
		printf("file %s doesnt exist:(", file_name1);
		return;
	}

	if (fptr2 != NULL)
	{
		printf("the %s already exist\ndo you want to overwrite it:y/n ?\n", file_name2);
		int is_file_overwritten;
		is_file_overwritten = getch();
		if (is_file_overwritten == 'y')
		{
			fclose(fptr2);
			fptr2 = fopen(file_name2, "wb"); // overwrite
			char ch;
			ch = fgetc(fptr1);

			while (!feof(fptr1))
			{
				fputc(ch, fptr2);
				ch = fgetc(fptr1);
			}

			fclose(fptr1);

			if (remove(file_name1) == 0)
				printf("file moved successfully:)\n");
			else
				printf("cannot move:(\n");
			fclose(fptr2);
			return;
		}
		else
		{
			fclose(fptr2);
			fptr2 = fopen(file_name2, "ab+"); // append
			char ch;
			ch = fgetc(fptr1);

			while (!feof(fptr1))
			{
				fputc(ch, fptr2);
				ch = fgetc(fptr1);
			}

			fclose(fptr1);

			if (remove(file_name1) == 0)
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
		fptr2 = fopen(file_name2, "wb");

		char ch;
		ch = fgetc(fptr1);

		while (!feof(fptr1))
		{
			fputc(ch, fptr2);
			ch = fgetc(fptr1);
		}

		fclose(fptr1);

		if (remove(file_name1) == 0)
			printf("file moved successfully:)\n");
		else
			printf("cannot move:(\n");

		fclose(fptr2);
		return;
	}
}

void redirection_greater_operand(char file_name1[], char file_name2[]) //>
{
	setcolor(11);
	FILE *fptr1 = fopen(file_name1, "rb");
	FILE *fptr2 = fopen(file_name2, "wb");

	if (fptr1 == NULL)
	{

		fprintf(fptr2, "%s", file_name1);
		fclose(fptr2);
		return;
	}
	else
	{
		printf("keep file %s? y/n\n", file_name1);
		int is_file_kept = getch();
		if (is_file_kept == 'y')
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
			remove(file_name1);
		}
	}
	return;
}

void redirection_greater_equal_operand(char file_name1[], char file_name2[]) //>>
{
	setcolor(11);
	FILE *fptr1 = fopen(file_name1, "rb");
	FILE *fptr2 = fopen(file_name2, "ab+");

	if (fptr1 == NULL)
	{
		fprintf(fptr2, "%s", file_name1);
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
		printf("keep file %s? y/n\n", file_name1);
		int is_file_kept = getch();

		if (is_file_kept == 'y')
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
			remove(file_name1);
		}
	}
	return;
}

void execute_help_command()
{
	do
	{
		help_command_summery();
		int selected_command;
		selected_command = get_help_selected_choice();
		if (handle_help_command_selection(selected_command) == -1)
		{
			break;
		}

	} while (1);

	return;
}

void help_command_summery()
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
}

int get_help_selected_choice()
{
	setcolor(14);
	int selected_command;
	printf("\t\tenter your choice :");
	scanf("%d", &selected_command);
	printf("\n");
	return selected_command;
}

int handle_help_command_selection(int selected_command)
{
	switch (selected_command)
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
		mkdir_command_help();
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
		redirection_command_help();
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
		return -1;
	default:
		printf("error!!");
		getch();
	}
}

void mkdir_command_help()
{
	printf("command mkdir : it will make a directory.\n"
		   "note that you can use address and say where you want to make the directory"
		   "\nan example for relative address : mkdir ../root/filename\nan example for absolute address : cd C:/Users/Win 10/Desktop/root/");
	getch();
}

void redirection_command_help()
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

bool update_usersinfo_file()
{
	if (read_usersinfo_file())
	{
		write_usersinfo_file();
		return true;
	}

	return false;
}

bool read_usersinfo_file()
{
	FILE *fptr = fopen(USERSINFO_FILE, "rb");
	int i;

	for (i = 0; i < NUMBER_OF_USERS + 1; i++)
	{
		fread(&users[i], sizeof(struct user), 1, fptr);

		if (is_strings_equal(users[i].username, current_user.username))
		{
			users[i] = current_user;
			fclose(fptr);
			return true;
		}
	}

	fclose(fptr);
	return false;
}

void write_usersinfo_file()
{
	FILE *fptr = fopen(USERSINFO_FILE, "wb");

	for (int j = 0; j < NUMBER_OF_USERS + 1; j++)
	{
		fwrite(&users[j], sizeof(struct user), 1, fptr);
	}

	fclose(fptr);
}

void execute_time_command()
{
	time_t current_system_time;
	struct tm *current_local_time;

	current_system_time = time(NULL);
	current_local_time = localtime(&current_system_time);

	setcolor(2);
	printf("%02d:%02d:%02d\n",
		   current_local_time->tm_hour,
		   current_local_time->tm_min,
		   current_local_time->tm_sec);
}

void execute_time_dash_a_command()
{
	char current_time_str[80];
	struct tm *current_local_time;

	time_t current_system_time;
	current_system_time = time(NULL);
	current_local_time = localtime(&current_system_time);

	setcolor(2);
	strftime(current_time_str, sizeof(current_time_str), "%B %A %Y-%m-%d %H:%M:%S %p %Z", current_local_time);
	puts(current_time_str);
	printf("\n");
}

void execute_level_command()
{
	printf("%d\n", level_of_access);
}

void change_current_password(char entered_password[])
{
	char cwd[PATH_MAX];
	char current_address[1000];
	char new_password[100];
	int entered_password_strength;

	getcwd(cwd, sizeof(cwd));
	strcpy(current_address, cwd);

	if (!is_strings_equal(entered_password, current_user.passwd))
	{
		print_incorrect_password_error();
		return;
	}

	print_enter_new_password();

	gets(new_password);
	entered_password_strength = get_password_strength(new_password);

	if (entered_password_strength >= MIN_PASSWORD_STRENGTH)
	{
		if (update_new_user_password_file(new_password, entered_password_strength))
		{
			print_successfully_update_password();
			chdir(current_address);
			return;
		}
	}
	else
	{
		print_weak_password_error();

		while (entered_password_strength < MIN_PASSWORD_STRENGTH)
		{
			gets(new_password);
			entered_password_strength = get_password_strength(new_password);

			if (entered_password_strength >= MIN_PASSWORD_STRENGTH)
			{
				if (update_new_user_password_file(new_password, entered_password_strength))
				{
					print_successfully_update_password();
					chdir(current_address);
					return;
				}
			}
			print_weak_password_error();
		}
	}

	print_user_not_found_error();
	chdir(current_address);
	return;
}

void print_enter_new_password()
{
	setcolor(11);
	printf("please enter your new password: ");
}

void print_weak_password_error()
{
	setcolor(4);
	printf("the password is too weak:(enter another password: ");
}

void print_successfully_update_password()
{
	setcolor(12);
	printf("your new password saved:)\n");
}

void print_user_not_found_error()
{
	setcolor(12);
	printf("user not found:(");
}

void print_incorrect_password_error()
{
	setcolor(12);
	printf("incorrect password:(\n");
}

bool update_new_user_password_file(char new_password[], int entered_password_strength)
{

	strcpy(current_user.passwd, new_password);
	current_user.strength = entered_password_strength;

	if (update_usersinfo_file())
	{
		return true;
	}

	return false;
}

void pass2()
{
	char time4[20], time5[20], username[100], pass2[100];
	int s2, n, i = 0;

	scanf("%s", time4);
	scanf("%s", time5);
	scanf("%s", username);

	strcat(time4, " ");
	strcat(time4, time5);
	setcolor(11);

	printf("please enter your new password: ");

	gets(pass2);
	n = get_password_strength(pass2);

	if (n > 34)
	{

		FILE *fptr = fopen(USERSINFO_FILE, "rb");
		for (int i = 0; i < NUMBER_OF_USERS + 1; i++)
		{
			fread(&users[i], sizeof(struct user), 1, fptr);
			if (strcmp(users[i].username, username) == 0)
			{
				users[i].strength = n;
				strcpy(users[i].passwd, pass2);
				strcpy(users[i].time, time4);
				fclose(fptr);
				fptr = fopen(USERSINFO_FILE, "wb");
				for (int j = 0; j < NUMBER_OF_USERS + 1; j++)
				{
					fwrite(&users[j], sizeof(struct user), 1, fptr);
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

		while (n < 34)
		{
			gets(pass2);
			n = get_password_strength(pass2);
			if (n > 33)
			{

				FILE *fptr = fopen(USERSINFO_FILE, "rb");
				for (int i = 0; i < NUMBER_OF_USERS + 1; i++)
				{
					fread(&users[i], sizeof(struct user), 1, fptr);
					if (strcmp(users[i].username, username) == 0)
					{
						users[i].strength = n;
						strcpy(users[i].passwd, pass2);
						strcpy(users[i].time, time4);
						fclose(fptr);
						fptr = fopen(USERSINFO_FILE, "wb");
						for (int j = 0; j < NUMBER_OF_USERS + 1; j++)
						{
							fwrite(&users[j], sizeof(struct user), 1, fptr);
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

void exif_file_command(char name[])
{
	struct stat stats;
	//* stat() returns 0 on successful operation,
	//* otherwise returns -1 if unable to get file properties.

	if (stat(name, &stats) == 0)
	{
		print_file_properties(stats);
	}
	else
	{
		boldred();
		printf("Unable to get file properties:(\n");
		printf("Please check whether '%s' file exists.\n", name);
	}
}

void print_file_properties(struct stat stats)
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

void hide_file_command(char file_name[])
{
	char buffer[100];
	sprintf(buffer, "attrib +h %s", file_name);
	system(buffer);
}

void show_file_command(char file_name[])
{
	char buffer[100];
	sprintf(buffer, "attrib -h %s", file_name);
	system(buffer);
}

void search_file(char file_name[])
{
	setcolor(11);
	char file_address[100];
	sprintf(file_address, "dir /s /b %s", file_name);
	system(file_address);
}

void search_directory(char directory_name[])
{
	setcolor(11);
	char directory_address[100];
	sprintf(directory_address, "dir %s /AD /s", directory_name);
	system(directory_address);
}
