#include "commands.h"

void execute_ls_command()
{
    setcolor(14);
    system("dir /b");
    printf("\n");
}

void execute_mkdir_command()
{
    char directory_name[100];

    getchar();
    gets(directory_name);

    CreateDirectory(directory_name, NULL);
    setcolor(2);
    printf("Directory created successfully\n");
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

void execute_create_command()
{
    char *user_name;
    user_name = (char *)malloc(sizeof(char));
    scanf("%s", user_name);

    if (level_of_access == 1)
    {
        handle_create_new_user_command(user_name);
    }
    else
    {
        boldred();
        printf("permission denied\n");
    }
}

void handle_create_new_user_command(char user_name[])
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
    handle_create_new_user_file(user_name);

    chdir(current_working_directory_copy);
    printf("\n");
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

void handle_create_new_user_file(char file_name[])
{

    FILE *file = fopen(USERSINFO_FILE, "ab+");

    print_enter_name();
    scanf("%s", users[NUMBER_OF_USERS].name);

    print_enter_username();
    scanf("%s", users[NUMBER_OF_USERS].username);

    print_enter_password();
    gets(users[NUMBER_OF_USERS].passwd);

    int entered_password_strength;
    entered_password_strength = get_password_strength(users[NUMBER_OF_USERS].passwd);

    if (entered_password_strength >= MIN_PASSWORD_STRENGTH)
    {
        print_successfully_save_password();
    }
    else
    {
        while (entered_password_strength < MIN_PASSWORD_STRENGTH)
        {
            gets(users[NUMBER_OF_USERS].passwd);
            entered_password_strength = get_password_strength(users[NUMBER_OF_USERS].passwd);

            if (entered_password_strength >= MIN_PASSWORD_STRENGTH)
            {
                print_successfully_save_password();
                break;
            }

            print_weak_password_error();
        }
    }

    print_enter_time();
    gets(users[NUMBER_OF_USERS].time);

    users[NUMBER_OF_USERS].strength = entered_password_strength;
    users[NUMBER_OF_USERS].access = 0;
    users[NUMBER_OF_USERS].mistakes = 0;

    fwrite(&users[NUMBER_OF_USERS], sizeof(struct user), 1, file);

    if (fwrite != 0)
    {
        print_successfully_save_new_user();
    }
    else
    {
        print_save_new_user_error();
    }

    fclose(file);
}

void execute_su_command()
{
    char username[100];
    scanf("%s", username);
    getchar();
    switch_user_command(username);
}

void switch_user_command(char entered_username[100])
{
    char cwd[PATH_MAX];
    char origin_address[1000];
    char formated_current_time[100], pass[100];

    getcwd(cwd, sizeof(cwd));
    strcpy(origin_address, cwd);

    chdir(PROGRAM_DIRECTORY);

    time_t current_time;
    struct tm *ts;

    current_time = time(NULL);
    ts = localtime(&current_time);

    setcolor(10);
    strftime(formated_current_time, sizeof(formated_current_time), "%Y/%m/%d %H:%M:%S", ts); // time now
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

            if (is_strings_equal(users[i].username, entered_username))
            {
                if (strcmp(users[i].time, formated_current_time) <= 0)
                {
                    print_timeout_user_session(entered_username);
                    fclose(fptr);
                    chdir(origin_address);
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
            strcat(address, entered_username);

            setcolor(9);
            printf("WELCOME %s USER:)", entered_username);
            chdir(address);
            getchar();
            system("cls");
        }
    }
    else
    {
        print_take_user_password(entered_username);
        gets(pass);

        for (i = 0; i < NUMBER_OF_USERS + 1; i++)
        {
            fread(&users[i], sizeof(struct user), 1, fptr);

            if (is_strings_equal(users[i].username, entered_username) && is_strings_equal(users[i].passwd, pass))
            {
                if (strcmp(users[i].time, formated_current_time) <= 0)
                {
                    print_timeout_user_session(entered_username);
                    fclose(fptr);
                    chdir(origin_address);
                    return;
                }

                level_of_access = users[i].access;
                current_user = users[i];
                break;
            }
        }

        if (i == NUMBER_OF_USERS + 1)
        {
            print_permission_denied_error();
            fclose(fptr);
            chdir(origin_address);
            return;
        }
        else
        {

            char root_address[1000] = "C:/Users/Win 10/Desktop/root/";
            strcat(root_address, entered_username);
            chdir(root_address);
            setcolor(9);
            printf("WELCOME %s USER:)", entered_username);
            getchar();
            system("cls");
            return;
        }
    }
}

void execute_diff_command()
{
    char file_name1[100];
    char file_name2[100];
    scanf("%s%s", file_name1, file_name2);
    // handle_diff_files_command(file_name1, file_name2);

    char diff_command[100] = "fc ";
    strcat(diff_command, file_name1);
    strcat(diff_command, " ");
    strcat(diff_command, file_name2);
    system(diff_command);

    printf("\n");
}

void handle_diff_files_command(char file_name1[], char file_name2[])
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

void execute_cd_command()
{
    char directory_address[1000];
    getchar();
    gets(directory_address);
    chdir(directory_address);
    printf("\n");
}

void execute_cat_command()
{
    char file_name[1000];
    scanf("%s", file_name);

    handle_cat_file_command(file_name);
    printf("\n");
}

void handle_cat_file_command(char file_name[])
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

void execute_wc_command()
{
    char file_name[1000];
    scanf("%s", file_name);

    handle_word_count_command(file_name);
    printf("\n");
}

void handle_word_count_command(char file_name[])
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

void execute_cp_command()
{
    char file_name1[100];
    char file_name2[100];

    scanf("%s%s", file_name1, file_name2);
    handle_copy_file_command(file_name1, file_name2);
    printf("\n");
}

void handle_copy_file_command(char name[], char name2[])
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

void execute_mv_command()
{
    char file_name1[100];
    char file_name2[100];

    scanf("%s%s", file_name1, file_name2);
    handle_move_file_command(file_name1, file_name2);
    printf("\n");
}

void handle_move_file_command(char file_name1[], char file_name2[])
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

void execute_passwd_command()
{
    char entered_password[100];
    getchar();
    setcolor(9);
    printf("please enter your current password: ");
    gets(entered_password);

    handle_change_current_password(entered_password);
}

void handle_change_current_password(char entered_password[])
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

void execute_passwd_dash_l_command()
{
    getchar();

    if (level_of_access == 1)
        get_new_data_by_admin();
    else
    {
        print_permission_denied_error();
    }
}

void get_new_data_by_admin()
{
    char time1[20], time2[20], entered_username[100], new_password[100];

    scanf("%s%s", time1, time2);
    scanf("%s", entered_username);

    strcat(time1, " ");
    strcat(time1, time2);
    print_enter_new_password();

    gets(new_password);
    handle_passwd_dash_l_command(entered_username, new_password, time1);
}

void handle_passwd_dash_l_command(char username[], char new_password[], char full_time[])
{
    int password_strength;
    password_strength = get_password_strength(new_password);
    bool is_updated_successfully = false;

    if (password_strength >= MIN_PASSWORD_STRENGTH)
    {
        is_updated_successfully = update_password_file_by_admin(username, new_password, full_time, password_strength);

        if (!is_updated_successfully)
            print_user_not_found_error();
        return;
    }
    else
    {
        while (password_strength < MIN_PASSWORD_STRENGTH)
        {
            gets(new_password);
            password_strength = get_password_strength(new_password);

            if (password_strength >= MIN_PASSWORD_STRENGTH)
            {
                is_updated_successfully = update_password_file_by_admin(username, new_password, full_time, password_strength);

                if (!is_updated_successfully)
                    print_user_not_found_error();
                return;
            }
            print_weak_password_error();
        }
    }
}

void execute_hide_command()
{
    getchar();
    char file_name[100];
    gets(file_name);
    handle_hide_file_command(file_name);
}

void handle_hide_file_command(char file_name[])
{
    char buffer[100];
    sprintf(buffer, "attrib +h %s", file_name);
    system(buffer);
}

void execute_hide_dash_r_command()
{
    getchar();
    char file_name[100];
    gets(file_name);
    handle_show_file_command(file_name);
}

void handle_show_file_command(char file_name[])
{
    char buffer[100];
    sprintf(buffer, "attrib -h %s", file_name);
    system(buffer);
}

void execute_exif_command()
{
    getchar();
    char file_name[100];
    gets(file_name);
    handle_exif_file_command(file_name);
    printf("\n");
}

void handle_exif_file_command(char name[])
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

void execute_search_command()
{
    char entered_name[100];
    getchar();
    gets(entered_name);

    FILE *fptr = fopen(entered_name, "rb");

    if (fptr == NULL)
    {
        handle_search_directory(entered_name);
        fclose(fptr);
    }
    else
    {
        handle_search_file(entered_name);
    }
}

void handle_search_directory(char directory_name[])
{
    setcolor(11);
    char directory_address[100];
    sprintf(directory_address, "dir %s /AD /s", directory_name);
    system(directory_address);
}

void handle_search_file(char file_name[])
{
    setcolor(11);
    char file_address[100];
    sprintf(file_address, "dir /s /b %s", file_name);
    system(file_address);
}

void execute_greater_command(char file_name1[])
{
    char file_name2[100];
    scanf("%s", file_name2);
    handle_redirection_greater_operand(file_name1, file_name2);
}

void handle_redirection_greater_operand(char file_name1[], char file_name2[]) //>
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

void execute_greater_equal_command(char file_name1[])
{
    char file_name2[100];
    scanf("%s", file_name2);
    handle_redirection_greater_equal_operand(file_name1, file_name2);
}

void handle_redirection_greater_equal_operand(char file_name1[], char file_name2[]) //>>
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

void handle_incorrect_command()
{
    boldred();
    printf("incorrect command\n");
    current_user.mistakes++;
    update_usersinfo_file();
}

int execute_pwd_command()
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
        perror("getcwd() error\n");
        return 1;
    }
}

void execute_exit_command()
{
    getchar();
    system("cls");
    setcolor(5);
    printf("END OF PROGRAM..\nGOOD BYE:)");
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
