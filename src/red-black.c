/*
 * Source: Programiz.com
 * https://www.programiz.com/dsa/insertion-in-a-red-black-tree
 */

// Implementing Red-Black Tree in C

#include <stdio.h>
#include <stdlib.h>

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

int main () {
    insertion(50);
    insertion(10);
    insertion(20);
    
    inorderTraversal(root);
    free_node(root);
    
    return 0;
}

