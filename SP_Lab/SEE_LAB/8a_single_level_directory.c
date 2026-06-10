/*
==================================================
MEMORY MAP / QUICK REVISION
==================================================

Goal:
- Simulate single-level directory organization.

Logic:
1. Store all file names in a single list.
2. Support create, delete, search, display.

Key Variables:
- files[] -> list of file names
- fileCount -> number of files

Algorithm Used:
- Single-level directory simulation

==================================================
*/

/*
Program Name: Single-Level Directory Organization
Aim: Write a C program to simulate the Single-level directory organization technique.
Algorithm:
1. Create a file list.
2. Support create, delete, search, display operations.
Compilation: gcc 8a_single_level_directory.c -o dir1
Execution: ./dir1
*/

#include <stdio.h>
#include <string.h>

#define MAX_FILES 30

typedef struct {
    char name[30];
} File;

int searchFile(File files[], int fileCount, const char *name)
{
    for (int i = 0; i < fileCount; i++) {
        if (strcmp(files[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

int main(void)
{
    File files[MAX_FILES];
    int fileCount = 0;
    int choice;

    while (1) {
        printf("\nSingle-Level File Organization\n");
        printf("1. Create file\n");
        printf("2. Delete file\n");
        printf("3. Search file\n");
        printf("4. Display all files\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            if (fileCount >= MAX_FILES) {
                printf("Directory full.\n");
                continue;
            }

            char fname[30];
            printf("Enter file name: ");
            scanf("%s", fname);

            if (searchFile(files, fileCount, fname) != -1) {
                printf("File already exists.\n");
            } else {
                strcpy(files[fileCount].name, fname);
                fileCount++;
                printf("File created.\n");
            }
        } else if (choice == 2) {
            char fname[30];
            printf("Enter file name to delete: ");
            scanf("%s", fname);

            int pos = searchFile(files, fileCount, fname);
            if (pos == -1) {
                printf("File not found.\n");
            } else {
                for (int i = pos; i < fileCount - 1; i++) {
                    files[i] = files[i + 1];
                }
                fileCount--;
                printf("File deleted.\n");
            }
        } else if (choice == 3) {
            char fname[30];
            printf("Enter file name to search: ");
            scanf("%s", fname);

            int pos = searchFile(files, fileCount, fname);
            if (pos == -1) {
                printf("File not found.\n");
            } else {
                printf("File found at index %d in directory.\n", pos);
            }
        } else if (choice == 4) {
            if (fileCount == 0) {
                printf("No files in directory.\n");
            } else {
                printf("\nFiles in directory:\n");
                for (int i = 0; i < fileCount; i++) {
                    printf("%d. %s\n", i + 1, files[i].name);
                }
            }
        } else if (choice == 5) {
            break;
        } else {
            printf("Invalid choice.\n");
        }
    }

    return 0;
}
