#pragma once
#include <stddef.h>
typedef enum {
	INT,
	CHAR,
	VECTOR

}DataType;
typedef struct Node {
	DataType type;
	size_t size;
	int data;
	
	struct Node* Next;
}Node;
void NodeAddStart(Node** n, void* data);
Node* NodeCreate(void* data, DataType type);
void NodePush(Node* n, void* data);
void NodePrintList(Node* n);
