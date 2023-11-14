#ifndef HUFF_DATA_AHRT
#define HUFF_DATA_AHRT

/* Defining the abstract type HUFF_DATA. */
typedef struct HUFF_DATA {
    Byte  character;
    INTEGER frequency;
} HUFF_DATA;

/* Recieves a Byte type and an INTEGER type. Allocates a HUFF_DATA pointer and sets its
character and frequency to the desired values. Returns the allocated pointer. */
HUFF_DATA* HUFF_DATA_Create(Byte character, INTEGER frequency) {
    HUFF_DATA* new_huff_data = (HUFF_DATA*) malloc(sizeof(HUFF_DATA));
    new_huff_data->character = character;
    new_huff_data->frequency = frequency;
    return new_huff_data;
}

/* Recieves a HUFF_DATA pointer and returns its character value. */
Byte  HUFF_DATA_Get_Character(HUFF_DATA *huff_data) {
	return huff_data->character;
}

/* Recieves a HUFF_DATA pointer and returns its frequency. */
INTEGER HUFF_DATA_Get_Frequency(HUFF_DATA *huff_data) {
	return huff_data->frequency;
}

/* Recieves two HUFF_DATA pointers: first and second. Allocates another HUFF_DATA which
character is set to be '*' and its frequency is the sum of first and second HUFF_DATAs. 
Returns the allocated pointer. */
GENERIC HUFF_DATA_Create_Merged(HUFF_DATA *second, HUFF_DATA *first) {
	HUFF_DATA* new_huff_data = (HUFF_DATA*) malloc(sizeof(HUFF_DATA));
	new_huff_data->character = '*';
	new_huff_data->frequency = second->frequency + first->frequency;
	return new_huff_data;
}

/* Recieves a TREE_NODE pointer (current) and its parent TREE_NODE pointer. Used 
as comparision function in the heap enqueue process, preserving the heap property. */
bool HUFF_DATA_Botton_Up_Cmp(TREE_NODE *current, TREE_NODE *parent){
	if(HUFF_DATA_Get_Frequency(current->data) < HUFF_DATA_Get_Frequency(parent->data) || 
		((HUFF_DATA_Get_Frequency(current->data) == HUFF_DATA_Get_Frequency(parent->data) ) 
			&& HUFF_DATA_Get_Character(current->data) == '*')) {
		return true;
	}
	return false;
}

/* Recieves a TREE_NODE pointer (current) and another TREE_NODE pointer (next). Used as 
comparision function in the heap dequeue process, preserving the heap property. */
bool HUFF_DATA_Top_Down_Cmp(TREE_NODE *current, TREE_NODE *next){
	if(HUFF_DATA_Get_Frequency(current->data) > HUFF_DATA_Get_Frequency(next->data) || 
		((HUFF_DATA_Get_Frequency(current->data) == HUFF_DATA_Get_Frequency(next->data)) 
			&& (HUFF_DATA_Get_Character(current->data) != '*'
			&& HUFF_DATA_Get_Character(next->data) == '*'))) {
		return true;
	}
	return false;
}

#endif
