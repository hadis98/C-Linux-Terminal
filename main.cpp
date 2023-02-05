#include "headers.h"
#include "general.h"
#include "commands.h"
#include "command_line_help.h"
#include "manage_commands.h"
#include "user_login.h"

int NUMBER_OF_USERS = 0;
user users[1000], current_user;

int main()
{
	NUMBER_OF_USERS = get_number_of_users();
	load_file_info();
	print_welcome_messages();
	handle_user_enter();
	handle_user_commands();

	return 0;
}
