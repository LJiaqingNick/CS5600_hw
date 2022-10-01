#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	int* array = (int*)malloc(sizeof(100));
	array[100] = 0;
	free(array);
	return 0;
}
