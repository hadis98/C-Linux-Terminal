#include "user_login.h"

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