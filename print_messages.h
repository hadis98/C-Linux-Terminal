#ifndef PRINT_MESSAGES_H
#define PRINT_MESSAGES_H

#include "headers.h"
#include "general.h"

void print_welcome_messages();
void print_enter_retry();
void print_enter_user_successfully(char[]);
void print_enter_name();
void print_enter_username();
void print_enter_password();
void print_take_user_password(char[]);
void print_timeout_user_session(char[]);
void print_save_new_user_error();
void print_enter_time();
void print_successfully_update_password();
void print_successfully_save_password();
void print_successfully_save_new_user();
void print_directory_successfully_created();
void print_enter_new_password();
void print_directory_create_error();
void print_welcome_user_login(char[]);
void print_weak_password_error();
void print_user_not_found_error();
void print_incorrect_password_error();
void print_permission_denied_error();
void print_successfully_admin_update_password(char[]);

void print_user_directory_details(struct user);
void print_normal_user_directory_info(struct user, char[]);
void print_admin_user_directory_info(struct user, char[]);

#endif