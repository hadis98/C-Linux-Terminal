#include "headers.h"
#include "general.h"
#include "commands.h"
#include "command_line_help.h"
#include "manage_commands.h"
#include "user_login.h"

void init_base_address();
void init_user_admin_config();
void handle_start_option_selection();

int NUMBER_OF_USERS = 0;
user users[1000], current_user;
char ROOT_DIRECTORY[120], USERSINFO_FILE[120];

int main()
{

	init_base_address();
	handle_start_option_selection();
	NUMBER_OF_USERS = get_number_of_users();
	load_file_info();
	print_welcome_messages();
	handle_user_enter();
	handle_user_commands();

	return 0;
}

void init_base_address()
{
	char cwd[PATH_MAX];
	chdir("..");
	getcwd(cwd, sizeof(cwd));
	strcpy(ROOT_DIRECTORY, cwd);
	printf("cwd=%s\n", ROOT_DIRECTORY);
	sprintf(USERSINFO_FILE, "%s\\usersinfo.txt", cwd);
	printf("users info file=%s\n", USERSINFO_FILE);
}

void handle_start_option_selection()
{
	char start_scratch = false;
	int is_init_config_selected = false;

	do
	{
		setcolor(1);
		printf("\n\nDo you want to start with initial admin file and dismiss updated usersinfo.txt file: y/n?\n");

		is_init_config_selected = getch();
	} while (is_init_config_selected != 'y' && is_init_config_selected != 'n');

	if (is_init_config_selected == 'y')
		init_user_admin_config();
}

void init_user_admin_config()
{
	struct user admin_user;
	strcpy(admin_user.name, "hadis");
	strcpy(admin_user.username, "admin");
	strcpy(admin_user.passwd, "1234");
	admin_user.strength = get_password_strength(admin_user.passwd);
	admin_user.access = 1;
	admin_user.mistakes = 0;
	strcpy(admin_user.time, "2023/12/13 13:13:13");

	FILE *fptr = fopen(USERSINFO_FILE, "wb");
	fwrite(&admin_user, sizeof(struct user), 1, fptr);
	fclose(fptr);
}