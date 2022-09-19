#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>

#define ITERATIONS 100000

int main(int argc, char* argv[]) {
  struct timeval start, end;
  int fd1[2], fd2[2];
  char char_buff[2];
  if (pipe(fd1) < 0 || pipe(fd2) < 0) {
    fprintf(stderr, "pipe failed\n");
    exit(1);
  }
  int rc1 = fork();
  if (rc1 < 0) {
    // fork failed
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc1 == 0) {
    // child process
    for (int n = 0; n < ITERATIONS; n++) {
      write(fd1[1], "1", 1);
      read(fd2[0], char_buff, 1);
    }
  } else {
    // parent process
    gettimeofday(&start, NULL);
    for (int n = 0; n < ITERATIONS; n++) {
      read(fd1[0], char_buff, 1);
      write(fd2[1], "2", 1);
    }
    gettimeofday(&end, NULL);
    unsigned long int start_time = start.tv_sec * 1000000 + start.tv_usec;
    unsigned long int end_time = end.tv_sec * 1000000 + end.tv_usec;
    unsigned long int time_diff = end_time - start_time;
    double average_time = time_diff / (double) ITERATIONS;
    printf("Average Context switch time is %f in microseconds\n", average_time);
  }


  return 0;
}