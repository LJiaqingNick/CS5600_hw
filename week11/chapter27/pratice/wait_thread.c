#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
  int a;
  int b;
} myarg_t;

typedef struct { int x; int y; } myret_t;

void* mythread(void *arg) {
  printf("Parameters are %d %d\n", ((myarg_t*)arg)->a, ((myarg_t*)arg)->b);
  myret_t* rvals = malloc(sizeof(myret_t));
  rvals->x = 1;
  rvals->y = 2;
  // myret_t oops;
  // oops.x = 1;
  // oops.x = 2;
  // return (void*) &oops;
  return (void*) rvals;
}

int main(int argc, char* argv[]) {
  pthread_t p;
  myret_t* rvals;
  myarg_t args = {10, 20};
  pthread_create(&p, NULL, mythread, &args);
  pthread_join(p, (void**) &rvals);
  printf("returned %d %d\n", rvals->x, rvals->y);
  free(rvals);
  return 0;
}