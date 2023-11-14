#ifndef COMPRESS_AHRT
#define COMPRESS_AHRT

/* Recieves a pointer to FILE and counts the frequencies of each character 
int the loaded file, storing the data in a hash table. Returns the HASH pointer. */
GENERIC Read_Stream_Counting(FILE *loaded_file) {
    HASH *counter = HASH_Create();
    Byte current_byte;

    while(current_byte = fgetc(loaded_file), feof(loaded_file) != 1) {
    	if(counter->table[current_byte] == NULL)
    		counter->table[current_byte] = 0;
    	counter->table[current_byte]++;
    }

    counter->table['\n']--;
    return counter;
}

/* Recieves a HASH pointer. Allocates a HEAP that will be used as a priority queue.
Enqueues all the huff nodes created from the hash table, then returns the heap. */
GENERIC Create_Priority_Queue(HASH *counter) {
	HEAP *heap = HEAP_Create();
    for(INTEGER i = 0; i < MAX_HASH_SIZE; i++) {
        if(counter->table[i] != NULL) {
        	HUFF_DATA *huff_data = HUFF_DATA_Create(i, counter->table[i]);
        	TREE_NODE *huff_node = TREE_NODE_Create(huff_data);
            HEAP_Enqueue(heap, huff_node, HUFF_DATA_Botton_Up_Cmp);          
        }
    }
    return heap;
}

/* Recieves a HEAP pointer. Allocates a BINARY_TREE pointer and creates the huffman tree
from the heap. Updates, at every step, the tree size and sets the single huff node of the 
one-sized heap to be the huffman tree root. Returns the BINARY_TREE pointer. */
GENERIC Create_Huffman_Tree(HEAP *heap) {
    BINARY_TREE *tree = BINARY_TREE_Create();
    tree->size = heap->size;

    while(heap->size > 1) {
    	TREE_NODE *merged_node = TREE_NODE_Create_Merged(
    		HEAP_Dequeue(heap, HUFF_DATA_Top_Down_Cmp),
    		HEAP_Dequeue(heap, HUFF_DATA_Top_Down_Cmp));
    	merged_node->data = HUFF_DATA_Create_Merged(merged_node->left->data, 
    		merged_node->right->data);

    	tree->size++;

    	HEAP_Enqueue(heap, merged_node, HUFF_DATA_Botton_Up_Cmp);
    }

    tree->root = heap->array[1];
    return tree;
}

/* Recieves a BINARY_TREE pointer and generates all compressed codes of each
character in the tree (leaf), storing the data in a hash table. Returns the HASH pointer. */
GENERIC Extract_Compressed_Representation(BINARY_TREE *tree) {
	LIST *list = LIST_Create();
	HASH *cmpressed_repr = HASH_Create();
	U_HASHING_Pre_Order_Walk(tree->root, list, cmpressed_repr);
	return cmpressed_repr;
}

/* Recieves the FILE pointer to the file to be compressed, the HASH pointer to the Hash table
containing the compressed code of each character and the BINARY_TREE pointer to the Huffman Tree.
Writes in the compressed file two empty bytes (to be used in the header), the pre order Huffman
Tree and the compressed file bits. Then, returns the trash size. */
GENERIC Compress(FILE *loaded_file, HASH *cmpressed_repr, BINARY_TREE *huff_tree) {
	FILE *compressed_file = fopen("compressed", "wb");
	BIT_MANIP *byte_to_brush = BIT_MANIP_Create(); 
	Byte current_byte;

	for(INTEGER i = 0; i < 2; i++)
		fputc(0, compressed_file);
	U_PRINTING_Pre_Order_Walk(huff_tree->root, compressed_file);

	rewind(loaded_file);

	while(current_byte = fgetc(loaded_file), feof(loaded_file) != 1) {
        
        LIST_NODE *current = LIST_Get_Pointer_To_Head(cmpressed_repr->table[current_byte]);
        
        while(current != NULL) {
			if(current->data == '1') {
				BIT_Set_Bit(&byte_to_brush->byte, byte_to_brush->position);
			}
			current = current->next;
			if(BIT_Error_In_Advance_Position(byte_to_brush)) {
				fputc(byte_to_brush->byte, compressed_file);
				byte_to_brush->byte = 0;
			}
		}
	}

	INTEGER trash_size = 0;
	if(byte_to_brush->position != 7) {
		fputc(byte_to_brush->byte, compressed_file);
		trash_size = byte_to_brush->position;
	}

	fclose(compressed_file);
	return trash_size;
}

/* Recieves the trash size and the tree size and writes the two frist bytes of the header. Then,
finalizes the compressing process. */
GENERIC Header_Writing(INTEGER trash_size, INTEGER tree_size) {
	FILE *compressed_file = fopen("compressed", "r+b");

	INTEGER aux = (trash_size << 13) | tree_size;

	Byte first_byte = (aux >> 8);
	Byte second_byte = aux;

	fputc(first_byte, compressed_file);
	fputc(second_byte, compressed_file);

	fclose(compressed_file);
    printf("Success!");
    
    return;
}

/* Main function used to compress the file. */
void Compress_File(char *fileName) {

    FILE *loaded_file = U_Read_From_Stream(fileName);

    HASH *counter = Read_Stream_Counting(loaded_file); //OK
    HEAP *heap = Create_Priority_Queue(counter); //OK
    BINARY_TREE *huff_tree = Create_Huffman_Tree(heap); //OK
    

    HASH *cmpressed_repr = Extract_Compressed_Representation(huff_tree);
    
    INTEGER trash_size = Compress(loaded_file, cmpressed_repr, huff_tree);
    Header_Writing(trash_size, huff_tree->size);

    return;
}

#endif
