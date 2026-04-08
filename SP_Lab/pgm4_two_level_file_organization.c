#include <stdio.h>
#include <string.h>

#define MAX_USERS 10
#define MAX_FILES 20

typedef struct {
    char name[30];
} File;

typedef struct {
    char userName[30];
    File files[MAX_FILES];
    int fileCount;
} UserDirectory;

int findUser(UserDirectory users[], int userCount, const char *name) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].userName, name) == 0) {
            return i;
        }
    }
    return -1;
}

int main(void) {
    UserDirectory users[MAX_USERS];
    int userCount = 0;
    int choice;

    while (1) {
        printf("\nTwo-Level File Organization\n");
        printf("1. Create user directory\n");
        printf("2. Create file in user directory\n");
        printf("3. Display all directories\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            if (userCount >= MAX_USERS) {
                printf("Cannot create more users.\n");
                continue;
            }

            char uname[30];
            printf("Enter user name: ");
            scanf("%s", uname);

            if (findUser(users, userCount, uname) != -1) {
                printf("User already exists.\n");
            } else {
                strcpy(users[userCount].userName, uname);
                users[userCount].fileCount = 0;
                userCount++;
                printf("User directory created.\n");
            }
        } else if (choice == 2) {
            char uname[30], fname[30];
            printf("Enter user name: ");
            scanf("%s", uname);

            int u = findUser(users, userCount, uname);
            if (u == -1) {
                printf("User not found.\n");
                continue;
            }

            if (users[u].fileCount >= MAX_FILES) {
                printf("User directory is full.\n");
                continue;
            }

            printf("Enter file name: ");
            scanf("%s", fname);

            // Check duplicate file name under same user
            int exists = 0;
            for (int i = 0; i < users[u].fileCount; i++) {
                if (strcmp(users[u].files[i].name, fname) == 0) {
                    exists = 1;
                    break;
                }
            }

            if (exists) {
                printf("File already exists in this user directory.\n");
            } else {
                strcpy(users[u].files[users[u].fileCount].name, fname);
                users[u].fileCount++;
                printf("File created successfully.\n");
            }
        } else if (choice == 3) {
            if (userCount == 0) {
                printf("No user directories available.\n");
                continue;
            }

            printf("\nDirectory Structure:\n");
            for (int i = 0; i < userCount; i++) {
                printf("User: %s\n", users[i].userName);
                if (users[i].fileCount == 0) {
                    printf("  (no files)\n");
                } else {
                    for (int j = 0; j < users[i].fileCount; j++) {
                        printf("  - %s\n", users[i].files[j].name);
                    }
                }
            }
        } else if (choice == 4) {
            break;
        } else {
            printf("Invalid choice.\n");
        }
    }

    return 0;
}
