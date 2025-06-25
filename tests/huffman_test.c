#include <stdio.h>
#include "../huffman.h"

void print_tree(tree_node_t* root, int depth);

int main(void) {


    FILE* testfile = fopen("tests/loremipsum.txt", "r");

    // read 1024 bytes for now
    const int READ_SIZE = 1 << 10;   
    char buf[READ_SIZE];
    for (int i = 0; i < READ_SIZE; i++) buf[i] = 0;

    size_t read = fread(buf, sizeof(char), READ_SIZE, testfile);

    printf("read:%ld\n%s\n", read, buf);
    tree_node_t* tree = make_huffman_tree(buf, read);

    print_tree(tree, 0);


    return 0;    
}

void print_tree(tree_node_t* root, int depth) {

    for (int i = 0; i < depth; i++) {
        printf("\t");
    }

    if (root == NULL) {
        printf("<empty>\n");
        return;
    }

    pair_t* data = (pair_t*)root->data;


    printf("<char: %c, frequency: %d>\n", data->first, data->second);


    print_tree(root->left, depth + 1);
    print_tree(root->right, depth + 1);
}