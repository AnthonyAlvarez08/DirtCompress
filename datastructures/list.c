#include "list.h"
#include <stdlib.h>


list_node_t* new_list_node() {
    list_node_t* res = (list_node_t*)malloc(sizeof(list_node_t));
    res->data = NULL;
    return res;
}

list_node_t* new_list_node(void* data) {
    list_node_t* res = (list_node_t*)malloc(sizeof(list_node_t));
    res->data = data;
    return res;
}

void list_append(list_node_t* head, list_node_t* new_node) {
    list_node_t* tail = head;

    while (1) {

        applier(tail->data);

        tail = tail->next;

        if (tail->next == NULL) {
            tail->next = new_node;
            new_node->prev = tail;
            return;
        }
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