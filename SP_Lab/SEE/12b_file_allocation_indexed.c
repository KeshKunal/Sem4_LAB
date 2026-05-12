#include <stdio.h>
#include <string.h>

#define MAX_BLOCKS 50
#define MAX_FILES  20
#define MAX_INDEX  20

typedef struct {
    char name[30];
    int indexBlock;
    int blocks[MAX_INDEX];
    int count;
} File;

int main(void) {
    int used[MAX_BLOCKS] = {0};
    File files[MAX_FILES];
    int fileCount = 0;
    int choice;

    while (1) {
        printf("\nIndexed File Allocation\n");
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
            int indexBlock, n;
            int tempBlocks[MAX_INDEX];
            int ok = 1;

            printf("Enter file name: ");
            scanf("%s", name);
            printf("Enter index block number: ");
            scanf("%d", &indexBlock);
            printf("Enter number of blocks: ");
            scanf("%d", &n);

            if (indexBlock < 0 || indexBlock >= MAX_BLOCKS || used[indexBlock]) {
                printf("Invalid or used index block.\n");
                continue;
            }
            if (n <= 0 || n > MAX_INDEX) {
                printf("Invalid number of blocks.\n");
                continue;
            }

            printf("Enter %d block numbers (0 to %d):\n", n, MAX_BLOCKS - 1);
            for (int i = 0; i < n; i++) {
                scanf("%d", &tempBlocks[i]);
                if (tempBlocks[i] < 0 || tempBlocks[i] >= MAX_BLOCKS || used[tempBlocks[i]] || tempBlocks[i] == indexBlock) {
                    ok = 0;
                }
                for (int j = 0; j < i; j++) {
                    if (tempBlocks[i] == tempBlocks[j]) {
                        ok = 0;
                    }
                }
            }

            if (!ok) {
                printf("Allocation failed: invalid or already used block(s).\n");
                continue;
            }

            strcpy(files[fileCount].name, name);
            files[fileCount].indexBlock = indexBlock;
            files[fileCount].count = n;

            used[indexBlock] = 1;
            for (int i = 0; i < n; i++) {
                files[fileCount].blocks[i] = tempBlocks[i];
                used[tempBlocks[i]] = 1;
            }

            fileCount++;
            printf("File allocated successfully using indexed allocation.\n");
        } else if (choice == 2) {
            printf("\nFile Name\tIndex\tBlocks\n");
            for (int i = 0; i < fileCount; i++) {
                printf("%s\t\t%d\t", files[i].name, files[i].indexBlock);
                for (int j = 0; j < files[i].count; j++) {
                    printf("%d ", files[i].blocks[j]);
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
