#pragma once
#include <stddef.h>

typedef enum {
	INT,
	CHAR,
	VECTOR

}DataType;
//DataType:enum for generic Node

typedef struct Node {
	DataType type;
	size_t size;
	void* data;
	
	struct Node* Next;
}Node;
//Node:

void NodeAddStart(Node** n, void* data);
Node* NodeCreate(void* data, DataType type);
Node* NodePush(Node* n, void* data);
void NodePrintList(Node* n);
void NodeDelete(Node*,Node*);
