#include <stdio.h>
#include <stdlib.h>
#include < string.h>

int main(int argc, char* argv[]) {
	char* src = "hello";
	char* dst = (char*)malloc(sizeof(char) * 6)
	strcpy(dst, src);
	printf("%s\n", &dst);
	return 0;
}
