#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct user
{
	char name[100];
	char username[100];
	char passwd[100];
	int strength;
	int access;
	int mistakes;
	char time[100];
};
int main()
{
	struct user u={"hadis","hadis80","invest in yourself",34,1,0,"2020/12/13 13:13:13"};
	char name[100];
	FILE *fptr=fopen("usersinfo.txt","wb");
	//fprintf(fptr,"%s%s%s%d%d",u.name,u.username,u.passwd,u.strength,u.access);
	fwrite(&u,sizeof(struct user),1,fptr);
	fclose(fptr);
	/*
	fptr=fopen("usersinfo.txt","rb");
	fread(&u,sizeof(struct user),1,fptr);
	fclose(fptr);
	char username[100];
	gets(username);
	gets(name);
	if(strcmp(u.passwd,name)==0 && strcmp(u.username,username)==0)
	printf("allow");
	//printf("%s  %s",u.username,u.passwd);
	*/
	return 0;
}
