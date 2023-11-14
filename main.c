#include "header.h"

int main(int argc, char *argv[]) {

	if (argc != 3) {
        	fprintf(stderr, "Uso: %s [-c/-d] arquivo\n", argv[0]);
        	return EXIT_FAILURE;
    	}

    	char *mode = argv[1];
    	char *fileName = argv[2];

	if (strcmp(mode, "-c") == 0) {
        	Compress_File(fileName);
    	} else if (strcmp(mode, "-d") == 0) {
        	Decompress_File(fileName);
    	} else {
        	fprintf(stderr, "Modo inválido. Use -c para compressão ou -d para descompressão.\n");
        	return -1;
    	}
	return 0;
}
