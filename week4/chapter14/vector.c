#include <stdlib.h>
#include <stdio.h>

typedef struct vector {
	int* data;
	int size;
	int capacity;
}vector_t;

vector_t* makeVector(int _capacity) {
	vector_t* vector = (vector_t*)malloc(sizeof(vector_t));
	vector->data = (int*)malloc(sizeof(int) * _capacity);
	vector->size = 0;
	vector->capacity = _capacity;
	return vector;
}

int resize(vector_t* vector, int newCap) {
	vector->data = realloc(vector->data, sizeof(int) * newCap);
	vector->capacity = newCap;
	return 1;
}

int push_back(vector_t* vector, int element) {
	if (vector->size == vector->capacity) {
		int newCap = vector->size + 1;
		resize(vector, newCap);
	}
	vector->data[vector->size] = element;
	vector->size += 1;
	return 1;
}


void print(vector_t* vector) {
	for (int i = 0; i < vector->size; i++) {
		printf("%d", vector->data[i]);
	}
	printf("\n");
}

void freeVector(vector_t* vector) {
	if (vector->data != NULL) {
		free(vector->data);
	}
	free(vector);
}

int main(int argc, char* argv[]) {
	vector_t* vector = makeVector(1);
	push_back(vector, 6);
	push_back(vector, 5);
	push_back(vector, 4);
	push_back(vector, 3);
	push_back(vector, 2);
	push_back(vector, 1);
	print(vector);
	freeVector(vector);
	return 0;
}







