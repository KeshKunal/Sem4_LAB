/*
==================================================
MEMORY MAP / QUICK REVISION
==================================================

Goal:
- Demonstrate IPC using message passing.
- Producer sends items via message queue.

Logic:
1. Create message queue.
2. Fork into producer and consumer.
3. Producer sends items; consumer receives.

Algorithm Used:
- Producer-Consumer using System V message queue

==================================================
*/

/*
Program Name: Producer Consumer using Message Passing
Aim: Write a C program to demonstrate IPC using message passing by implementing the Producer-Consumer problem.
Algorithm:
1. Create message queue.
2. Fork producer and consumer.
3. Producer sends fixed items; consumer receives them.
Compilation: gcc 6a_message_passing_producer_consumer.c -o pc_msg
Execution: ./pc_msg
*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <unistd.h>

struct message {
    long type;
    int data;
};

int main(void)
{
    int msgid;
    struct message msg;

    msgid = msgget(IPC_PRIVATE, IPC_CREAT | 0666);

    if (fork() == 0) {
        // Consumer
        for (int i = 1; i <= 5; i++) {
            // receive message
            msgrcv(msgid, &msg, sizeof(int), 1, 0);
            printf("Consumed: %d\n", msg.data);
            sleep(1);
        }
    } else {
        // Producer
        msg.type = 1;
        for (int i = 1; i <= 5; i++) {
            msg.data = i;
            // send message
            msgsnd(msgid, &msg, sizeof(int), 0);
            printf("Produced: %d\n", i);
            sleep(1);
        }

        wait(NULL);
        msgctl(msgid, IPC_RMID, NULL);
    }

    /* Time Complexity: O(n) for n items (here n = 5). */
    return 0;
}

/*
Sample Output:
Produced: 1
Consumed: 1
... (continues up to 5)
*/
