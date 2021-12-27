#pragma once
#include <stddef.h>

#define SIZE_OF_VECTOR 2
typedef struct vec
{
	int x;
	int y;
}vec;

vec* vector(int x, int y);
vec* copyVector(vec* v);
void deleteVector(vec* v);
void printVector(vec* v);

