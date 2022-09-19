#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
  int fd = open("./test.txt", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
  int rc = fork();
  if (rc < 0) {
    // fork failed
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {
    // child process
    // printf("Child open descriptor is %d\n", fd);
    write(fd, "world\n", strlen("world\n"));
  } else {
    // parent process
    // printf("Parent open descriptor is %d\n", fd);
    write(fd, "hello, ", 7);
  }
  return 0;
}