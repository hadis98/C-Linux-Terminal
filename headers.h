
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

#define PROGRAM_DIRECTORY "C:/Users/Win 10/Desktop/root/hadis80/"
#define ROOT_DIRECTORY "C:/Users/Win 10/Desktop/root/"
#define MIN_PASSWORD_STRENGTH 34
#define USERSINFO_FILE "../usersinfo.txt"

struct user
{
    char name[100];
    char username[100];
    char passwd[100];
    int strength;
    int access;
    int mistakes;
    char time[20];
};

extern user users[1000], current_user;
extern int NUMBER_OF_USERS;
extern int errno;

#endif