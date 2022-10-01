#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	int* array = (int*)malloc(sizeof(100));
	free(array[50]);
	printf("%d\n", array[2]);
	return 0;
}
