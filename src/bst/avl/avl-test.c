//
// Created by František Gič on 11/04/2020.
//

#include "avl.c"
#include <time.h>

/**
 * Simple assertions
 *
 * @param node BST to perform operations
 * @param operation not.exist | exist | have.value | have.height
 * @param value
 */
void should (Node *node, char *operation, int value) {
    
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
    
    // Special case, have.height should be given the actual node, not the node
    // thus, searching be done prior
    if (!strcmp(operation, "have.height")) {
        if (node->height != value) {
            printf("Wrong height found! (Should have height %d, returned %d)\n", value,
                   node->height);
            exit(1);
        };
        printf("should(%s): OK. Node %d height %d.\n", operation, node->data, value);
    };
}

void test () {
    Node *tree = NULL;
    
    tree = insert(tree, 50);
    tree = insert(tree, 10);
    tree = insert(tree, 20);
    tree = insert(tree, 20);
    
    should(tree, "not.exist", 80);
    should(tree, "exist", 50);
    should(tree, "have.value", 10);
    
    should(search(tree, 20), "have.height", 2);
    should(search(tree, 10), "have.height", 1);
    should(search(tree, 50), "have.height", 1);
    
    print(tree);
    free_node(tree);
}

void test_ll () {
    Node *tree = NULL;
    
    tree = insert(tree, 100);
    tree = insert(tree, 150);
    tree = insert(tree, 50);
    tree = insert(tree, 25);
    tree = insert(tree, 75);
    tree = insert(tree, 12);
    
    should(tree, "exist", 75);
    should(tree, "exist", 12);
    should(tree, "not.exist", 15);
    
    should(search(tree, 50), "have.height", 3);
    should(search(tree, 25), "have.height", 2);
    should(search(tree, 100), "have.height", 2);
    should(search(tree, 12), "have.height", 1);
    should(search(tree, 75), "have.height", 1);
    should(search(tree, 150), "have.height", 1);
    
    print(tree);
    free_node(tree);
}

void test_rr () {
    Node *tree = NULL;
    
    tree = insert(tree, 67);
    tree = insert(tree, 39);
    tree = insert(tree, 85);
    tree = insert(tree, 90);
    tree = insert(tree, 100);
    
    should(tree, "exist", 39);
    should(tree, "exist", 100);
    should(tree, "not.exist", 150);
    
    should(search(tree, 67), "have.height", 3);
    should(search(tree, 39), "have.height", 1);
    should(search(tree, 90), "have.height", 2);
    should(search(tree, 85), "have.height", 1);
    should(search(tree, 100), "have.height", 1);
    
    print(tree);
    free_node(tree);
}

void test_lr () {
    Node *tree = NULL;
    
    tree = insert(tree, 78);
    tree = insert(tree, 90);
    tree = insert(tree, 67);
    tree = insert(tree, 50);
    tree = insert(tree, 75);
    tree = insert(tree, 70);
    
    should(tree, "exist", 75);
    should(tree, "exist", 67);
    should(tree, "not.exist", 150);
    
    should(search(tree, 75), "have.height", 3);
    should(search(tree, 67), "have.height", 2);
    should(search(tree, 78), "have.height", 2);
    should(search(tree, 50), "have.height", 1);
    should(search(tree, 70), "have.height", 1);
    should(search(tree, 90), "have.height", 1);
    
    print(tree);
    free_node(tree);
}

void test_rl () {
    Node *tree = NULL;
    
    tree = insert(tree, 90);
    tree = insert(tree, 68);
    tree = insert(tree, 105);
    tree = insert(tree, 95);
    tree = insert(tree, 110);
    tree = insert(tree, 92);
    
    should(tree, "exist", 110);
    should(tree, "exist", 92);
    should(tree, "not.exist", 150);
    
    should(search(tree, 95), "have.height", 3);
    should(search(tree, 90), "have.height", 2);
    should(search(tree, 105), "have.height", 2);
    should(search(tree, 68), "have.height", 1);
    should(search(tree, 92), "have.height", 1);
    should(search(tree, 110), "have.height", 1);
    
    print(tree);
    free_node(tree);
}

void height_test () {
    Node *tree = NULL;
    
    tree = insert(tree, 2);
    tree = insert(tree, 1);
    tree = insert(tree, 4);
    tree = insert(tree, 5);
    tree = insert(tree, 9);
    tree = insert(tree, 3);
    tree = insert(tree, 6);
    tree = insert(tree, 7);
    
    should(tree, "exist", 5);
    should(tree, "exist", 3);
    should(tree, "not.exist", 25);
    
    should(search(tree, 4), "have.height", 4);
    should(search(tree, 2), "have.height", 2);
    should(search(tree, 6), "have.height", 3);
    should(search(tree, 1), "have.height", 1);
    should(search(tree, 3), "have.height", 1);
    should(search(tree, 5), "have.height", 1);
    should(search(tree, 9), "have.height", 2);
    should(search(tree, 7), "have.height", 1);
    
    print(tree);
    free_node(tree);
}

void get_time_test () {
    Node *tree = NULL;
    
    tree = insert(tree, 2);
    tree = insert(tree, 1);
    tree = insert(tree, 4);
    tree = insert(tree, 5);
    tree = insert(tree, 9);
    tree = insert(tree, 3);
    tree = insert(tree, 6);
    tree = insert(tree, 7);
    
    float startTime = (float) clock() / CLOCKS_PER_SEC;
    
    printf("%d\n", search(tree, 6)->data);
    
    float endTime = (float) clock() / CLOCKS_PER_SEC;
    float timeElapsed = endTime - startTime;
    printf("(%fs)\n", timeElapsed);
    
}

void insert_time_test () {
    Node *tree = NULL;
    
    float startTime = (float) clock() / CLOCKS_PER_SEC;
    for (int i = 0; i < 10000; i++) {
        tree = insert(tree, i);
    }
    float endTime = (float) clock() / CLOCKS_PER_SEC;
    
    float timeElapsed = endTime - startTime;
    printf("Insertion time: (%fs)\n", timeElapsed);
    free_node(tree);
}

int main () {
    
    // Tests 1-5
    /*
      float startTime = (float) clock() / CLOCKS_PER_SEC;
  
  //  test();
  //  test_ll();
  //  test_rr();
  //  test_lr();
      test_rl();
      
      float endTime = (float) clock() / CLOCKS_PER_SEC;
      float timeElapsed = endTime - startTime;
      printf("Success. (%fs)\n", timeElapsed);
      */

//    height_test();
//    get_time_test();
    insert_time_test();
    
    return 0;
}

