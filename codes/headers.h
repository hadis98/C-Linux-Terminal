
#ifndef HEADERS_H
#define HEADERS_H

#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <process.h>
#include <io.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <errno.h>

// #define ROOT_DIRECTORY "C:/Users/Win 10/Desktop/root/"
#define MIN_PASSWORD_STRENGTH 34
// #define USERSINFO_FILE "C:/Users/Win 10/Desktop/root/usersinfo.txt"

struct user
{
    char name[30];
    char username[30];
    char passwd[40];
    int strength;
    int access;
    int mistakes;
    char time[30];
};

extern user users[1000], current_user;
extern int NUMBER_OF_USERS;
extern int errno;
extern char ROOT_DIRECTORY[120], USERSINFO_FILE[120];

#endif