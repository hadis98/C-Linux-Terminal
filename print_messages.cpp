#include "print_messages.h"

void print_enter_name()
{
    setcolor(11);
    printf("enter name: ");
}

void print_enter_username()
{
    setcolor(11);
    printf("enter username: ");
}

void print_enter_password()
{
    setcolor(11);
    printf("choose password: ");
}

void print_take_user_password(char username[])
{
    setcolor(11);
    printf("\nplease enter user %s password: ", username);
}

void print_timeout_user_session(char username[])
{
    setcolor(12);
    printf("the time for user %s has finished:(\nso this cannot access to terminal any more:(\n", username);
}

void print_enter_new_password()
{
    setcolor(2);
    printf("please enter your new password: ");
}

void print_enter_time()
{
    setcolor(11);
    printf("please enter the time : ");
}

void print_weak_password_error()
{
    setcolor(4);
    printf("the password is too weak:(enter another password: ");
}

void print_successfully_save_password()
{
    setcolor(12);
    printf("your password saved:)\n");
}

void print_successfully_update_password()
{
    setcolor(12);
    printf("your new password saved:)\n");
}

void print_successfully_admin_update_password(char username[])
{
    setcolor(12);
    printf("the new password of user %s saved:)\n", username);
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

void print_permission_denied_error()
{
    boldred();
    printf("permission denied:(\n");
}

void print_successfully_save_new_user()
{
    setcolor(11);
    printf("information of new user saved successfully:)\nuser created;)\n");
}

void print_save_new_user_error()
{
    setcolor(12);
    printf("error saving data:(\n");
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
