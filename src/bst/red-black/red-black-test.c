// Implementing Red-Black Tree in C

#include "red-black.c"
#include <string.h>
#include <time.h>


/**
 * Simple assertions
 *
 * @param node BST to perform operations
 * @param operation not.exist | exist | have.value | have.color
 * @param value
 */



/**
 * Simple assertions
 *
 * @param node BST to perform operations
 * @param operation not.exist | exist | have.value | have.height
 * @param value
 */
void should (struct rbNode *node, char *operation, int value) {
    
    
    if (!strcmp(operation, "not.exist")) {
        if (search(node, value) != NULL) {
            printf("%d does somehow exist in the node!\n", value);
            exit(1);
        }
        else
            printf("should(%s): OK. %d does not exist in tree.\n", operation, value);
    }
    
    
    if (!strcmp(operation, "exist")) {
        if (search(node, value) == NULL) {
            printf("Node not found for %d!\n", value);
            exit(1);
        }
        else
            printf("should(%s): OK. %d exists in tree.\n", operation, value);
    }
    
    if (!strcmp(operation, "have.value")) {
        int result = search(node, value)->data;
        if (result != value) {
            printf("Incorrect node returned! (Should have %d, returned %d)\n", value, result);
            exit(1);
        }
        else
            printf("should(%s): OK. Node with data %d has value %d.\n", operation, result, value);
    };
    
    // Special case, have.color should be given the actual node, not the node
    // thus, searching be done prior
    if (!strcmp(operation, "have.color")) {
        if (node->color != value) {
            printf(
                "Wrong color found! (Should have color %s, returned %s)\n",
                value == 0 ? "RED" : "BLACK",
                node->color == 0 ? "RED" : "BLACK"
            );
            exit(1);
        };
        printf(
            "should(%s): OK. Node %d color is %s.\n",
            operation,
            node->data,
            node->color == 0 ? "RED" : "BLACK"
        );
    };
}

void height_test () {
    root = NULL;
    
    insertion(2);
    insertion(1);
    insertion(4);
    insertion(5);
    insertion(9);
    insertion(3);
    insertion(6);
    insertion(7);
    
    should(root, "exist", 5);
    should(root, "exist", 3);
    should(root, "not.exist", 25);
    
    should(search(root, 2), "have.color", BLACK);
    should(search(root, 1), "have.color", BLACK);
    should(search(root, 5), "have.color", RED);
    should(search(root, 4), "have.color", BLACK);
    should(search(root, 7), "have.color", BLACK);
    should(search(root, 3), "have.color", RED);
    should(search(root, 6), "have.color", RED);
    should(search(root, 9), "have.color", RED);
    
    print(root);
    free_node(root);
}

void get_time_test () {
    root = NULL;
    
    insertion(2);
    insertion(1);
    insertion(4);
    insertion(5);
    insertion(9);
    insertion(3);
    insertion(6);
    insertion(7);
    
    float startTime = (float) clock() / CLOCKS_PER_SEC;
    
    printf("%d\n", search(root, 6)->data);
    
    float endTime = (float) clock() / CLOCKS_PER_SEC;
    float timeElapsed = endTime - startTime;
    printf("(%fs)\n", timeElapsed);
}

void insert_time_test () {
    root = NULL;
    
    float startTime = (float) clock() / CLOCKS_PER_SEC;
    for (int i = 0; i < 10000; i++) {
        insertion(i);
    }
    float endTime = (float) clock() / CLOCKS_PER_SEC;
    
    float timeElapsed = endTime - startTime;
    printf("Insertion time: (%fs)\n", timeElapsed);
    free_node(root);
}


int main () {
//    height_test();
//    get_time_test();
    insert_time_test();
    return 0;
}

