#include "aiv_dict.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Bernstein classic hash
static size_t djb33x_hash(void *key, size_t keylen) {
    register int hash = 5381;
    int i;

    // register is used to optimize the code
    unsigned char *key_as_num = (unsigned char *)key;

    // iterate over the key
    for (i = 0; i < keylen; i++) {
        hash = ((hash << 5) + hash) ^ key_as_num[i];
    }
    return hash;
}

aiv_dict_t aiv_dict_new() {
    // create a new dictionary with 10 buckets and the djb33x hash function
    return aiv_dict_new_with_params(10, djb33x_hash);
}

aiv_dict_t aiv_dict_new_with_params(size_t hashmap_size, size_t (*hash_func)(void *key, size_t keylen)) {
    // create a new dictionary with the given size and hash function
    aiv_dict_t dict;
    dict.hashmap_size = hashmap_size;
    dict.hash_func = hash_func;
    // allocate memory for the hashmap
    dict.hashmap = (void**)calloc(hashmap_size, sizeof(void*));
    // return the dictionary
    return dict;
}

void aiv_dict_put(aiv_dict_t* dict, void* key, size_t key_size, void* value) {
    // hash the key
    size_t hash =  dict->hash_func(key, key_size);
    // get the index of the hashmap
    size_t hash_index = hash % dict->hashmap_size;

    // Scenario 1: hash(key) not present
    if (!dict->hashmap[hash_index]) {
        aiv_dict_node_t* node = malloc(sizeof(aiv_dict_node_t));
        //node->key = key;
        node->key = malloc(sizeof(key_size));
        memcpy(node->key, key, key_size);
        node->key_size = key_size;
        node->value = value;
        node->next = NULL;
        dict->hashmap[hash_index] = node;
    } else {  // Scenario 2: hash(key) present

        // key already exists (update value)
        aiv_dict_node_t* node = dict->hashmap[hash_index];
        aiv_dict_node_t* last = NULL;
        while(node) {
            last = node;

            //if (node->key == key) {
            if (node->key_size == key_size && !memcmp(node->key, key, key_size)) {
                node->value = value;
                return;
            }
            node = node->next;
        }

        // key not exists (to be added)
        aiv_dict_node_t* new_node = malloc(sizeof(aiv_dict_node_t));
        //new_node->key = key;
        new_node->key = malloc(sizeof(key_size));
        memcpy(new_node->key, key, key_size);
        new_node->key_size = key_size;
        new_node->value = value;
        new_node->next = NULL;

        last->next = new_node;
    }

}

void* aiv_dict_get(aiv_dict_t* dict, void* key, size_t key_size) {
    size_t hash = dict->hash_func(key, key_size);
    size_t hash_index = hash % dict->hashmap_size;
    
    aiv_dict_node_t* node = dict->hashmap[hash_index];
    while (node) {
        if (node->key_size == key_size && !memcmp(node->key, key, key_size)) {
            return node->value;
        }
        node = node->next;
    }
    return NULL;
}

void aiv_dict_remove(aiv_dict_t* dict, void* key, size_t key_size) {
    size_t hash = dict->hash_func(key, key_size);
    size_t hash_index = hash % dict->hashmap_size;
    
    aiv_dict_node_t* node = dict->hashmap[hash_index];
    aiv_dict_node_t* prev = NULL;
    
    while (node) {
        if (node->key_size == key_size && !memcmp(node->key, key, key_size)) {
            // if node is found, remove it
            if (prev) {
                prev->next = node->next;
            } else {
                // if prev is NULL, it means that the node is the first in the list
                dict->hashmap[hash_index] = node->next;
            }
            
            free(node->key);
            free(node);
            return;
        }
        prev = node;
        node = node->next;
    }
}

size_t aiv_dict_size(aiv_dict_t* dict) {
    size_t count = 0;
    // iterate over the hashmap
    for (size_t i = 0; i < dict->hashmap_size; i++) {
        aiv_dict_node_t* node = dict->hashmap[i];
        while (node) {
            // count the number of nodes in the list
            count++;
            node = node->next;
        }
    }
    return count;
}

bool aiv_dict_contains_key(aiv_dict_t* dict, void* key, size_t key_size) {
    size_t hash = dict->hash_func(key, key_size);  // hash the key
    // get the index of the hashmap
    size_t hash_index = hash % dict->hashmap_size;
    
    aiv_dict_node_t* node = dict->hashmap[hash_index]; // get the node at the index
    // iterate over the list
    while (node) {
        // if the key is found, return true
        if (node->key_size == key_size && !memcmp(node->key, key, key_size)) {
            return true;
        }
        // iterate to the next node
        node = node->next;
    }
    // if the key is not found, return false
    return false;
}

void aiv_dict_destroy(aiv_dict_t* dict) {
    // iterate over the hashmap
    for (size_t i = 0; i < dict->hashmap_size; i++) {
        // get the node at the index
        aiv_dict_node_t* node = dict->hashmap[i];
        // iterate over the list
        while (node) {
            // get the next node
            aiv_dict_node_t* next = node->next;
            free(node->key);
            free(node);
            // iterate to the next node
            node = next;
        }
    }
    // free the hashmap
    free(dict->hashmap);
    // set the hashmap to NULL
    dict->hashmap = NULL;
    // set the hashmap size to 0
    dict->hashmap_size = 0;
}