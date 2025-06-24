#include "huffman.h"


#define BITWIDTH 8


typedef struct pair {
    int first;
    int second;
} pair_t;

void sort_by_frequency(pair_t* arr, int len);

tree_node_t* encode(char* stg, size_t len) {

    // get character frequencies dictionary
    pair_t frequencies[1 << BITWIDTH];
    
    for (size_t i = 0; i < len; i++) {
        int temp = (int)stg[i];
        frequencies[temp].first = i;
        frequencies[temp].second++;
    }

    // sort by frequency
    sort_by_frequency(frequencies, 1 << BITWIDTH);

    // build the tree

    return NULL;
}


void sort_by_frequency(pair_t* arr, int len) {
    // bubble sort because I am lazy and this is 256 elements at most
    for (int i = 0; i < len; i++) {
        for (int j = i + 1; j < len; i++) {
            if (arr[i].second > arr[j].second) {
                pair_t temp = arr[j];
                arr[j] = arr[i];
                arr[i] = temp;
            }
        }
    }
}