#pragma once

typedef struct tree_node {
    struct tree_node* left;
    struct tree_node* right;
    void* data;
} tree_node_t;

tree_node_t* new_tree();
tree_node_t* new_tree(void* data);
void tree_insert_data(tree_node_t* root, void* data, int (*comparator)(void* a, void* b));
void tree_insert_node(tree_node_t* root, tree_node_t* node, int (*comparator)(void* a, void* b));
int tree_search(tree_node_t* root, void* data, int (*equal)(void* a, void* b));
void tree_free(tree_node_t* root);