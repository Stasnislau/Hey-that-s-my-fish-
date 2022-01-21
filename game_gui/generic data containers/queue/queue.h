/*
 * KEY REMARKS
 * - the queue is implemented using doubly liked lists
 * - it is a generic data container - can store any type of data, by only one type at a time 
 * - to use the queue, the construtor is needed to be called - it returns a pointer to the memory allocated for the queue
 * - all memory managment is done behind the scenes, however deconstructor is needed to be called in order to free all the memory taken up by the queue
 */
struct queue_node {
    void *data;
    struct queue_node *next;    // the first element points to NULL
    struct queue_node *prev;    // the last element points to NULL
};

typedef struct queue_node queue_node;

typedef struct {
    queue_node *front;  // pointer to the front  
    queue_node *back;   // pointer to the back  
    int size;           // number of elements in the queue
    int elemSize;
} queue;

// creates a new queue
// arguments: size in bytes of the data to be stored in the queue
// returs: a pointer to the memory allocated for the queue
queue *queue_create(int elemSize);
// frees the memory taken by the queue
// argurments: pointer to the queue
void queue_destroy(queue *q);
// checkes if the queue is not empty
// arguments: pointer to the queue
// returns: 1 if queue is empty, 0 otherwise
int queue_empty(queue *q);
// pushes a new element onto a queue, copies the contents (shallow copy) of the data at address given
// arguments: poiner to the queue, address of the data 
void queue_push(queue *q, void *elemAddr);
// pop last element from the queue
// argurments: pointer to the queue
void queue_pop(queue *q);
// copies the data at the front of the queue to the variable at address elemAddr
// arguments: pointer to the queue, address of the variable
void queue_front(queue *q, void *elemAddr);
