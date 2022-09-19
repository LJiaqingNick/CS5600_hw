#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
  int fd[2];
  if (pipe(fd) < 0) {
    // pipe failed
    fprintf(stderr, "pipe failed\n");
    exit(1);
  }
  int rc1 = fork();
  if (rc1 < 0) {
    // fork failed
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc1 == 0) {
    // child1 process
    write(fd[1], "Hello, World!\n", 14);
    // close the pipe input
    close(fd[0]);
  } else {
    // parent process
    int rc2 = fork();
    if (rc2 < 0) {
      // fork failed
      fprintf(stderr, "fork failed\n");
      exit(1);
    } else if(rc2 == 0) {
      // child2 process
      char string[14];
      read(fd[0], string, 14);
      // close pipe output
      close(fd[0]);
      printf("%s", string);
    } else {
      // parent process
    }
  }
  return 0;
}