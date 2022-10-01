#include <stdlib.h>
#include <stdio.h>
#define MEGABYTE 1048576

int main(int argc, char* argv[]) {
	int totalMemory = atoi(argv[1]) * MEGABYTE;
	int* array = malloc(totalMemory);
	if (array == NULL) {
		printf("malloc filed\n");
		exit(1);
	}
	int i;
	while (1) {
		for (i = 0; i < totalMemory/sizeof(int); i++) {
			array[i] = i;
		}
	}
	return 0;
}
