#include <stdio.h>
#include <string.h>

#define MAX_BLOCKS 50
#define MAX_FILES  20

typedef struct {
    char name[30];
    int start;
    int length;
} File;

int main(void) {
    int used[MAX_BLOCKS] = {0};
    File files[MAX_FILES];
    int fileCount = 0;
    int choice;

    while (1) {
        printf("\nContiguous File Allocation\n");
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
            int length, i, j, start = -1;

            printf("Enter file name: ");
            scanf("%s", name);
            printf("Enter number of blocks needed: ");
            scanf("%d", &length);

            for (i = 0; i <= MAX_BLOCKS - length; i++) {
                int free = 1;
                for (j = 0; j < length; j++) {
                    if (used[i + j]) {
                        free = 0;
                        break;
                    }
                }
                if (free) {
                    start = i;
                    break;
                }
            }

            if (start == -1) {
                printf("Allocation failed: no contiguous space available.\n");
            } else {
                for (i = start; i < start + length; i++) {
                    used[i] = 1;
                }

                strcpy(files[fileCount].name, name);
                files[fileCount].start = start;
                files[fileCount].length = length;
                fileCount++;

                printf("File allocated from block %d to %d\n", start, start + length - 1);
            }
        } else if (choice == 2) {
            int i;
            printf("\nFile Name\tStart\tLength\tBlocks\n");
            for (i = 0; i < fileCount; i++) {
                printf("%s\t\t%d\t%d\t", files[i].name, files[i].start, files[i].length);
                for (int b = files[i].start; b < files[i].start + files[i].length; b++) {
                    printf("%d ", b);
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
