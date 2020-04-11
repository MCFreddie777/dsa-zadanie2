//
// Created by František Gič on 11/04/2020.
//

#include <stdio.h>

#define SIZE 10
#define hash(key) (key%SIZE)

/*
 * Algorithm of quadratic probing inspired by
 * explanation of hashing algorithms by:
 * https://www.youtube.com/watch?v=mFY0J5W8Udk
 */

int probe (const int table[], int key) {
    int index = hash(key);
    int i = 0;
    while (table[(index + i * i) % SIZE] != 0)
        i++;
    return (index + i * i) % SIZE;
}

void insert (int table[], int key) {
    int index = hash(key);
    
    if (table[index] != 0)
        index = probe(table, key);
    
    table[index] = key;
}

int search (const int table[], int key) {
    int index = hash(key);
    int i = 0;
    
    while (table[(index + i * i) % SIZE] != key) {
        if (table[(index + i * i) % SIZE] == 0)
            return 0;
        i++;
    }
    
    return (index + i * i) % SIZE;
}

int main () {
    // TODO (fgic): Implement dynamic hashmap size
    
    int table[SIZE] = {0};
    
    insert(table, 76);
    insert(table, 93);
    insert(table, 40);
    insert(table, 35);
    insert(table, 47);
    
    printf("Key of 55 found at %d\n", search(table, 55));
    
    return 0;
}

