#include <stdio.h>

#define MAX_PAGES 50
#define MAX_SEGS  20

int main(void) {
    int pageSize, numPages;
    int pageTable[MAX_PAGES];

    printf("Paging Simulation\n");
    printf("Enter page size: ");
    scanf("%d", &pageSize);
    printf("Enter number of pages: ");
    scanf("%d", &numPages);

    if (pageSize <= 0 || numPages <= 0 || numPages > MAX_PAGES) {
        printf("Invalid paging values.\n");
        return 1;
    }

    printf("Enter frame number for each page:\n");
    for (int i = 0; i < numPages; i++) {
        printf("Page %d -> Frame: ", i);
        scanf("%d", &pageTable[i]);
    }

    while (1) {
        int la;
        printf("Enter logical address (-1 to stop): ");
        scanf("%d", &la);
        if (la < 0) {
            break;
        }

        int page = la / pageSize;
        int offset = la % pageSize;
        if (page < 0 || page >= numPages) {
            printf("Invalid logical address.\n");
            continue;
        }
        int pa = pageTable[page] * pageSize + offset;
        printf("Physical address: %d\n", pa);
    }

    int segCount;
    int base[MAX_SEGS], limit[MAX_SEGS];

    printf("\nSegmentation Simulation\n");
    printf("Enter number of segments: ");
    scanf("%d", &segCount);
    if (segCount <= 0 || segCount > MAX_SEGS) {
        printf("Invalid number of segments.\n");
        return 1;
    }

    for (int i = 0; i < segCount; i++) {
        printf("Segment %d base and limit: ", i);
        scanf("%d %d", &base[i], &limit[i]);
    }

    while (1) {
        int seg, offset;
        printf("Enter segment and offset (-1 -1 to stop): ");
        scanf("%d %d", &seg, &offset);
        if (seg < 0 && offset < 0) {
            break;
        }
        if (seg < 0 || seg >= segCount) {
            printf("Invalid segment number.\n");
            continue;
        }
        if (offset < 0 || offset >= limit[seg]) {
            printf("Segmentation fault (offset exceeds limit).\n");
            continue;
        }
        printf("Physical address: %d\n", base[seg] + offset);
    }

    return 0;
}
