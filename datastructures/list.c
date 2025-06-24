#include "list.h"
#include <stdlib.h>

// TODO: sort on a linked list


list_node_t* new_list_node(void* data) {
    list_node_t* res = (list_node_t*)malloc(sizeof(list_node_t));
    res->data = data;
    res->next = NULL;
    res->prev = NULL;
    return res;
}

void list_append(list_node_t* head, list_node_t* new_node) {
    list_node_t* tail = head;

    if (head == NULL) {
        if (new_node != NULL)
            *head = *new_node;
        return;
    }

    if (new_node == NULL)
        return;

    while (1) {

        if (tail->next == NULL) {
            tail->next = new_node;
            new_node->prev = tail;
            return;
        }

        tail = tail->next;

        
    }
}

void list_foreach(list_node_t* head, void (*applier)(void*)) {
    list_node_t* tail = head;

    while (tail != NULL) {

        applier(tail->data);

        tail = tail->next;
    }

}

void list_free(list_node_t* head) {
    list_node_t* tail = head;

    while (tail != NULL) {
        list_node_t* temp  = tail;
        tail = tail->next;
        free(temp->data);
        free(temp);
    }
}

