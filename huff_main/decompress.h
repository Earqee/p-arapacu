#ifndef DECOMPRESS_AHRT
#define DECOMPRESS_AHRT

/* Recieves a FILE pointer to the compressed file and returns the trash size. */
INTEGER Get_Trash_Size(FILE *loaded_file) {
    rewind(loaded_file);
    INTEGER trash_size = fgetc(loaded_file) >> 5;
    return trash_size;
}

/* Recieves a FILE pointer to the compressed file and returns the tree size. */
INTEGER Get_Huff_Tree_Size(FILE *loaded_file) {
    rewind(loaded_file);
    INTEGER first_byte = fgetc(loaded_file) << 8;
    INTEGER second_byte = fgetc(loaded_file);
    first_byte = first_byte | second_byte;
    INTEGER tree_size = 0;

    for(INTEGER i = 12; i >= 0; i--) {
        if(BIT_Is_Set(&first_byte, i)) {
            BIT_Set_Bit(&tree_size, i);
        }
    }
    return tree_size;
}

/* Recieves a FILE pointer to the loaded file and a Byte type. Allocates a TREE_NODE 
pointer to the huffman tree root to be built and builds it, reading from the file header. Returns
the TREE_NODE "root" allocated pointer. */
TREE_NODE* Build_Huff_Tree(FILE *loaded_file, Byte key) {
    TREE_NODE *new_tree_node = TREE_NODE_Create(key);

    if(key == '\\') {
        new_tree_node->data = fgetc(loaded_file);
    }
    if(key == '*') {
        new_tree_node->left = Build_Huff_Tree(loaded_file, fgetc(loaded_file));
        new_tree_node->right = Build_Huff_Tree(loaded_file, fgetc(loaded_file));
    }
    return new_tree_node;
}

/* Recieves a FILE pointer to the loaded file and allocates a BINARY_TREE pointer to the
huffman tree to be created. Assigns the created tree root to be the extracted tree root from
the file and then, returns the allocated BINARY_TREE pointer.  */
BINARY_TREE* Extract_Huff_Tree_From_File(FILE *loaded_file) {
    BINARY_TREE *huff_tree = BINARY_TREE_Create();
    huff_tree->root = Build_Huff_Tree(loaded_file, fgetc(loaded_file));
    return huff_tree;
}

/* Recieves a FILE pointer to the loaded file, a BINARY_TREE pointer to the huffman tree
created and an INTEGER containing the trash size. Writes in the decompressed, file each character,
traversing through the huffman tree until finding a leaf. Uses the trash size to keep track of the 
print bit-by-bit process. Then finalizes the decompressing process. */
void Decompress(FILE *loaded_file, BINARY_TREE *huff_tree, INTEGER trash_size) {
    FILE *decompressed_file = fopen("decompressed", "wb");
    TREE_NODE *current = huff_tree->root;
    Byte current_byte, stop_point;
    INTEGER stream_position, final_position;

    stream_position = ftell(loaded_file);
    fseek(loaded_file, 0, SEEK_END);
    final_position = ftell(loaded_file);
    fseek(loaded_file, stream_position, SEEK_SET);

    stop_point = 0;
    while(current_byte = fgetc(loaded_file), feof(loaded_file) != 1) {
        for(INTEGER i = 7; i >= stop_point; i--) {
            if(current->left == NULL) {
                fgetpos(loaded_file, &stream_position);

                if(stream_position == final_position) {                    
                    stop_point = trash_size;
                }
                fputc(current->data, decompressed_file);
                current = huff_tree->root;
            }

            if(BIT_Is_Set(&current_byte, i)) {
                current = current->right;
            } else {
                current = current->left;
            }
        }
    }
    printf("Success!");
    return;
}

/* Main function used to decompress the file. */
void Decompress_File(char *fileName) {
 
    FILE *loaded_file = U_Read_From_Stream(fileName);

    INTEGER trash_size = Get_Trash_Size(loaded_file);
    INTEGER tree_size = Get_Huff_Tree_Size(loaded_file);
    BINARY_TREE *huff_tree = Extract_Huff_Tree_From_File(loaded_file);
    Decompress(loaded_file, huff_tree, trash_size);

    return;    
}

#endif