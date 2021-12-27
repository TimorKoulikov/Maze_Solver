#include<stdio.h>
#include<stdlib.h>
#include "Node.h"
#include "Vector.h"
/*Function create a single node and return it
data must be lvalue*/
Node* NodeCreate(void* data,DataType type) {
	size_t effectivesize = 0;
	
	switch (type)
	{
		case(INT):
			effectivesize = sizeof(int);
			break;
		case(CHAR):
			effectivesize = sizeof(char);
			break;
		case(VECTOR):
			effectivesize = sizeof(vec);
			break;
		default:
			printf("NodeCreate() got wrong Type\n");
			exit(0);
	 }
	
	

	Node* tmp = (Node*)malloc(sizeof(Node));

	tmp->type = type;
	tmp->size = effectivesize;
	tmp->data = malloc(sizeof(effectivesize));
	tmp->data =data;

	tmp->Next = NULL;

	return tmp;
}
/*Function push node to end to the list
data must be lvalue*/
Node* NodePush(Node* n, void* data) {
		
	
	if (n->Next != NULL) 
	{
		return NodePush(n->Next, data);
	}

	n->Next = NodeCreate(data, n->type);
}

/*Function add node to the beginning of the list*/
void NodeAddStart(Node** n, void* data) {
	Node* newhead = NodeCreate(data, (*n)->type);
	newhead->Next = *n;
	*n =newhead;
}

/*Function prints list*/
void NodePrintList(Node* n) {
	if (n == NULL)
		return 0;

	switch (n->type) 
	{
		case(INT):
			printf("NodeData:%d\n",n->data);
			break;
		case(CHAR):
			printf("NodeData:%c\n", n->data);
			break;
		case(VECTOR):
			printf("[X:%d Y:%d]\n", ((int*)n->data)[0], ((int*)n->data)[1] );
		default:
			printf("NodePrintList() Nodepointer doesnt exists");
			exit(0);

	}
	
	
	NodePrintList(n->Next);

}

/*Function Delete spesific node from the list*/
void NodeDelete(Node* head,Node* next) {
	
	if (head == next)
	{
		free(head);
		return;
	}

	if (head->Next != next) NodeDelete(head->Next, next);
	else {
		head->Next = next->Next;
		free(next);
	}
	

}