#ifndef AIV_LIST
#define AIV_LIST
#include <stddef.h>
#include <stdbool.h>

// define the node
typedef struct aiv_list_node {
    void* data;
    struct aiv_list_node* prev;
    struct aiv_list_node* next;
} aiv_list_node_t;

// define the list
typedef struct aiv_list {
    // head of the list
    aiv_list_node_t* head;
    // tail of the list
    aiv_list_node_t* tail;
    // count of the list
    size_t count;
} aiv_list_t;

// create a new list
aiv_list_t aiv_list_new();

// destroy the list
void aiv_list_destroy(aiv_list_t* list);
// create a new node
aiv_list_node_t* aiv_list_node_new(void* data);

// add an item to the list
void aiv_list_add(aiv_list_t* list, void* item);

// check if the list is empty
bool aiv_list_is_empty(aiv_list_t* list);

// get the size of the list
size_t aiv_list_size(aiv_list_t* list);

// get the item at the index
void* aiv_list_get_at(aiv_list_t* list, size_t index);

// set the item at the index
void aiv_list_set_at(aiv_list_t* list, size_t index, void* item);

// remove an item from the list
void aiv_list_remove(aiv_list_t* list, void* item);

// remove the item at the index
void aiv_list_remove_at(aiv_list_t* list, size_t index);

#endif //AIV_LIST