#ifndef TREE_AHRT
#define TREE_AHRT

/* Defining the Abstract Type TREE_NODE */
typedef struct TREE_NODE {
    GENERIC data;
    struct TREE_NODE *left, *right;
} TREE_NODE;

/* Defining the Abstract Type BINARY_TREE */
typedef struct BINARY_TREE {
    struct TREE_NODE *root;
    INTEGER size;
} BINARY_TREE;

/* Allocates a BINARY_TREE pointer and initializes an empty binary tree.
Returns the allocated pointer */
GENERIC BINARY_TREE_Create() {
    BINARY_TREE *new_tree = (BINARY_TREE*) malloc(sizeof(BINARY_TREE));
    new_tree->root = NULL;
    new_tree->size = 0;
    return new_tree;
}

/* Allocates a TREE_NODE pointer and sets its data to a Generic type.
Both left and right childs point to NULL. Returns the allocated pointer*/
GENERIC TREE_NODE_Create(GENERIC data) {
    TREE_NODE *new_node = (TREE_NODE*) malloc(sizeof(TREE_NODE));
    new_node->data = data;
    new_node->left = new_node->right = NULL;
    return new_node;
}

/* Allocates a TREE_NODE pointer and sets its left and right childs. Returns the
allocated pointer */
GENERIC TREE_NODE_Create_Merged(GENERIC right, GENERIC left) {
    TREE_NODE *new_node = (TREE_NODE*) malloc(sizeof(TREE_NODE));
    new_node->left = left;
    new_node->right = right;
    return new_node;
}

#endif





