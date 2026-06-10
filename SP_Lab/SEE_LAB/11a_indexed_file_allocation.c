
#include <stdio.h>

int main()
{
    int n;
    int indexBlock[10];
    int blocks[10][20];
    int count[10];

    printf("Enter number of files: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++)
    {
        printf("\nEnter index block for File-%d: ", i + 1);
        scanf("%d", &indexBlock[i]);

        printf("Enter number of blocks used: ");
        scanf("%d", &count[i]);

        printf("Enter block numbers: ");
        for(int j = 0; j < count[i]; j++)
        {
            scanf("%d", &blocks[i][j]);
        }
    }

    printf("\nFile\tIndex Block\tAllocated Blocks\n");

    for(int i = 0; i < n; i++)
    {
        printf("%d\t%d\t\t", i + 1, indexBlock[i]);

        for(int j = 0; j < count[i]; j++)
        {
            printf("%d ", blocks[i][j]);
        }

        printf("\n");
    }

    return 0;
}