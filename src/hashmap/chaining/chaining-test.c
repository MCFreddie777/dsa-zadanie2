//
// Created by František Gič on 12/04/2020.
//

#include "chaining.c"
#include <string.h>
#include <time.h>

/**
 * Simple assertions
 *
 * @param operation not.exist | exist
 * @param key
 */
void should (char *operation, int key) {
    
    if (!strcmp(operation, "not.exist")) {
        int result = search(key);
        if (result != 0) {
            printf("%d does somehow exist in the table on position %d!\n", key, result);
            exit(1);
        }
        else
            printf("should(%s): OK. %d does not exist in table.\n", operation, key);
    }
    
    if (!strcmp(operation, "exist")) {
        int result = search(key);
        if (result == 0) {
            printf("Value not found for key %d!\n", key);
            exit(1);
        }
        else
            printf("should(%s): OK. %d exists in table on position %d\n", operation, key, result);
    }
}

void test () {
    init();
    
    insert(76);
    insert(56);
    insert(93);
    insert(40);
    insert(35);
    
    print();
    should("exist", 35);
    
    insert(47);
    insert(23);
    insert(5);
    
    print();
    should("exist", 35);
    should("exist", 23);
    should("not.exist", 50);
}

void test_time () {
    init();
    
    float startTime = (float) clock() / CLOCKS_PER_SEC;
    
    for (int i =0; i<1000;i++) {
        insert(i);
    }
    
    float endTime = (float) clock() / CLOCKS_PER_SEC;
    printf("(%fs)\n", endTime - startTime);
}

int main () {
//    test();
    test_time();
    print();
    
    return 0;
}

