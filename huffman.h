#pragma once
#include "datastructures/list.h"
#include "datastructures/binary_tree.h"
#include <stdlib.h>

char* encode(char*, size_t);
tree_node_t* make_huffman_tree(char* stg, size_t len);
// char* decode();



// helper structs
// in here so I can test easier
#define BITWIDTH 8
typedef struct pair {
    char first;
    int second;
} pair_t;