//
// Created by František Gič on 12/04/2020.
//

#include "quadratic-probing.c"
#include <string.h>
#include <time.h>

/**
 * Simple assertions
 *
 * @param hashTable A HashTable to be searched
 * @param operation not.exist | exist | have.key
 * @param key
 */
void should (HashTable *hashTable, char *operation, int key) {
    
    if (!strcmp(operation, "not.exist")) {
        int result = search(hashTable, key);
        if (result != 0) {
            printf("%d does somehow exist in the table on position %d!\n", key, result);
            exit(1);
        }
        else
            printf("should(%s): OK. %d does not exist in table.\n", operation, key);
    }
    
    if (!strcmp(operation, "exist")) {
        int result = search(hashTable, key);
        if (result == 0) {
            printf("Value not found for key %d!\n", key);
            exit(1);
        }
        else
            printf("should(%s): OK. %d exists in table on position %d\n", operation, key, result);
    }
    
    if (!strcmp(operation, "have.value")) {
        int result = hashTable->table[search(hashTable, key)];
        if (result != key) {
            printf("Incorrect value returned! (Should have value %d, returned %d)\n", key, result);
            exit(1);
        }
        else
            printf("should(%s): OK. Hashtable with key %d has value %d.\n", operation, key, key);
    }
}

void test () {
    HashTable *hashTable = new(10);
    
    insert(&hashTable, 76);
    insert(&hashTable, 56);
    insert(&hashTable, 93);
    insert(&hashTable, 40);
    insert(&hashTable, 35);
    
    print(hashTable);
    should(hashTable, "exist", 35);
    
    insert(&hashTable, 47);
    insert(&hashTable, 23);
    insert(&hashTable, 5);
    
    print(hashTable);
    should(hashTable, "exist", 35);
    should(hashTable, "exist", 23);
    should(hashTable, "not.exist", 50);
    should(hashTable, "have.value", 23);
    
    free_hashtable(hashTable);
}

void test_time () {
    HashTable *hashTable = new(10);
    
    float startTime = (float) clock() / CLOCKS_PER_SEC;
    
    for (int i = 0; i < 1000; i++) {
        insert(&hashTable, i);
    }
    
    float endTime = (float) clock() / CLOCKS_PER_SEC;
    printf("(%fs)\n", endTime - startTime);
    print(hashTable);
}

int main () {
//    test();
    test_time();
    return 0;
}

