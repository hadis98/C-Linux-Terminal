#include "headers.h"
#include "general.h"
#include "commands.h"
#include "command_line_help.h"
#include "manage_commands.h"
#include "user_login.h"

int level_of_access = 1, NUMBER_OF_USERS = 0;
user users[1000], current_user;

int main()
{

	print_welcome_messages();
	handle_user_enter();
	handle_user_commands();

	return 0;
}
