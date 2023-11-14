#ifndef BIT_AHRT
#define BIT_AHRT

/* Defining the BIT_MANIP abstract data type. Contains one byte to store the
information and other byte that keeps track of the cursor position */ 
typedef struct BIT_MANIP {
    Byte byte, position;
} BIT_MANIP;

/* Allocates a BIT_MANIP pointer and sets its Byte to 0. The cursor position points to the
most significative bit (7th position from right to left). */
BIT_MANIP* BIT_MANIP_Create() {
	BIT_MANIP *byte_to_brush = (BIT_MANIP*) malloc(sizeof(BIT_MANIP));
    byte_to_brush->byte = 0;
    byte_to_brush->position = 7;
}

/* Recieves a pointer to INTEGER (byte), and an INTEGER (position). Sets the
bit in the desired postition of the byte to 1. */
void BIT_Set_Bit(Byte *byte, INTEGER position) {
    INTEGER mask = 1 << position;
    (*byte) = (*byte) | mask;
    return;
}

/* Recieves a pointer to INTEGER (byte), and an INTEGER (position). Returns true
if the bit in the desired position is 1 and false, otherwise*/
bool BIT_Is_Set(INTEGER *byte, INTEGER position) {
    INTEGER mask = 1 << position;
    return (*byte) & mask;
}

/* Recieves a pointer to BIT_MANIP abstract type. If the cursor position is 
at the end of the byte (least significative bit), returns true and sets the 
cursor position to the begining (most significative bit). If not, decreases the
cursor position by one (traversing from left to right) and returns false.
*/
bool BIT_Error_In_Advance_Position(BIT_MANIP *byte_to_brush) {
    if(byte_to_brush->position == 0) {
        byte_to_brush->position = 7;
        return true;
    } else {
        byte_to_brush->position -= 1;
        return false;
    }
}

#endif
