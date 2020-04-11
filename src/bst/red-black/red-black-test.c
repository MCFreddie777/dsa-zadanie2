/*
 * This algorithm was acquired from Programiz.com
 * https://www.programiz.com/dsa/insertion-in-a-red-black-tree
 */

// Implementing Red-Black Tree in C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum nodeColor {
    RED,
    BLACK
};

struct rbNode {
    int data, color;
    struct rbNode *link[2];
};

struct rbNode *root = NULL;

struct rbNode *createNode (int data) {
    struct rbNode *newnode;
    newnode = (struct rbNode *) malloc(sizeof(struct rbNode));
    newnode->data = data;
    newnode->color = RED;
    newnode->link[0] = newnode->link[1] = NULL;
    return newnode;
}

void insertion (int data) {
    struct rbNode *stack[98], *ptr, *newnode, *xPtr, *yPtr;
    int dir[98], ht = 0, index;
    ptr = root;
    if (!root) {
        root = createNode(data);
        return;
    }
    stack[ht] = root;
    dir[ht++] = 0;
    while (ptr != NULL) {
        if (ptr->data == data) {
            printf("Duplicates Not Allowed!!\n");
            return;
        }
        index = (data - ptr->data) > 0 ? 1 : 0;
        stack[ht] = ptr;
        ptr = ptr->link[index];
        dir[ht++] = index;
    }
    stack[ht - 1]->link[index] = newnode = createNode(data);
    while ((ht >= 3) && (stack[ht - 1]->color == RED)) {
        if (dir[ht - 2] == 0) {
            yPtr = stack[ht - 2]->link[1];
            if (yPtr != NULL && yPtr->color == RED) {
                stack[ht - 2]->color = RED;
                stack[ht - 1]->color = yPtr->color = BLACK;
                ht = ht - 2;
            }
            else {
                if (dir[ht - 1] == 0) {
                    yPtr = stack[ht - 1];
                }
                else {
                    xPtr = stack[ht - 1];
                    yPtr = xPtr->link[1];
                    xPtr->link[1] = yPtr->link[0];
                    yPtr->link[0] = xPtr;
                    stack[ht - 2]->link[0] = yPtr;
                }
                xPtr = stack[ht - 2];
                xPtr->color = RED;
                yPtr->color = BLACK;
                xPtr->link[0] = yPtr->link[1];
                yPtr->link[1] = xPtr;
                if (xPtr == root) {
                    root = yPtr;
                }
                else {
                    stack[ht - 3]->link[dir[ht - 3]] = yPtr;
                }
                break;
            }
        }
        else {
            yPtr = stack[ht - 2]->link[0];
            if ((yPtr != NULL) && (yPtr->color == RED)) {
                stack[ht - 2]->color = RED;
                stack[ht - 1]->color = yPtr->color = BLACK;
                ht = ht - 2;
            }
            else {
                if (dir[ht - 1] == 1) {
                    yPtr = stack[ht - 1];
                }
                else {
                    xPtr = stack[ht - 1];
                    yPtr = xPtr->link[0];
                    xPtr->link[0] = yPtr->link[1];
                    yPtr->link[1] = xPtr;
                    stack[ht - 2]->link[1] = yPtr;
                }
                xPtr = stack[ht - 2];
                yPtr->color = BLACK;
                xPtr->color = RED;
                xPtr->link[1] = yPtr->link[0];
                yPtr->link[0] = xPtr;
                if (xPtr == root) {
                    root = yPtr;
                }
                else {
                    stack[ht - 3]->link[dir[ht - 3]] = yPtr;
                }
                break;
            }
        }
    }
    root->color = BLACK;
}

void inorderTraversal (struct rbNode *node) {
    if (node) {
        inorderTraversal(node->link[0]);
        printf("%d ", node->data);
        inorderTraversal(node->link[1]);
    }
}

void free_node (struct rbNode *node) {
    if (node) {
        free_node(node->link[0]);
        free_node(node->link[1]);
        free(node);
    }
}

/**
 * Function that searches in the given BST for the given data
 *
 * @param tree The BST to search through
 * @param data The data we're trying to find
 * @return
 */
struct rbNode *search (struct rbNode *tree, int data) {
    if (tree == NULL) return NULL;
    if (tree->data == data) return tree;
    return search(data < tree->data ? tree->link[0] : tree->link[1], data);
};


/**
 * Simple assertions
 *
 * @param node BST to perform operations
 * @param operation not.exist | exist | have.value | have.color
 * @param value
 */
void should (struct rbNode *node, char *operation, int value) {
    
    if (!strcmp(operation, "not.exist"))
        if (search(node, value) != NULL) {
            printf("%d does somehow exist in the node!", value);
            exit(1);
        }
    
    
    if (!strcmp(operation, "exist"))
        if (search(node, value) == NULL) {
            printf("Node not found for %d!", value);
            exit(1);
        };
    
    if (!strcmp(operation, "have.value")) {
        int result = search(node, value)->data;
        if (result != value) {
            printf("Incorrect node returned! (Should have %d, returned %d)", value, result);
            exit(1);
        };
    };
    
    // Special case, have.color should be given the actual node, not the node
    // thus, searching be done prior
    if (!strcmp(operation, "have.color")) {
        if (node->color != value) {
            printf(
                "Wrong color found! (Should have color %s, returned %s)",
                value == 0 ? "RED" : "BLACK",
                node->color == 0 ? "RED" : "BLACK"
            );
            exit(1);
        };
    };
}

int main () {
    root = NULL;
    
    insertion(13);
    insertion(8);
    insertion(17);
    insertion(1);
    insertion(11);
    insertion(15);
    insertion(25);
    insertion(27);
    insertion(6);
    insertion(22);
    
    should(root, "exist", 17);
    should(root, "exist", 25);
    should(root, "not.exist", 3);
    
    should(search(root, 13), "have.color", BLACK);
    should(search(root, 8), "have.color", RED);
    should(search(root, 17), "have.color", RED);
    should(search(root, 1), "have.color", BLACK);
    should(search(root, 11), "have.color", BLACK);
    should(search(root, 15), "have.color", BLACK);
    should(search(root, 25), "have.color", BLACK);
    should(search(root, 6), "have.color", RED);
    should(search(root, 22), "have.color", RED);
    should(search(root, 27), "have.color", RED);
    
    return 0;
}

