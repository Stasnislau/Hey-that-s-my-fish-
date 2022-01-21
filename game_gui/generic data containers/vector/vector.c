#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"
#define kInitialAllocationSize 4

/*
    - the constuctor needs size of sigle element in bytes up front
    - we choose allocate memory for 4 element at the beginning - it is an arbitrary number
    - the doubling technique is used when vector is full
*/
vector *vector_create(int elemSize)
{
    vector *v = malloc(sizeof(vector));
    assert(v != NULL);
    assert(elemSize > 0);
    v->elemSize = elemSize;
    v->logLength = 0;
    v->allocLength = kInitialAllocationSize;
    v->elems = malloc(kInitialAllocationSize * elemSize);
    assert(v->elems != NULL);
    return v;
}

/*
    - frees the memory allocated for elements
    - alos free the vector itself - the clinet should not call free on the vector as it will already by freed
    - if the vector is not empty, the destructor empties is first
*/
void vector_destroy(vector *v)
{
    while (!vector_empty(v))
        vector_pop(v);
    free(v->elems);
    free(v);
}

int vector_empty(vector *v)
{
    return v->logLength == 0;
}

int vector_size(vector *v)
{
    return v->logLength;
}

/*
    - The last three lines replicate the byte pattern addressed by elemAddr placing it at the manually computed address within raw storage.
    - Note that we do a shallow copy. If the v->elemSize bytes copied in are pointers to dynamically allocated memory, then ownership of that memory is transferred from the client to the implementation.
    - The conditional reallocation only applies if we’ve previously saturated memory. Type ‘man realloc’ at the command line to get the full documentation on how realloc works.
*/
void vector_push(vector *v, void *elemAddr) {
    void *destAddr;
    if (v->logLength == v->allocLength) {
        v->allocLength *= 2;
        v->elems = realloc(v->elems, v->allocLength * v->elemSize);
        assert(v->elems != NULL);
    }
    
    destAddr = (char *)v->elems + v->logLength * v->elemSize;
    memcpy(destAddr, elemAddr, v->elemSize);
    v->logLength++;
}  

/*
    - We don't call relloc to reduce the size of the elements array, because in practice realloc punts on any request to shrink the array anyway, to it's typically a wasted effort.
 */
void vector_pop(vector *v) 
{
    assert(!vector_empty(v));
    v->logLength--;
}

void vector_at_n(vector *v, void *elemAddr, int n)
{
    void *sourceAddr;
    assert(!vector_empty(v));
    sourceAddr = (char *)v->elems + n * v->elemSize;
    memcpy(elemAddr, sourceAddr, v->elemSize);
}

void vector_back(vector *v, void *elemAddr)
{
    assert(!vector_empty(v));
    vector_at_n(v, elemAddr, v->logLength - 1);
}
