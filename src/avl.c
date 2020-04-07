//
// Created by František Gič on 07/04/2020.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    struct Node *left;
    struct Node *right;
    int data;
} Node;


Node *insert (Node *node, int data) {
    
    // Inserting a new element
    if (node == NULL) {
        
        node = (Node *) malloc(sizeof(Node));
        node->data = data;
        node->left = NULL;
        node->right = NULL;
        
        return node;
    }
    
    // Recursively insert left or right depending on value of data
    if (data < node->data)
        node->left = insert(node->left, data);
    else
        node->right = insert(node->right, data);
    
    return node;
};

void search (Node *tree, int data) {};

void free_node (Node *node) {
    if (!node) return;
    free_node(node->left);
    free_node(node->right);
    free(node);
}

int main () {
    Node *tree = NULL;
    
    tree = insert(tree, 10);
    tree = insert(tree, 20);
    tree = insert(tree, 30);
    tree = insert(tree, 40);
    tree = insert(tree, 50);
    tree = insert(tree, 25);
    
    free_node(tree);
    return 0;
}

