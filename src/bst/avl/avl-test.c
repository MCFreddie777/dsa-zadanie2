//
// Created by František Gič on 11/04/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

/**
 * Rotation functions inspired by
 * https://www.youtube.com/watch?v=jDM6_TnYIqE
 * Named by the location of the imbalance in the tree
 * (e.g. LL == right rotation, the imbalance is in left child of left subtree etc..)
 */

Node *rot_ll (Node *node) {
    Node *node_l = node->left;
    Node *node_lr = node_l->right;
    
    node_l->right = node;
    node->left = node_lr;
    node->height = height(node);
    node_l->height = height(node_l);
    
    return node_l;
};

Node *rot_rr (Node *node) {
    Node *node_r = node->right;
    Node *node_rl = node_r->left;
    
    node_r->left = node;
    node->right = node_rl;
    node->height = height(node);
    node_r->height = height(node_r);
    
    return node_r;
};

Node *rot_lr (Node *node) {
    Node *node_l = node->left;
    Node *node_lr = node_l->right;
    
    node->left = node_lr->right;
    node_l->right = node_lr->left;
    
    node_lr->left = node_l;
    node_lr->right = node;
    
    node->height = height(node);
    node_l->height = height(node_l);
    node_lr->height = height(node_lr);
    
    return node_lr;
};

Node *rot_rl (Node *node) {
    Node *node_r = node->right;
    Node *node_rl = node_r->left;
    
    node_r->left = node_rl->right;
    node->right = node_rl->left;
    
    node_rl->left = node;
    node_rl->right = node_r;
    
    node->height = height(node);
    node_r->height = height(node_r);
    node_rl->height = height(node_rl);
    
    return node_rl;
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
        if (balance(node->right) == 1)
            return rot_rl(node);
        else if (balance(node->right) == -1)
            return rot_rr(node);
    }
    
    return node;
};

/**
 * Function that searches in the given BST for the given data
 *
 * @param tree The BST to search through
 * @param data The data we're trying to find
 * @return
 */
Node *search (Node *tree, int data) {
    if (tree == NULL) return NULL;
    if (tree->data == data) return tree;
    return search(data < tree->data ? tree->left : tree->right, data);
};

/**
 * Pretty print function for printing the BST
 *
 * @param node The tree we're gonna print out
 */
void inorderTraversal (Node *node) {
    if (node) {
        inorderTraversal(node->left);
        printf("%d (h:%d) (bf: %d)\n", node->data, height(node), balance(node));
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

/**
 * Simple assertions
 *
 * @param node BST to perform operations
 * @param operation not.exist | exist | have.value | have.height
 * @param value
 */
void should (Node *node, char *operation, int value) {
    
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
    
    // Special case, have.height should be given the actual node, not the node
    // thus, searching be done prior
    if (!strcmp(operation, "have.height")) {
        if (node->height != value) {
            printf("Wrong height found! (Should have height %d, returned %d)", value, node->height);
            exit(1);
        };
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
    
    free_node(tree);
}

int main () {
    test();
    test_ll();
    test_lr();
    test_rl();
    test_rr();
    return 0;
}

