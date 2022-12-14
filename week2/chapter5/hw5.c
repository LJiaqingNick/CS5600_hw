#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
  printf("This is before the fork (pid:%d)\n", (int) getpid());
  int rc = fork();
  if (rc < 0) {
    // fork failed
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {
    // child process
    pid_t result = wait(NULL);
    printf("wait return %d\n", result);
    printf("hello, I am child (pid:%d)\n", (int) getpid());
  } else {
    // parent process
    printf("hello, I am parent (pid:%d)\n", (int) getpid());
  }
  return 0;
}