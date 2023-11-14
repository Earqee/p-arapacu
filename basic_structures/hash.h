#ifndef HASH_AHRT
#define HASH_AHRT

/* Defining the abstract data type HASH. */
typedef struct HASH {
    GENERIC *table;
} HASH;

/* Allocates a pointer to HASH. Sets the hash table array to MAX_HASH_SIZE, allocating
a GENERIC pointer. Returns the allocated HASH pointer. */
GENERIC HASH_Create() {
    HASH *new_hash = (HASH*) malloc(sizeof(HASH));
    new_hash->table = calloc(MAX_HASH_SIZE, sizeof(GENERIC));
    return new_hash;
}

/* Recieves a HASH pointer, a GENERIC data and an INTEGER index. Inserts the
desired data in the given index position of the hash table. */
GENERIC HASH_Insert(HASH *hash, GENERIC data, INTEGER index) {
    hash->table[index] = data;
}

#endif
