#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>

// Constants for how many iterations, the larger the number
// the more precious for the system call
#define ITERATIONS 1000000

int main(int argc, char* argv[]) {
  // Open the file first
  int fd = open("./test.txt",O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
  char character[1];
  // set up variables to recod time
  struct timeval start, end;

  // start the timer
  gettimeofday(&start, NULL);
  for (int n = 0; n < ITERATIONS; n++) {
    read(fd, character, 0);
  }
  // stop the timer
  gettimeofday(&end, NULL);

  close(fd);
  unsigned long int start_time = start.tv_sec * 1000000 + start.tv_usec;
  unsigned long int end_time = end.tv_sec * 1000000 + end.tv_usec;
  unsigned long int time_diff = end_time - start_time;
  double average_time = time_diff / (double) ITERATIONS;
  printf("Average system call to read is %f in microseconds\n", average_time);
  return 0;
}