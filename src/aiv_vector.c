#include "aiv_vector.h"
#include <stddef.h>
#include <stdlib.h>

aiv_vector_t aiv_vector_new() {
    aiv_vector_t vector;
    vector.count = 0;
    vector.capacity = 10;
    vector.items = malloc(sizeof(void*) * vector.capacity);
    return vector;
}

void aiv_vector_destroy(aiv_vector_t* vector) {
    if (!vector->items) return;
    
    free(vector->items);
    vector->items = NULL;
    vector->count = 0;
    vector->capacity = 0;
}

void aiv_vector_add(aiv_vector_t* vector, void* item) {
    if (vector->count == vector->capacity) {
        vector->capacity = vector->capacity * 2;
        vector->items = realloc(vector->items, sizeof(void*) * vector->capacity);    
    }

    size_t new_index = vector->count;
    vector->count++;
    //vector->items = realloc(vector->items, sizeof(void*) * vector->count);
    vector->items[new_index] = item;
}

void* aiv_vector_at(aiv_vector_t* vector, size_t index) {
    if (index >= vector->count) {
        return NULL;
    }
    return vector->items[index];
}

/*
void aiv_vector_sort_bubble(
    aiv_vector_t* vector, 
    int (*comparator)(void*, void*) ) {

        for(size_t i = 0; i < vector->count; ++i) {       // COUNT
            //void* item1 = vector->items[i]; //BUG

            for(size_t j = 0; j < vector->count; ++j) {      // COUNT  
                void* item1 = vector->items[i];                // 1
                void* item2 = vector->items[j];                // 1

                int res = comparator(item1, item2);            // 1
                if (res > 0) {                                 // 1
                    void* temp = item1;                        // 1
                    vector->items[i] = item2;                  // 1
                    vector->items[j] = temp;                   // 1
                 }
            }    
        }  
}

   6 * COUNT * COUNT 

   6 * N * N => 6 * N^2 ~ N^2 => O(N^2)
*/

void aiv_vector_sort_bubble(aiv_vector_t *vector,
                       int (*comparator)(void *, void *)) {
  for (size_t i = 0; i < vector->count; i++) {
    for (size_t j = i+1; j < vector->count; j++) {
      int comp = comparator(vector->items[i], vector->items[j]);  
      if (comp < 0) {
        void *tmp = vector->items[i];
        vector->items[i] = vector->items[j];
        vector->items[j] = tmp;
      }
    }
  }
}