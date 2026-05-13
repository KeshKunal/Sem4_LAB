/*
==================================================
MEMORY MAP / QUICK REVISION
==================================================

Goal:
- Show IPC using message passing.
- Producer sends items through a message queue.
- Consumer receives items from the queue.

Logic:
1. Create message queue.
2. Fork: parent = producer, child = consumer.
3. Producer sends fixed items.
4. Consumer reads and prints items.

Key Variables:
- msgid -> message queue id
- type -> message type
- data -> data sent

Algorithm Used:
- Producer-Consumer using System V message queue

==================================================
*/

/*
Program Name: Producer Consumer using Message Passing
Aim: Write a C program to demonstrate Inter-Process Communication (IPC) using message passing by implementing the Producer Consumer problem.
Algorithm:
1. Create message queue.
2. Fork producer and consumer.
3. Producer sends fixed items.
4. Consumer receives and prints items.
Compilation: gcc 2_producer_consumer_message_passing.c -o pc_msg
Execution: ./pc_msg
*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <unistd.h>

// Structure for message
struct message
{
    long type;
    int data;
};

int main()
{
    int msgid;
    struct message msg;

    // Input Section
    // No user input; fixed 5 items are produced and consumed.

    // Processing Section
    // Create message queue
    msgid = msgget(IPC_PRIVATE, IPC_CREAT | 0666);

    // Create child process
    if(fork() == 0)
    {
        // Consumer
        for(int i = 1; i <= 5; i++)
        {
            // Receive message
            msgrcv(msgid, &msg, sizeof(int), 1, 0);

            // Output Section
            printf("Consumed: %d\n", msg.data);

            sleep(1);
        }
    }
    else
    {
        // Producer
        msg.type = 1;

        for(int i = 1; i <= 5; i++)
        {
            msg.data = i;

            // Send message
            msgsnd(msgid, &msg, sizeof(int), 0);

            // Output Section
            printf("Produced: %d\n", i);

            sleep(1);
        }

        wait(NULL);

        // Delete message queue
        msgctl(msgid, IPC_RMID, NULL);
    }

    /* Time Complexity: O(n) for n items (here n = 5). */
    return 0;
}

/*
Sample Input:
No input

Sample Output:
Produced: 1
Consumed: 1
Produced: 2
Consumed: 2
Produced: 3
Consumed: 3
Produced: 4
Consumed: 4
Produced: 5
Consumed: 5
*/
