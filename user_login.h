
#ifndef USER_LOGIN_H
#define USER_LOGIN_H

#include "headers.h"
#include "general.h"

void handle_user_enter();
void print_welcome_messages();
void enter_user_successfully(char[]);
bool is_password_valid(char[], char[]);
bool is_username_valid(char[], char[]);

#endif