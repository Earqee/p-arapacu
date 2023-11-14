#ifndef UTILITY_AHRT
#define UTILITY_AHRT

/* Reads a string from the standard input (keyboard) containing the compressed file path.
Creates a pointer to the loaded file and then returns it. */
FILE* U_Read_From_Stream(char *fileName) {
    scanf(" %[^\n]s", string);
    FILE *loaded_file = fopen(fileName, "rb");
    free(fileName);
    return loaded_file;
}

/* Recieves pointers to TREE_NODE, LIST and HASH. Applies a DFS traversal in the tree
(BACKTRACKING) to generate the compressed code of each character (tree leaf). At each
step of the recursion the code is generated inserting '1' or '0' to a linked list. At the end
of the recursion, is created a new list in the hash table character position, and then copying the 
generated code list to the hash table. */ 
void U_HASHING_Pre_Order_Walk(TREE_NODE *tree_node, LIST *list, HASH *cmpressed_repr) {
    if(tree_node == NULL)
        return;
    if(tree_node->left == NULL && tree_node->right == NULL) {
        LIST_NODE *current = list->head;
        while(current != NULL) {
            if(cmpressed_repr->table[HUFF_DATA_Get_Character(tree_node->data)] == NULL)
                cmpressed_repr->table[HUFF_DATA_Get_Character(tree_node->data)] = LIST_Create();
            LIST_Insert_Tail(cmpressed_repr->table[HUFF_DATA_Get_Character(tree_node->data)], current->data);
            current = current->next;
        }
    }
    LIST_Insert_Tail(list, '0');
    U_HASHING_Pre_Order_Walk(tree_node->left, list, cmpressed_repr);
    LIST_Remove_Tail(list);
    
    LIST_Insert_Tail(list, '1');
    U_HASHING_Pre_Order_Walk(tree_node->right, list, cmpressed_repr);
    LIST_Remove_Tail(list);
    return;
}

/* Recieves pointers to TREE_NODE and FILE. Traverses the tree in pre order walk and writes
its nodes data in the compressed file header. If the leaf data is '*' or '\' it's printed a
'\' as escape character. */
void U_PRINTING_Pre_Order_Walk(TREE_NODE *tree_node, FILE *compressed_file) {
    if(tree_node == NULL)
        return;
    if(tree_node->left == NULL && tree_node->right == NULL) {
        if(HUFF_DATA_Get_Character(tree_node->data) == '*' ||
            HUFF_DATA_Get_Character(tree_node->data) == '\\') {
            fputc('\\', compressed_file);
        }
    }
    fputc(HUFF_DATA_Get_Character(tree_node->data), compressed_file);
    U_PRINTING_Pre_Order_Walk(tree_node->left, compressed_file);
    U_PRINTING_Pre_Order_Walk(tree_node->right, compressed_file);
    return;
}

#endif
