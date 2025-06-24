#include "huffman.h"
#include "terminalio.h"

#define BITWIDTH 8


typedef struct pair {
    char first;
    int second;
} pair_t;

void sort_by_frequency(pair_t* arr, size_t len);
list_node_t* insertion_sort(list_node_t* head, int (*comparator)(void* a, void* b));
int compare_nodes(void* a, void* b);


tree_node_t* encode(char* stg, size_t len) {


    const size_t NUM_NODES = 1 << BITWIDTH;

    // get character frequencies dictionary
    pair_t frequencies[NUM_NODES];
    
    for (size_t i = 0; i < len; i++) {
        int temp = (int)stg[i];

        // encode as first = character, second = freqency
        frequencies[temp].first = stg[i];
        frequencies[temp].second++;
    }

    // sort by frequency
    sort_by_frequency(frequencies, NUM_NODES);

    // build the tree
    tree_node_t* temp_node = new_tree(&frequencies[0]);
    list_node_t* nodes = new_list_node(temp_node);
    for (size_t i = 1; i < NUM_NODES; i++) {

        // each list node pointer holds a tree node pointer which holds a pair pointer
        tree_node_t* node = new_tree(&frequencies[i]);
        list_node_t* temp = new_list_node(node);
        list_append(nodes, temp);
    }

    while (1) {
        // pop two smallest nodes
        list_node_t* top = nodes;
        list_node_t* next_top = nodes->next;

        // if the second element is null, then that means we are done and we can return the tree
        if (next_top == NULL)
            break;

        // I did check that nodes->next is not null so tis should work
        nodes = nodes->next->next;

        if (nodes == NULL) {
            printerr("HUFFMAN algorithm failed somehow");
            return NULL;
        }

        // merge them
        pair_t mergepair;
        pair_t* topdata = (pair_t*)((tree_node_t*)top->data)->data;
        pair_t* next_top_data = (pair_t*)((tree_node_t*)next_top->data)->data;
        mergepair.second = topdata->second + next_top_data->second;

        // doesn't really matter tho, only leaf nodes matter for their character
        mergepair.first = topdata->first;

        tree_node_t* temp = new_tree(&mergepair);
        list_node_t* merged = new_list_node(temp);

        // put them back into the list
        list_append(nodes, merged);

        // I think I have to free these to avoid a memory leak
        free(top);
        free(next_top);

        // TODO: sort them
        insertion_sort(nodes, compare_nodes);
    }

    return (tree_node_t*)nodes->data;
}


void sort_by_frequency(pair_t* arr, size_t len) {
    // bubble sort because I am lazy and this is 256 elements at most
    for (size_t i = 0; i < len; i++) {
        for (size_t j = i + 1; j < len; i++) {
            if (arr[i].second > arr[j].second) {
                pair_t temp = arr[j];
                arr[j] = arr[i];
                arr[i] = temp;
            }
        }
    }
}



// I just copied the linked list insertion sort from geeks for geeks lol
// Function to insert a new_node in the result list.
list_node_t* sorted_insert(list_node_t* createNode, list_node_t* sorted, int (*comparator)(void* a, void* b)) {
    
    // Special case for the head end
    if (sorted == NULL || 
        comparator(sorted->data, createNode->data) >= 0) {
        createNode->next = sorted;
        sorted = createNode;
    }
    else {
        list_node_t* curr = sorted;
        
        // Locate the node before the point of insertion
        while (curr->next != NULL && 
                comparator(curr->next->data, createNode->data) < 0) {
            curr = curr->next;
        }
        createNode->next = curr->next;
        curr->next = createNode;
    }
    
    return sorted;
}


// comparator returs 
// 1 if a > b
// 0 if a == b
// -1 if a < b
list_node_t* insertion_sort(list_node_t* head, int (*comparator)(void* a, void* b)) {
    
    // Initialize sorted linked list
    list_node_t* sorted = NULL;
    list_node_t* curr = head;
    
    // Traverse the given linked list and insert
    // every node to sorted
    while (curr != NULL) {
        
        // Store next for next iteration
        list_node_t* next = curr->next;
        
        // Insert current in sorted linked list
        sorted = sorted_insert(curr, sorted, comparator);
        
        // Update current
        curr = next;
    }
    
    return sorted;
}

int compare_nodes(void* a, void* b) {
    // a and b are list nodes which hold tree nodes which hold pairs

    list_node_t* a_list = (list_node_t*)a;
    tree_node_t* a_tree = (tree_node_t*)(a_list->data);
    pair_t* a_pair = (pair_t*)(a_tree->data);

    list_node_t* b_list = (list_node_t*)b;
    tree_node_t* b_tree = (tree_node_t*)(b_list->data);
    pair_t* b_pair = (pair_t*)(b_tree->data);

    // 1 if a > b
    // 0 if a == b
    // -1 if a < b

    // second is the frequency, first is the character
    if (a_pair->second > b_pair->second) {
        return 1;
    } else if (a_pair->second < b_pair->second) {
        return -1;
    } else {
        return 0;
    }

}