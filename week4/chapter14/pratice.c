#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
	char* src = "hello";
	char* dest = (char*)malloc(strlen(src) + 1);
	strcpy(dest, src);
	printf("%s\n", dest);
	return 0;
}
