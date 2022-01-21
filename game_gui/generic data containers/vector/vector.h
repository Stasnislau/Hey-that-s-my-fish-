/*
 * KEY REMARKS
 * - the vector is implemented using dynamic arrays
 * - it is a generic data container,  but it can store only one type of data at a time 
 * - to use the vector, the construtor is needed to be called - it returns a pointer to the memory allocated for it
 * - all memory managment is done behind the scenes, however deconstructor is needed to be called in order to free all the memory taken up by the vector
 * - doubling technique is used in case of vector saturation
*/

typedef struct {
    void *elems;        // pointer to the data
    int elemSize;       // number of bytes a single element takes
    int logLength;      // number of elements in the vector
    int allocLength;    // for how many elements the vector allocated memory 
} vector;

// allocates new memory for the vector
// arguments: size if bytes of a sigle element to be stored in the vector
// returns: pointer to the newly created vector
vector *vector_create(int elemSize);

// frees all the memory taken up by the vector
// arguments: pointer to the vector
void vector_destroy(vector *v);

// checks if the vector is empty
// arguments: poiner to the vector
// returns: 1 if vector is empty, 0 otherwise
int vector_empty(vector *v);

// arguments: pointer to the vector
// returns: the number of elements in the vector
int vector_size(vector *v);

// pushes a new element into the vector, copies (shallow copy) the data at address elemAddr
// arguments: pointer to the vector, pointer to the data
void vector_push(vector *v, void *elemAddr);

// pops the last element from the vector
// arguments: pointer to the vector
void vector_pop(vector *v);

// copies the data stored in the vector's last element to the variable at address elemAddr
// arguments: pointer to the vector, address of the variable
void vector_back(vector *v, void *elemAddr);

// copies the data stored in the vector's n-th element to the variable at address elemAddr
// arguments: pointer to the vector, address of the variable
void vector_at_n(vector *v, void *elemAddr, int n);

