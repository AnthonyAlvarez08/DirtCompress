#include "huffman.h"
#include "terminalio.h"
#include <stdio.h> // TODO: remove once done debugging


void sort_by_frequency(pair_t** arr, size_t len);
int compare_nodes(void* a, void* b);
tree_node_t* make_huffman_tree(char* stg, size_t len);
list_node_t* insertion_sort_wikipedia(list_node_t* pList, int (*comparator)(void* a, void* b));

char* encode(char* stg, size_t len) {

    // tree_node_t* encoding_tree = make_huffman_tree(stg, len);

    return "waho";
}


tree_node_t* make_huffman_tree(char* stg, size_t len) {


    const size_t NUM_NODES = 1 << BITWIDTH;

    // get character frequencies dictionary
    pair_t* frequencies[NUM_NODES];
    for (size_t i = 0; i < NUM_NODES; i++) {
        frequencies[i] = malloc(sizeof(pair_t));
        frequencies[i]->first = (char)i;
        frequencies[i]->second = 0;
    }
    
    for (size_t i = 0; i < len; i++) {
        int temp = (int)stg[i];

        // encode as first = character, second = freqency
        frequencies[temp]->second++;
    }

    // sort by frequency
    sort_by_frequency(frequencies, NUM_NODES);

    // build the tree
    list_node_t* nodes = NULL;
    for (size_t i = 0; i < NUM_NODES; i++) {

        // each list node pointer holds a tree node pointer which holds a pair pointer
        if (frequencies[i]->second > 0) {
            tree_node_t* node = new_tree(frequencies[i]);
            list_node_t* temp = new_list_node(node);
            if (nodes == NULL) {
                nodes = temp;
            } else {
                list_append(nodes, temp);
            }
            
        }
        
    }

    while (nodes != NULL) {

        // pop two smallest nodes
        list_node_t* top = nodes;
        list_node_t* next_top = nodes->next;

        // if the second element is null, then that means we are done and we can return the tree
        if (next_top == NULL)
            break;



        // merge them
        pair_t* merge_pair = malloc(sizeof(pair_t));
        pair_t* top_data = (pair_t*)((tree_node_t*)top->data)->data;
        pair_t* next_top_data = (pair_t*)((tree_node_t*)next_top->data)->data;
        merge_pair->second = top_data->second + next_top_data->second;

        // doesn't really matter tho, only leaf nodes matter for their character
        merge_pair->first = top_data->first;


        tree_node_t* temp = new_tree(merge_pair);
        temp->left = (tree_node_t*)top->data;
        temp->right = (tree_node_t*)next_top->data;
        list_node_t* merged = new_list_node(temp);


        // update the list
        nodes = next_top->next; // pops the nodes

        if (nodes == NULL) {
            nodes = merged;
        } else {
            list_append(nodes, merged);
            nodes = insertion_sort_wikipedia(nodes, compare_nodes);
        }

    }


    return (tree_node_t*)nodes->data;
}


void sort_by_frequency(pair_t** arr, size_t len) {
    // bubble sort because I am lazy and this is 256 elements at most
    for (size_t i = 0; i < len; i++) {
        for (size_t j = i + 1; j < len; j++) {
            if (arr[i]->second > arr[j]->second) {
                pair_t* temp = arr[j];
                arr[j] = arr[i];
                arr[i] = temp;
            }
        }
    }
}





// wikipedias insertion sort for a linked list
// https://en.wikipedia.org/wiki/Insertion_sort#List_insertion_sort_code_in_C
list_node_t* insertion_sort_wikipedia(list_node_t* pList, int (*comparator)(void* a, void* b)) 
{
    // zero or one element in list
    if (pList == NULL || pList->next == NULL)
        return pList;
    // head is the first element of resulting sorted list
    list_node_t * head = NULL;
    while (pList != NULL) {
        list_node_t* current = pList;
        pList = pList->next;
        if (head == NULL || comparator(current->data, head->data) < 0) {
            // current->iValue < head->iValue) {
            // insert into the head of the sorted list
            // or as the first element into an empty sorted list
            current->next = head;
            head = current;
        } else {
            // insert current element into proper position in non-empty sorted list
            list_node_t * p = head;
            while (p != NULL) {
                if (p->next == NULL || // last element of the sorted list
                    comparator(current->data, p->next->data) < 0)
                    // current->iValue < p->next->iValue) // middle of the list
                {
                    // insert into middle of the sorted list or as the last element
                    current->next = p->next;
                    p->next = current;
                    break; // done
                }
                p = p->next;
            }
        }
    }
    return head;
}

int compare_nodes(void* a, void* b) {
    // a and b are data of list nodes which hold tree nodes which hold pairs
    // so a and b are already in tree node format


    tree_node_t* a_tree = (tree_node_t*)a;
    pair_t* a_pair = (pair_t*)(a_tree->data);

    tree_node_t* b_tree = (tree_node_t*)b;
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


        // apparently it assumes uniqueness
        // so use the character as a tiebreaker
        if (a_pair->first > b_pair->first) {
            return 1;
        } else {
            return -1;
        }

        // return 0;
    }

    return -1;

}