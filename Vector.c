#include<stdio.h>
#include<stdlib.h>

#include "Vector.h"


//create vector <x,y>
vec* vector(int x, int y)
{
	vec* return_vector = (vec*)malloc(sizeof(vec));

	if (return_vector)
	{
		return_vector->x = x;
		return_vector->y = y;
	}

	return return_vector;
}

//deep copy of pointer of vec
vec* copyVector(vec* v)
{
	vec* return_vector = (vec*)malloc(sizeof(vec));
	
	if (return_vector)
	{
		return_vector->x = v->x;
		return_vector->y = v->y;
	}

	return return_vector;

}
//delete dynamic allocation of vector
void deleteVector(vec* v)
{
	free(v);
}



//print out the vector<x,y>
void printVector(vec* v)
{
	printf("x:%d y:%d\n", v->x, v->y);

}