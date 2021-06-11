#ifndef LINKED_LIST
#define LINKED_LIST

#define ERROR_INVALID_INDEX -1
#define ERROR_INVALID_VALUE -2


typedef struct Node {
	int val;
	struct Node* prev;
	struct Node* next;
} Node;

typedef struct Linked_List {
	int num_of_nodes;
	struct Node* first;
	struct Node* last;
} Linked_List;

Linked_List* create_emplty_Linked_List();

int print_index( int val, Linked_List* list );

void add_to_start_of_list(int val, Linked_List* list);

void add_to_end_of_list(int val, Linked_List* list);

int add_after(int new_val, int existing_val, Linked_List* list);

void terminate_list(Linked_List* list);

void print_list(Linked_List* list);


int delete_element_index_from_list(int index, Linked_List* list);
#endif
