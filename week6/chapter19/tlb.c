#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <sys/time.h>

int main(int argc, char* argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Need 2 parameters\n");
    exit(1);
  }

  long pageSize = sysconf(_SC_PAGESIZE);
  int jump = pageSize / sizeof(int);
  int numPages = atoi(argv[1]);
  int numTrials = atoi(argv[2]);

  int pid = getpid();
  if (pid <= 0) {
    fprintf(stderr, "Get pid failed\n");
    exit(1);
  }

  // bounding the cpu
  cpu_set_t set;
  CPU_SET(0, &set);
  int boundSuccess = sched_setaffinity(pid, sizeof(cpu_set_t), &set);
  if (boundSuccess != 0) {
    fprintf(stderr, "Bounding cpu failed\n");
    exit(1);
  }

  // initalize array with zero
  int* a = calloc(numPages, pageSize);
  if (a == NULL) {
    fprintf(stderr, "Array allocation go wrong\n");
    exit(1);
  }

  struct timeval tvStart, tvEnd;
  int i, j;
  // start the timer
  gettimeofday(&tvStart, NULL);
  for (j = 0; j < numTrials; j++) {
    for (i = 0; i < numPages * jump; i += jump) {
      a[i] += 1;
    }
  }
  // stop the timer
  gettimeofday(&tvEnd, NULL);
  double totalTime = (tvEnd.tv_sec - tvStart.tv_sec) * (double) 1000000 + tvEnd.tv_usec - tvStart.tv_usec;
  double averageTime = totalTime / (numTrials * numPages);
  printf("Average Time Per Access(ns) is %f, with total %d pages\n", averageTime * 1000, numPages);

  free(a);
  exit(0);
}