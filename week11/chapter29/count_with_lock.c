#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#define NUM_THREADS 7 // 7 children thread with 1 parent thread total 8 thread
#define NUM_COUNTS 10000

typedef struct __counter_t {
  int value;
  pthread_mutex_t lock;
} counter_t;

void init(counter_t* c) {
  c->value = 0;
  pthread_mutex_init(&c->lock, NULL);
}

void increment(counter_t* c) {
  pthread_mutex_lock(&c->lock);
  c->value++;
  pthread_mutex_unlock(&c->lock);
}

void decrement(counter_t* c) {
  pthread_mutex_lock(&c->lock);
  c->value--;
  pthread_mutex_unlock(&c->lock);
}

int get(counter_t* c) {
  pthread_mutex_lock(&c->lock);
  int rc = c->value;
  pthread_mutex_unlock(&c->lock);
  return rc;
}

void* routine(void* arg) {
  counter_t* c = (counter_t*) arg;
  int i;
  for (i = 0; i < NUM_COUNTS; i++) {
    increment(c);
  }
  return NULL;
}



int main(int argc, char* argv[]) {
  struct timeval start, end;
  counter_t* c = (counter_t*)malloc(sizeof(counter_t));
  if (c == NULL) {
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  init(c);
  pthread_t thread_id[NUM_THREADS];
  gettimeofday(&start, NULL);
  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_create(&thread_id[i], NULL, routine, (void *)c);
  }
  for (int i = 0; i < NUM_COUNTS; i++) {
    increment(c);
  }
  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_join(thread_id[i], NULL);
  }
  gettimeofday(&end, NULL);
  long double start_time = start.tv_sec + start.tv_usec * 1e-6;
  long double end_time = end.tv_sec + end.tv_usec * 1e-6;
  printf("Total time %Lf\n", (end_time - start_time));
  printf("Total count %d\n", c->value);
  return 0;
}