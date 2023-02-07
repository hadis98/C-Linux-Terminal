#include "manage_files.h"

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

bool write_usersinfo_file()
{
    FILE *fptr = fopen(USERSINFO_FILE, "wb");

    for (int i = 0; i < NUMBER_OF_USERS + 1; i++)
    {
        fwrite(&users[i], sizeof(struct user), 1, fptr);
    }

    fclose(fptr);

    if (fwrite != 0)
        return true;

    return false;
}

bool update_new_user_password_file(char new_password[], int entered_password_strength)
{

    strcpy(current_user.passwd, new_password);
    current_user.strength = entered_password_strength;

    if (update_usersinfo_file())
        return true;

    return false;
}

bool update_password_file_by_admin(char username[], char new_password[], char entered_time[], int password_strength)
{

    FILE *fptr = fopen(USERSINFO_FILE, "rb");

    for (int i = 0; i < NUMBER_OF_USERS + 1; i++)
    {
        fread(&users[i], sizeof(struct user), 1, fptr);

        if (is_strings_equal(users[i].username, username))
        {
            users[i].strength = password_strength;
            strcpy(users[i].passwd, new_password);
            strcpy(users[i].time, entered_time);
            fclose(fptr);

            if (write_usersinfo_file())
            {
                print_successfully_admin_update_password(username);
                return true;
            }
        }
    }

    return false;
}

void load_file_info()
{
    FILE *fptr = fopen(USERSINFO_FILE, "rb");

    int counter = 0;
    struct user temp;

    for (int i = 0; i < NUMBER_OF_USERS; i++)
    {
        fread(&users[i], sizeof(struct user), 1, fptr);
    }

    fclose(fptr);
}

void print_users_info()
{
    printf("number of users: %d\n", NUMBER_OF_USERS);

    for (int i = 0; i < NUMBER_OF_USERS; i++)
    {
        printf("username: %s , password: %s , strength: %d, mistakes:%d, access: %d , time: %s\n", users[i].username, users[i].passwd, users[i].strength, users[i].mistakes, users[i].access, users[i].time);
    }
}