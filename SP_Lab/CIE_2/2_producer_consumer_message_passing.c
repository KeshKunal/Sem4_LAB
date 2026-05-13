/*
==================================================
MEMORY MAP / QUICK REVISION
==================================================

Goal:
- Show IPC using message passing.
- Producer sends items through a message queue.
- Consumer receives items until a stop message arrives.

Logic:
1. Create message queue.
2. Fork: parent = producer, child = consumer.
3. Producer sends data, then a stop value.
4. Consumer reads and prints data, then exits.

Key Variables:
- msgid -> message queue id
- mtype -> message type
- value -> data sent

Algorithm Used:
- Producer-Consumer using System V message queue

==================================================
*/

/*
Program Name: Producer Consumer using Message Passing
Aim: Write a C program to demonstrate Inter-Process Communication (IPC) using message passing by implementing the Producer Consumer problem.
Algorithm:
1. Get number of items.
2. Create message queue.
3. Producer sends items and a stop message.
4. Consumer receives and prints items.
Compilation: gcc 2_producer_consumer_message_passing.c -o pc_msg
Execution: ./pc_msg
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_ITEMS 20

struct msg_buffer {
    long mtype;
    int value;
};

int main(void)
{
    int msgid;
    int n, i;
    struct msg_buffer message;

    // Input Section
    printf("Enter number of items to produce (1-%d): ", MAX_ITEMS);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_ITEMS) {
        printf("Invalid input.\n");
        return 0;
    }

    // Processing Section
    msgid = msgget(IPC_PRIVATE, IPC_CREAT | 0666);
    if (msgid == -1) {
        printf("Message queue creation failed.\n");
        return 0;
    }

    if (fork() == 0) {
        /* Consumer process */
        while (1) {
            if (msgrcv(msgid, &message, sizeof(int), 1, 0) == -1) {
                printf("Message receive failed.\n");
                return 0;
            }
            if (message.value == -1) {
                break;
            }
            // Output Section
            printf("Consumer received: %d\n", message.value);
        }
        return 0;
    } else {
        /* Producer process */
        message.mtype = 1;
        for (i = 1; i <= n; i++) {
            message.value = i;
            msgsnd(msgid, &message, sizeof(int), 0);
            // Output Section
            printf("Producer sent: %d\n", i);
        }
        message.value = -1; /* stop message */
        msgsnd(msgid, &message, sizeof(int), 0);

        wait(NULL);
        msgctl(msgid, IPC_RMID, NULL);
    }

    /* Time Complexity: O(n) for n messages. */
    return 0;
}

/*
Sample Input:
Enter number of items to produce (1-20): 3

Sample Output:
Producer sent: 1
Producer sent: 2
Producer sent: 3
Consumer received: 1
Consumer received: 2
Consumer received: 3
*/
