#include "terminalio.h"
#include <stdio.h>

void printerr(char* error) {
    fprintf(stderr, "Error: %s\n", error);

}


void printerr_with_usage(char* error) {
    fprintf(stderr, "Error: %s\n", error);
    fprintf(stderr, "Usage 1: dirt zip {containing_folder}\n");
    fprintf(stderr, "Usage 2: dirt unzip [{archive_file}.dirt]\n");
}