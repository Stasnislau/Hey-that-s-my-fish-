#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

// allocates a memory for the stack and returns a pointer to it
stack *stack_create(int elemSize)
{
    stack *s = malloc(sizeof(stack));
    assert(s != NULL);
    s->size = 0;
    assert(elemSize > 0);
    s->elemSize = elemSize;
    return s;
}

// frees memory allocated during stack creation, empties the stack if needed
void stack_destroy(stack *s)
{
    while (!stack_empty(s))
        stack_pop(s);
    free(s);
}

int stack_empty(stack *s)
{
    return s->size == 0;
}

int stack_size(stack *s)
{
    return s->size;
}

// pushes a new element onto the top of the stack by copying the contents stored at itemAddr
void stack_push(stack *s, void *elemAddr) {
    stack_node *new_top = malloc(sizeof(stack_node));
    assert(new_top != NULL);
    // if the stack is empty s->top will be a NULL
    new_top->next = s->top;
    // number of bytes for every element in the stack is the same so we write the 3rd argument as below
    new_top->data = malloc(s->elemSize);
    assert(new_top->data != NULL);
    memcpy(new_top->data, elemAddr, s->elemSize);
    s->top = new_top;
    s->size++;
}

void stack_pop(stack *s)
{
    s->size--;
    // temporary pointer is created to store an adress to the node which we want to delete
    stack_node *temp = s->top;
    s->top = s->top->next;
    free(temp->data);
    free(temp);
}

void stack_top(stack *s, void *elemAddr) 
{
    memcpy(elemAddr, s->top->data, s->elemSize);
}
