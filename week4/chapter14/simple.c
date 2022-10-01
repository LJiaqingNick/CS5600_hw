#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	int* b = (int*)malloc(sizeof(int));
	*b = 7;
	printf("number %d\n", *b);
	return 0;
}
