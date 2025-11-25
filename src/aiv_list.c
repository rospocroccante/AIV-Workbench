#include "aiv_list.h"
#include <stdlib.h>

// create a new list
aiv_list_t aiv_list_new() {
    aiv_list_t list;
    list.head = NULL;
    list.tail = NULL;
    list.count = 0;
    return list;
}

// destroy the list
void aiv_list_destroy(aiv_list_t* list) {
    // iterate over the list
    aiv_list_node_t* current = list->head;
    while(current) {
        // get the next node
        aiv_list_node_t* next = current->next;
        // free the current node
        free(current);
        // iterate to the next node
        current = next;
    }
}


// check if the list is empty
bool aiv_list_is_empty(aiv_list_t* list) {
    // return true if the list is empty
    return list->count == 0;
}

// add an item to the list
void aiv_list_add(aiv_list_t* list, void* item) {
    // create a new node
    aiv_list_node_t* node = (aiv_list_node_t*)malloc(sizeof(aiv_list_node_t));
    // set the data of the node
    node->data = item;
    // set the previous node to NULL
    node->prev = NULL;
    // set the next node to NULL
    node->next = NULL;

    // if the list is empty
    if (aiv_list_is_empty(list)) {
        // set the head and tail to the new node
        list->head = node;
        list->tail = node;
    } else {   //  node1 <-- node2  
        // get the previous node
        aiv_list_node_t* prev = list->tail;
        // set the previous node to the new node
        node->prev = prev;
        // set the next node to the new node
        prev->next = node;
        // set the tail to the new node
        list->tail = node;
    }

    // increment the count
    list->count++;
}


// get the size of the list
size_t aiv_list_size(aiv_list_t* list) {
    // return the count
    return list->count;
}

// get the item at the index
void* aiv_list_get_at(aiv_list_t* list, size_t index) {
    // if the index is out of range, return NULL
    if (index >= list->count) {
        return NULL;
    }
    
    aiv_list_node_t* current = list->head;
    // iterate over the list
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    // return the data of the node
    return current->data;
}

void aiv_list_set_at(aiv_list_t* list, size_t index, void* item) {
    if (index >= list->count) {
        return; // Indice fuori range
    }
    // iterate over the list
    aiv_list_node_t* current = list->head;
    // iterate over the list
    for (size_t i = 0; i < index; i++) {
        // get the next node
        current = current->next;
    }
    // set the data of the node
    current->data = item;
}

void aiv_list_remove(aiv_list_t* list, void* item) {
    aiv_list_node_t* current = list->head;
    
    while (current) {
        if (current->data == item) {
            // Trovato il nodo da rimuovere
            if (current->prev) {
                current->prev->next = current->next;
            } else {
                // È il head
                list->head = current->next;
            }
            
            if (current->next) {
                current->next->prev = current->prev;
            } else {
                // È il tail
                list->tail = current->prev;
            }
            
            free(current);
            list->count--;
            return;
        }
        current = current->next;
    }
}

void aiv_list_remove_at(aiv_list_t* list, size_t index) {
    if (index >= list->count) {
        return; // index out of range
    }
    
    aiv_list_node_t* current = list->head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    
    // unlink the node
    if (current->prev) {
        current->prev->next = current->next;
    } else {
        // if prev is NULL, it means that the node is the first in the list
        list->head = current->next;
    }
    
    if (current->next) {
        current->next->prev = current->prev;
    } else {
        // if next is NULL, it means that the node is the last in the list
        list->tail = current->prev;
    }
    
    // free the node
    free(current);
    // decrement the count
    list->count--;
}