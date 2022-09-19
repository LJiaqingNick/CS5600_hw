#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
  int pid = (int) getpid();
  printf("This is before the fork (pid:%d)\n", pid);
  int rc = fork();
  if (rc < 0) {
    // fork failed
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {
    // child process
    printf("hello, I am child (pid:%d)\n", (int) getpid());
  } else {
    // parent process
    pid_t result = waitpid(rc, NULL, 0);
    printf("waitpid return %d\n", result);
    printf("hello, I am parent (pid:%d)\n", (int) getpid());
  }
  return 0;
}