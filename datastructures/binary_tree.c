#include "binary_tree.h"
#include <stdlib.h>

tree_node_t* new_tree() {
    tree_node_t* res = (tree_node_t*)malloc(sizeof(tree_node_t));
    res->data = NULL;

    return res;
}

tree_node_t* new_tree(void* data) {
    tree_node_t* res = (tree_node_t*)malloc(sizeof(tree_node_t));
    res->data = data;

    return res;
}



void tree_insert_data(tree_node_t* root, void* data, int (*comparator)(void* a, void* b)) {
    int comparison = comparator(root->data, data);

    if (comparison == 1) {
        if (root->right == NULL) {
            root->right = new_tree(data);
            return;
        } else {
            tree_insert_data(root->right, data, comparator);
        }
    } else {
       if (root->left == NULL) {
            root->left = new_tree(data);
            return;
        } else {
            tree_insert_data(root->left, data, comparator);
        } 
    }
}

void tree_insert_node(tree_node_t* root, tree_node_t* node, int (*comparator)(void* a, void* b)) {
    int comparison = comparator(root->data, node->data);

    if (comparison == 1) {
        if (root->right == NULL) {
            root->right = node;
            return;
        } else {
            tree_insert_node(root->right, node, comparator);
        }
    } else {
       if (root->left == NULL) {
            root->left = node;
            return;
        } else {
            tree_insert_node(root->left, node, comparator);
        } 
    }
}


int tree_search(tree_node_t* root, void* data, int (*comparator)(void* a, void* b)) {
    if (root == NULL) {
        return 0;
    }
    
    int comparison = comparator(root->data, data);


    if (comparison == 0) {
        return 1;
    }

    if (comparison == 1) {
        return tree_search(root->right, data, comparator);
    }

    return tree_search(root->left, data, comparator);
}

void tree_free(tree_node_t* root) {
    if (root == NULL) {
        return;
    }

    if (root->left)
        tree_free(root->left);
    
    if (root->right)
        tree_free(root->right);


    free(root->data);
    free(root);

}