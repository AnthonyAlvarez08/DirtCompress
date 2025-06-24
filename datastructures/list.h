#pragma once

typedef struct list_node {
    struct list_node* next;
    struct list_node* prev;
    void* data;
} list_node_t;

list_node_t* new_list_node();
list_node_t* new_list_node(void* data);
void list_append(list_node_t* head, list_node_t* new_node);
void list_foreach(list_node_t* head, void (*applier)(void*));
void list_free(list_node_t* head);