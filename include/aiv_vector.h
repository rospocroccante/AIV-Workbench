#ifndef AIV_VECTOR
#define AIV_VECTOR

typedef struct aiv_vector {
    void** items;
    size_t count;
    size_t capacity;
} aiv_vector_t;

// Alternative separated from struct definition
// typedef struct aiv_vector aiv_vector;

aiv_vector_t aiv_vector_new();
void aiv_vector_destroy(aiv_vector_t* vector);

void aiv_vector_add(aiv_vector_t* vector, void* item);

void* aiv_vector_at(aiv_vector_t* vector, size_t index);

void aiv_vector_sort_bubble(aiv_vector_t* vector, int (*comparator)(void* item1, void* item2) );

//set
#endif