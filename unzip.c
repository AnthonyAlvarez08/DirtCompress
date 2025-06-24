#include "unzip.h"
#include "huffman.h"
#include "terminalio.h"
#include <stdio.h>
#include <stdint.h>

int unzip(char* filename) {

    FILE* archive = fopen(filename, "r");
    if (archive == NULL) {

        fprintf(stderr, "%s does not exist\n", filename);
    
        return 1;
    }





    fclose(archive);

    return 0;
}