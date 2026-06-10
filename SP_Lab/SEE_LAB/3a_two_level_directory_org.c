/*
==================================================
MEMORY MAP / QUICK REVISION
==================================================

Goal:
- Simulate two-level directory organization.
- Each user has a separate directory with files.

Logic:
1. Create user directories.
2. Create files under a user.
3. Display all users and their files.

Algorithm Used:
- Two-level directory organization

==================================================
*/

/*
Program Name: Two-Level Directory Organization
Aim: Write a C program to simulate the Two-level directory organization technique.
Algorithm:
1. Maintain a list of users.
2. Each user has a file list.
3. Support create user, create file, display.
Compilation: gcc 3a_two_level_directory_org.c -o dir2
Execution: ./dir2
*/

#include <stdio.h>
#include <string.h>

struct user
{
    char name[20];
    int files;
    char file[10][20];
};

int main()
{
    struct user u[10];
    int n;
    char search_user[20], search_file[20], found=0;

    printf("Enter number of users: ");
    scanf("%d",&n);

    for(int i=0;i<n;i++)
    {
        printf("\nEnter user name: ");
        scanf("%s",u[i].name);

        printf("Enter number of files: ");
        scanf("%d",&u[i].files);

        for(int j=0;j<u[i].files;j++)
        {
            printf("Enter file name: ");
            scanf("%s",u[i].file[j]);
        }
    }

    printf("\nTwo Level Directory\n");

    for(int i=0;i<n;i++)
    {
        printf("\n%s\n",u[i].name);

        for(int j=0;j<u[i].files;j++)
        {
            printf(" +-- %s\n",u[i].file[j]);
        }
    }

    printf("\nEnter username to search in: "); 
    scanf("%s", search_user); 

    printf("Enter file name to search: "); 
    scanf("%s", search_file); 
 
    for(int i = 0; i < n; i++) 
    { 
        if(strcmp(u[i].name, search_user) == 0) 
        { 
            for(int j = 0; j < u[i].files; j++) 
            { 
                if(strcmp(u[i].file[j], search_file) == 0) 
                { 
                    found = 1; 
                    break; 
                } 
            } 
        } 
    } 
 
    if(found) 
        printf("File '%s' found under user '%s'.\n", search_file, search_user); 
    else 
        printf("File '%s' not found under user '%s'.\n", search_file, search_user); 
 
    return 0;
}