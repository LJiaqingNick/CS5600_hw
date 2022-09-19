#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
  int rc = fork();
  if (rc < 0) {
    // fork failed
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {
    // child process
    char* myargs[3];
    myargs[0] = strdup("ls");
    myargs[1] = strdup("./");
    myargs[2] = NULL;
    execl(myargs[0], myargs);
  } else {
    // parent process
  }
  return 0;
}