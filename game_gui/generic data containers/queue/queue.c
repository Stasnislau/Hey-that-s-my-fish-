#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

queue *queue_create(int elemSize)
{
    queue *q = malloc(sizeof(queue));
    assert(q != NULL);
    q->size = 0;
    assert(elemSize > 0);
    q->elemSize = elemSize;
    return q;
}

// all the memory taken up by the queue is freed, the queue is emptied if needed
void queue_destroy(queue *q)
{
    while (!queue_empty(q))
        queue_pop(q);
    free(q);
}

int queue_empty(queue *q)
{
    return q->size == 0;
}

int queue_size(queue *q)
{
    return q->size;
}

void queue_push(queue *q, void *elemAddr) {
    queue_node *new_back = malloc(sizeof(queue_node));
    assert(new_back != NULL);
    // insert new element to the queue
    new_back->next = q->back;
    // if te queue has at least one element
    if (q->size++)
        q->back->prev = new_back;
    else
        q->front = new_back;
    q->back = new_back;
    // number of bytes for every element in the stack is the same so we write the 3rd arugment as below
    new_back->data = malloc(q->elemSize);
    assert(new_back->data != NULL);
    memcpy(new_back->data, elemAddr, q->elemSize);
}

void queue_pop(queue *q)
{ 
    // we create a temporary pointer to store the adress to the node which we want to delete
    queue_node *temp = q->front;
    q->front = q->front->prev;
    if (q->front)
        q->front->next = NULL;
    free(temp->data);
    free(temp);
    q->size--;
}

void queue_front(queue *q, void *elemAddr) 
{
    memcpy(elemAddr, q->front->data, q->elemSize);
}
