//
// Created by František Gič on 07/04/2020.
//

#include <stdio.h>
#include <stdlib.h>

#define left_height(node) (node->left ? node->left->height : 0)
#define right_height(node) (node->right ? node->right->height : 0)
#define height(node) ((right_height(node) > left_height(node) ? right_height(node) : left_height(node))+1)
#define balance(node) (left_height(node) - right_height(node))

typedef struct Node {
    struct Node *left;
    struct Node *right;
    int data;
    int height;
} Node;

Node *rot_ll (Node *node) {
    Node *node_l = node->left;
    Node *node_lr = node_l->right;
    
    node_l->right = node;
    node->left = node_lr;
    node->height = height(node);
    node_l->height = height(node_l);
    
    return node_l;
};

Node *rot_lr (Node *node) {
    Node *node_l = node->left;
    Node *node_lr = node_l->right;
    
    node_l->right = node_lr->left;
    node->left = node_lr->right;
    node_lr->left = node_l;
    node_lr->right = node;
    
    node_l->height = height(node_l);
    node->height = height(node);
    node_lr->height = height(node_lr);
    
    return node_lr;
};

Node *rot_rl (Node *node) {
    return NULL;
};

Node *rot_rr (Node *node) {
    return NULL;
};

/**
 * Recursive function to insert data into the BST
 *
 * @param node the root node of a subtree
 * @param data The value that should be inserted into the right place
 * @return whole subtree with @param data inserted
 */
Node *insert (Node *node, int data) {
    
    // Inserting a new element
    if (node == NULL) {
        
        node = (Node *) malloc(sizeof(Node));
        node->data = data;
        node->height = 1;
        node->left = NULL;
        node->right = NULL;
        
        return node;
    }
    
    // Recursively insert left or right depending on value of data
    if (data < node->data)
        node->left = insert(node->left, data);
    else
        node->right = insert(node->right, data);
    
    // Update the height - maximum height of its children increased by 1
    node->height = height(node);
    
    // Check the imbalance in the tree and perform rotations
    if (balance(node) == 2) {
        if (balance(node->left) == 1)
            return rot_ll(node);
        else if (balance(node->left) == -1)
            return rot_lr(node);
    }
    if (balance(node) == -2) {
        if (balance(node->left) == 1)
            return rot_rl(node);
        else if (balance(node->left) == -1)
            return rot_rr(node);
    }
    
    return node;
};

void search (Node *tree, int data) {};

void inorderTraversal (Node *node) {
    if (node) {
        inorderTraversal(node->left);
        printf("%d ", node->data);
        inorderTraversal(node->right);
    }
}

void free_node (Node *node) {
    if (node) {
        free_node(node->left);
        free_node(node->right);
        free(node);
    }
}

int main () {
    Node *tree = NULL;
    
    tree = insert(tree, 50);
    tree = insert(tree, 10);
    tree = insert(tree, 20);
    
    inorderTraversal(tree);
    free_node(tree);
    return 0;
}

