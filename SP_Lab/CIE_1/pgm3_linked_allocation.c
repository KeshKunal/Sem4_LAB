#include <stdio.h>
#include <string.h>

#define MAX_BLOCKS 50
#define MAX_FILES  20
#define MAX_CHAIN  20

typedef struct {
    char name[30];
    int blocks[MAX_CHAIN];
    int count;
} File;

int main(void) {
    int used[MAX_BLOCKS] = {0};
    File files[MAX_FILES];
    int fileCount = 0;
    int choice;

    while (1) {
        printf("\nLinked File Allocation\n");
        printf("1. Allocate file\n");
        printf("2. Display file table\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            if (fileCount >= MAX_FILES) {
                printf("File table is full.\n");
                continue;
            }

            char name[30];
            int n, i;
            int tempBlocks[MAX_CHAIN];
            int ok = 1;

            printf("Enter file name: ");
            scanf("%s", name);
            printf("Enter number of blocks: ");
            scanf("%d", &n);

            if (n <= 0 || n > MAX_CHAIN) {
                printf("Invalid number of blocks.\n");
                continue;
            }

            printf("Enter %d block numbers (0 to %d):\n", n, MAX_BLOCKS - 1);
            for (i = 0; i < n; i++) {
                scanf("%d", &tempBlocks[i]);

                // Validate range and availability
                if (tempBlocks[i] < 0 || tempBlocks[i] >= MAX_BLOCKS || used[tempBlocks[i]]) {
                    ok = 0;
                }

                // Check duplicates in current file input
                for (int j = 0; j < i; j++) {
                    if (tempBlocks[i] == tempBlocks[j]) {
                        ok = 0;
                    }
                }
            }

            if (!ok) {
                printf("Allocation failed: invalid or already used block(s).\n");
            } else {
                strcpy(files[fileCount].name, name);
                files[fileCount].count = n;

                for (i = 0; i < n; i++) {
                    files[fileCount].blocks[i] = tempBlocks[i];
                    used[tempBlocks[i]] = 1;
                }

                fileCount++;
                printf("File allocated successfully using linked blocks.\n");
            }
        } else if (choice == 2) {
            int i;
            printf("\nFile Name\tLinked Blocks\n");
            for (i = 0; i < fileCount; i++) {
                printf("%s\t\t", files[i].name);
                for (int j = 0; j < files[i].count; j++) {
                    printf("%d", files[i].blocks[j]);
                    if (j != files[i].count - 1) {
                        printf(" -> ");
                    }
                }
                printf("\n");
            }
            if (fileCount == 0) {
                printf("No files allocated yet.\n");
            }
        } else if (choice == 3) {
            break;
        } else {
            printf("Invalid choice.\n");
        }
    }

    return 0;
}
