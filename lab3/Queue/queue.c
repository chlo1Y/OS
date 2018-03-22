/* This is the shell you must fill in or replace in order to complete
   this project.  Do not forget to include your name in the initial
   comments in this file.
   Zesun Yang and Yuchen Wang
*/
#include <stdio.h>
#include <stdlib.h>
#include "./queue.h"
void deleteQueue(Queue *Aqueue);
Bool enqueue(Queue *Aqueue, int processId, int arrivalTime,
             int serviceTime, int remainingTime);
int printQueue(Queue Aqueue);
int queueSize(Queue Aqueue);
Node dequeue(Queue *Aqueue);

void deleteQueue(Queue *Aqueue) {
    while ((*Aqueue).head != NULL) {
        dequeue(Aqueue);
    }
}

Bool enqueue(Queue *Aqueue, int processId, int arrivalTime,
        int serviceTime, int remainingTime) {
    Node* a = (Node *)malloc(sizeof(Node));
    (*a).processId = processId;
    (*a).arrivalTime = arrivalTime;
    (*a).serviceTime = serviceTime;
    (*a).remainingTime = remainingTime;
    (*a).next = NULL;
    if ((*Aqueue).head == NULL) {
        (*Aqueue).head = a;
    } else {
        (*(*Aqueue).tail).next = a;
    }
        (*Aqueue).tail = a;

    if (Aqueue == NULL) {
        return FALSE;
    }
    return TRUE;
}
int printQueue(Queue Aqueue) {
    int count = 0;
    Node *a = Aqueue.head;
    while  (a != NULL) {
        printf("%d\t%d\t%d\t%d\n",
            (*a).processId,
            (*a).arrivalTime,
            (*a).serviceTime,
            (*a).remainingTime);
        count++;
        a = (*a).next;
    }
    return count;
}
int queueSize(Queue Aqueue) {
    int count = 0;
    Node *a = Aqueue.head;
    while (a != NULL) {
        count++;
        a = (*a).next;
    }
    return count;
}

Node dequeue(Queue *Aqueue) {
    Node anItem;
    Node* head = (*Aqueue).head;
    if (head == NULL) {
        anItem.processId = -1;
        return anItem;
    }

    Node toReturn = (*head);
    if ((*head).next != NULL) {
        (*Aqueue).head = (*head).next;
    } else {
        (*Aqueue).head = NULL;
        (*Aqueue).tail = NULL;
    }
     free(head);
     return toReturn;
}
