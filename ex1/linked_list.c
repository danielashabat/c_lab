#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"


//internal function declarations:
Node* create_Node(int val);

void insert_first_node(Node* node, Linked_List* list);

int index_of_val_in_list(int val, Linked_List* list);

// function definitions:

int print_index( int val, Linked_List* list ){
	int index = index_of_val_in_list(val,list);
	if (index >= 0){
		printf("%d\n",index);
		return 0;
	}
	else {
		terminate_list(list);
		return ERROR_INVALID_INDEX;
	}
}


Linked_List* create_emplty_Linked_List(){
	Linked_List* list = (Linked_List*)malloc(sizeof(Linked_List));
	list->first = NULL;
	list->last = NULL;
	list->num_of_nodes = 0;
	return list;
}

Node* create_Node(int val){
	Node* node= (Node*)malloc(sizeof(Node));
	node->val = val;
	node->next = NULL;
	node->prev = NULL;
	return node;
}

void insert_first_node(Node* node, Linked_List* list){
	list->first = node;
	list->last = node;
	list->num_of_nodes = 1;
}

void add_to_start_of_list(int val, Linked_List* list){
	Node* node = NULL;
	node = create_Node(val);
	if (list->num_of_nodes == 0){
		insert_first_node(node, list);
	}
	else{
		list->first->prev = node;
		node->next = list->first;
		list->first = node;
		list->num_of_nodes++;
	}
}

void add_to_end_of_list(int val, Linked_List* list){
	Node* node = NULL;
	node = create_Node(val);
	if (list->num_of_nodes == 0){
		insert_first_node(node, list);
	}
	else{
		list->last->next = node;
		node->prev = list->last;
		list->last = node;
		list->num_of_nodes++;
	}
}

int add_after(int new_val, int existing_val, Linked_List* list){
	Node* new_node = NULL;
	Node* exisisting_node= NULL;
	int i = 0;
	int index = index_of_val_in_list(existing_val, list);
	if (index == -1){
		terminate_list(list);
		return ERROR_INVALID_VALUE;
	}
	if (index == list->num_of_nodes - 1) {
		add_to_end_of_list(new_val, list);
		return 0;
	}
	exisisting_node = list->first;
	for (i = 0; i < index; i++) {
		exisisting_node = exisisting_node->next;
	}
	new_node = create_Node(new_val);
	new_node->next = exisisting_node->next;
	new_node->prev = exisisting_node;
	exisisting_node->next->prev = new_node;
	exisisting_node->next = new_node;
	list->num_of_nodes++;
	return 0;
}

void terminate_list(Linked_List* list){
	while (list->num_of_nodes != 0) {
		delete_element_index_from_list(0, list);
	}
	free(list);
}

void print_list(Linked_List* list) {
	Node* node = NULL;
	int i = 0;
	if (list->num_of_nodes == 0) {
		printf("[]\n");
		return;
	}
	node = list->first;
	printf("[");
	for (i = 0; i < list->num_of_nodes-1; i++) {
		printf("%d, ", node->val);
		node = node->next;
	}
	printf("%d]\n", node->val);
}

int index_of_val_in_list(int val, Linked_List* list) {
	int i = 0;
	Node* node = NULL;
	if (list->num_of_nodes == 0) {
		return -1;
	}
	node = list->first;
	for (i = 0; i < list->num_of_nodes; i++) {
		if (node->val == val) {
			return i;
		}
		node = node->next;
	}
	return -1;
}
int delete_element_index_from_list(int index, Linked_List* list) {
	int i = 0;
	Node* node = NULL;
	if (index >= list->num_of_nodes || index < 0) {
		terminate_list(list);
		return ERROR_INVALID_INDEX;
	}
	if (list->num_of_nodes == 1) {
		free(list->first);
		list->first = NULL;
		list->last = NULL;
		list->num_of_nodes = 0;
		return 0;
	}
	if (index == 0) {
		list->first = list->first->next;
		free(list->first->prev);
		list->first->prev = NULL;
		list->num_of_nodes--;
		return 0;
	}
	if (index == list->num_of_nodes - 1) {
		list->last = list->last->prev;
		free(list->last->next);
		list->last->next = NULL;
		list->num_of_nodes--;
		return 0;
	}
	node = list->first;
	for (i = 0; i < index; i++) {
		node = node->next;
	}
	node->prev->next = node->next;
	node->next->prev = node->prev;
	free(node);
	list->num_of_nodes--;
	return 0;
}

