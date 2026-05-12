#include <stdio.h>
#include <stdlib.h>

#define MAX_REQ 50

int compare_ints(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    return x - y;
}

int main(void) {
    int n, head, diskSize;
    int req[MAX_REQ];
    char direction;

    printf("Disk Scheduling (FCFS and SCAN)\n");
    printf("Enter number of requests: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX_REQ) {
        printf("Invalid number of requests.\n");
        return 1;
    }

    printf("Enter request sequence:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &req[i]);
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);
    printf("Enter disk size (number of cylinders): ");
    scanf("%d", &diskSize);
    printf("Enter direction for SCAN (l/r): ");
    scanf(" %c", &direction);

    int total = 0;
    int current = head;
    for (int i = 0; i < n; i++) {
        total += abs(req[i] - current);
        current = req[i];
    }
    printf("\nFCFS Total Head Movement: %d\n", total);

    int left[MAX_REQ], right[MAX_REQ];
    int lcount = 0, rcount = 0;
    for (int i = 0; i < n; i++) {
        if (req[i] < head) {
            left[lcount++] = req[i];
        } else {
            right[rcount++] = req[i];
        }
    }

    qsort(left, lcount, sizeof(int), compare_ints);
    qsort(right, rcount, sizeof(int), compare_ints);

    total = 0;
    current = head;
    printf("SCAN Order: ");

    if (direction == 'l' || direction == 'L') {
        for (int i = lcount - 1; i >= 0; i--) {
            printf("%d ", left[i]);
            total += abs(left[i] - current);
            current = left[i];
        }
        if (current != 0) {
            total += abs(current - 0);
            current = 0;
        }
        for (int i = 0; i < rcount; i++) {
            printf("%d ", right[i]);
            total += abs(right[i] - current);
            current = right[i];
        }
    } else {
        for (int i = 0; i < rcount; i++) {
            printf("%d ", right[i]);
            total += abs(right[i] - current);
            current = right[i];
        }
        if (current != diskSize - 1) {
            total += abs(current - (diskSize - 1));
            current = diskSize - 1;
        }
        for (int i = lcount - 1; i >= 0; i--) {
            printf("%d ", left[i]);
            total += abs(left[i] - current);
            current = left[i];
        }
    }

    printf("\nSCAN Total Head Movement: %d\n", total);

    return 0;
}
