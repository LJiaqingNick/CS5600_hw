/*
Calculate the single thread to increment the counter to 10000
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "count_without_lock.h"
#define NUM_COUNTS 10000

int main(int argc, char* argv[]) {
  struct timeval start, end;
  int i;
  counter_t* c = malloc(sizeof(counter_t));
  if (c == NULL) {
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  init(c);
  gettimeofday(&start, NULL);
  for (i = 0; i < NUM_COUNTS; i++) {
    increment(c);
  }
  gettimeofday(&end, NULL);
  long double start_time = start.tv_sec + start.tv_usec * 1e-6;
  long double end_time = end.tv_sec + end.tv_usec * 1e-6;
  printf("Total time %Lf\n", (end_time - start_time));
  printf("Total count %d\n", c->value);
  return 0;
}