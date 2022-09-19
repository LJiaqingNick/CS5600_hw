#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
  int x = 100;
  printf("x value is %d\n\n", x);
  int rc = fork();
  if (rc < 0) {
    // fork failed
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {
    // child process
    x++;
    printf("Increment 1 in child process we got %d\n", x);
  } else {
    // parent process
    x--;
    printf("Decrement 1 in parent process we got %d\n", x);
  }
  return 0;
}