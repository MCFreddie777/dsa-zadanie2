//
// Created by František Gič on 11/04/2020.
//

#include <stdio.h>
#include <stdlib.h>

#define hash(table, key) (key%table->size)
#define load_factor(keys, size) (keys / (size * 1.0))
#define MAX_LOAD_FACTOR 0.5

typedef struct HashTable {
    int keys;
    int size;
    int *table;
} HashTable;

void insert (HashTable **hashTable, int key);

/**
 * Creates and allocates the memory for a new hashtable
 *
 * @param size The size of the new hashtable
 * @return Pointer to a newly created hashtable
 */
HashTable *new (int size) {
    HashTable *temp = (HashTable *) malloc(sizeof(HashTable));
    temp->keys = 0;
    temp->size = size;
    temp->table = (int *) calloc(size, sizeof(int));
    return temp;
}

/**
 * Create a new hashtable with double the size
 * and rehash the old keys into the new one
 *
 * @param table The table to be resized and rehashed
 * @return Pointer to a new allocated hashTable
 */
HashTable *rehash (HashTable *hashTable) {
    HashTable *temp = new(hashTable->size * 2);
    
    for (int i = 0; i < hashTable->size; i++)
        if (hashTable->table[i] != 0)
            insert(&temp, hashTable->table[i]);
    
    free(hashTable);
    return temp;
}

/**
 * Algorithm of quadratic probing inspired by
 * explanation of hashing algorithms by:
 * https://www.youtube.com/watch?v=mFY0J5W8Udk
 */
int probe (HashTable *hashTable, int key) {
    int index = hash(hashTable, key);
    int i = 0;
    while (hashTable->table[(index + i * i) % hashTable->size] != 0)
        i++;
    return (index + i * i) % hashTable->size;
}

/**
 * Function for inserting key into the hashtable
 *
 * @param hashTable Pointer to a hashTable structure
 * @param key A key to be inserted
 */
void insert (HashTable **hashTable, int key) {
    
    /*
     * If load factor of hashtable would be greater than 0.5 after insertion
     * rehash the table first
     */
    float lf = load_factor(((*hashTable)->keys + 1), (*hashTable)->size);
    if (lf > MAX_LOAD_FACTOR)
        *hashTable = rehash(*hashTable);
    
    // Find the suitable position in the table
    int index = hash((*hashTable), key);
    if ((*hashTable)->table[index] != 0)
        index = probe(*hashTable, key);
    
    // Insert the key
    (*hashTable)->table[index] = key;
    (*hashTable)->keys++;
}

/**
 * Function which searches for the given key
 *
 * @param hashTable HashTable to be searched in
 * @param key The value to be looked for
 * @return The index of the given key or 0 in case of element not being found
 */
int search (HashTable *hashTable, int value) {
    int index = hash(hashTable, value);
    int i = 0;
    
    while (hashTable->table[(index + i * i) % hashTable->size] != value) {
        // If the place is empty , it means the element does not exist in the hashtable
        if (hashTable->table[(index + i * i) % hashTable->size] == 0)
            return 0;
        else
            // Keep searching by increasing the i
            i++;
    }
    
    return (index + i * i) % hashTable->size;
}

int main () {
    HashTable *hashTable = new(10);
    
    insert(&hashTable, 76);
    insert(&hashTable, 56);
    insert(&hashTable, 93);
    insert(&hashTable, 40);
    insert(&hashTable, 35);
    insert(&hashTable, 47);
    insert(&hashTable, 57);
    insert(&hashTable, 23);
    
    int find = 47;
    printf("Key of %d found at %d\n", find, search(hashTable, find));
    find = 23;
    printf("Key of %d found at %d\n", find, search(hashTable, find));
    
    return 0;
}

