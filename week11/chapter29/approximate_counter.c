#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#define NUM_CPUS 8
#define NUM_COUNTS 10000

typedef struct __counter_t {
  // global count
  int global;
  // global lock
  pthread_mutex_t glock;
  // per-CPU count
  int local[NUM_CPUS];
  // per-cpu locks
  pthread_mutex_t llock[NUM_CPUS];
  // update frequency
  int threshold;
} counter_t;

void init(counter_t* c, int _threshold) {
  c->threshold = _threshold;
  c->global = 0;
  pthread_mutex_init(&c->glock, NULL);
  for (int i = 0; i < NUM_CPUS; i++) {
    c->local[i] = 0;
    pthread_mutex_init(&c->llock[i], NULL);
  }
}

void update(counter_t* c, int threadID, int amt) {
  int cpu = threadID % NUM_CPUS;
  pthread_mutex_lock(&c->llock[cpu]);
  c->local[cpu] += amt;
  if (c->local[cpu] >= c->threshold) {
    // transfer the local to global
    pthread_mutex_lock(&c->glock);
    c->global += c->local[cpu];
    pthread_mutex_unlock(&c->glock);
    c->local[cpu] = 0;
  }
  pthread_mutex_unlock(&c->llock[cpu]);
}

// get the global amount
int get(counter_t* c) {
  pthread_mutex_lock(&c->glock);
  int val = c->global;
  pthread_mutex_unlock(&c->glock);
  return val;
}

typedef struct __arg_t {
  counter_t* c;
  int threadID;
} arg_t;

void* routine(void* arg) {
  arg_t* thread_arg = (arg_t*) arg;
  for (int i = 0; i < NUM_COUNTS; i++) {
    update(thread_arg->c, thread_arg->threadID, 1);
  }
  return NULL;
}


int main(int argc, char* argv[]) {
  struct timeval start, end;
  counter_t c;
  arg_t thread_args[NUM_CPUS];
  for (int i = 0; i < NUM_CPUS; i++) {
    thread_args[i].c = &c;
    thread_args[i].threadID = i;
  }
  init(&c, 1000);
  pthread_t threads[NUM_CPUS];
  gettimeofday(&start, NULL);
  for (int i = 0; i < NUM_CPUS; i++) {
    pthread_create(&threads[i], NULL, routine, (void *)&thread_args[i]);
  }
  for (int i = 0; i < NUM_CPUS; i++) {
    pthread_join(threads[i], NULL);
  }
  gettimeofday(&end, NULL);
  long double start_time = start.tv_sec + start.tv_usec * 1e-6;
  long double end_time = end.tv_sec + end.tv_usec * 1e-6;
  printf("Total time %Lf\n", (end_time - start_time));
  printf("Total count %d\n", get(&c));
  return 0;
}