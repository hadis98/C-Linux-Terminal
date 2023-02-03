
#ifndef MANAGE_FILES_H
#define MANAGE_FILES_H

#include "headers.h"
#include "general.h"
#include "print_messages.h"

bool update_usersinfo_file();
bool read_usersinfo_file();
void write_usersinfo_file();
bool update_new_user_password_file(char[], int);
bool update_password_file_by_admin(char[], char[], char[], int);

#endif
