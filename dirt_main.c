#include <stdio.h>
#include <string.h>
#include "zip.h"
#include "unzip.h"
#include "huffman.h"
#include "terminalio.h"



const char* ZIP = "zip";
const int ZIPLEN = 3;
const char* UNZIP = "unzip";
const int UNZIPLEN = 5;



int main(int argc, char** argv) {

    printf("Hello World\n");

    if (argc < 3) {
        printerr_with_usage("Not enough arguments");
        return 1;
    }

    char* option = argv[1];

    if (strncmp(option, ZIP, ZIPLEN) == 0) {
        printf("zipping...");

        if (argc != 3) {
            printerr_with_usage("Only one directory may be zipped at a time");
        }

        int res = zip_folder(argv[2]);

        if (res != 0) {
            fprintf(stderr, "failed to compress directory");
        }



    } else if (strncmp(option, UNZIP, UNZIPLEN) == 0) {

        printf("unzipping...");

        // let them unzip multiple files
        for (int i = 2; i < argc; i++) {


            printf("Attemprint to unzip %s\n", argv[i]);


            int result = unzip(argv[i]);
            
            if (result != 0) {
                fprintf(stderr, "failed to unzip file %s\n", argv[i]);
            } else {
                printf("succesfully unzipped %s\n", argv[i]);
            }
        }



        
    } else {
        printerr_with_usage("Option must be either \"zip\" or \"unzip\"");
    }



    return 0;
}



