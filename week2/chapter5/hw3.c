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
    exit(1);
  }
  int rc = fork();
  if (rc < 0) {
    // fork failed
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {
    // child process
    printf("Hello, ");
    write(fd[1], "1", 1);
  } else {
    // parent process
    char charBuff[2];
    read(fd[0], charBuff, 1);
    printf("goodbye!\n");
  }
  return 0;
}