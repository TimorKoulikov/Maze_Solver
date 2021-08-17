#include<stdio.h>
#include<stdlib.h>
#include "Node.h"
//data must be lvalue
Node* NodeCreate(void* data,DataType type) {
	size_t effectivesize = 0;

	if (type == INT) {
		effectivesize = sizeof(int);
		
	}
	else if (type == CHAR) {
		effectivesize = sizeof(char);
	}
	else if (type == VECTOR) {
		effectivesize = sizeof(int)*2;	
	}

	Node* tmp = (Node*)malloc(sizeof(Node));
	tmp->type = type;
	tmp->size = effectivesize;
	tmp->data = malloc(sizeof(effectivesize));

	if (type == INT) {
		int* x = data;
		tmp->data =*x;

	}
	else if (type == CHAR) {
		char* x = data;
		tmp->data = *x;
	}
	else if (type==VECTOR) {
		int* x = data;
		tmp->data = x;
	}

	tmp->Next = NULL;
	return tmp;
}

void NodePush(Node* n, void* data) {
	Node* current = n;
	if (current->Next != NULL) {
		NodePush(current->Next, data);
	}
	else {
		current->Next = NodeCreate(data, current->type);
	}
}
void NodeAddStart(Node** n, void* data) {
	Node* newhead = NodeCreate(data, (*n)->type);
	newhead->Next = *n;
	*n =newhead;
}


void NodePrintList(Node* n) {
	if (n == NULL)
		return 0;
	if (n->type == INT) {
		printf("%d\n",(int)n->data);
	}
	else if (n->type == CHAR) {
		printf("%c\n", (char)n->data);
	}
	else if (n->type == VECTOR) {
		printf("[X:%d ", ((int*)n->data)[0]);
		printf("Y:%d]\n", ((int*)n->data)[1]);
	}
	
	NodePrintList(n->Next);

}
void NodeDelete(Node* head) {
	
	if (head->Next != NULL) {
		NodeDelete(head->Next);
	}
	//free(head->data);
	free(head);
	

}