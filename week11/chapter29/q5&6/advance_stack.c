#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#define MAX_INSERT 1000000

typedef struct __node_t {
  int key;
  struct __node_t* prev;
  pthread_mutex_t lock;
} node_t;

typedef struct __stack_t {
  node_t* tail;
  pthread_mutex_t lock;
  int size;
} stack_t;

node_t* node_init(int _key) {
  node_t* new = malloc(sizeof(node_t));
  if (new == NULL) {
    perror("malloc");
    return NULL;
  }
  new->key = _key;
  new->prev = NULL;
  pthread_mutex_init(&new->lock, NULL);
  return new;
}

void stack_init(stack_t* t) {
  t->tail = NULL;
  t->size = 0;
  pthread_mutex_init(&t->lock, NULL);
}

void push(stack_t* t, int _key) {
  node_t* new = node_init(_key);
  if (new ==NULL) {
    return;
  }
  pthread_mutex_lock(&t->lock);
  new->prev = t->tail;
  t->tail = new;
  t->size++;
  pthread_mutex_unlock(&t->lock);
  return;
}

int pop(stack_t* t){
  if (t->size == 0) {
    perror("empty can't pop");
    return -1;
  }
  int val;
  node_t* temp;
  pthread_mutex_lock(&t->lock);
  val = t->tail->key;
  temp = t->tail;
  t->tail = t->tail->prev;
  t->size--;
  pthread_mutex_unlock(&t->lock);
  free(temp);
  return val;
}

void* routine_push(void* arg) {
  stack_t* t = (stack_t*) arg;
  for (int i = 0; i < MAX_INSERT; i++) {
    push(t, i);
  }
  return NULL;
}

void* routine_pop(void* arg) {
  stack_t* t = (stack_t*) arg;
  for (int i = 0; i < MAX_INSERT; i++) {
    pop(t);
  }
  return NULL;
}

int main(int argc, char* argv[]) {
  int num_thread = atoi(argv[1]);
  pthread_t threads[num_thread];
  struct timeval start, end;
  stack_t t;
  stack_init(&t);
  gettimeofday(&start, NULL);
  for (int i = 0; i < num_thread; i++) {
    pthread_create(&threads[i], NULL, routine_push, (void*)&t);
  }
  for (int i = 0; i < num_thread; i++) {
    pthread_join(threads[i], NULL);
  }
  gettimeofday(&end, NULL);
  long double start_time = start.tv_sec + start.tv_usec * 1e-6;
  long double end_time = end.tv_sec + end.tv_usec * 1e-6;
  long double total_time = end_time - start_time;
  printf("Stack size is %d\n", t.size);
  printf("Total time %Lf\n", total_time);
  printf("Average thread_time %Lf\n", total_time/num_thread);
  gettimeofday(&start, NULL);
  for (int i = 0; i < num_thread; i++) {
    pthread_create(&threads[i], NULL, routine_pop, (void*)&t);
  }
  for (int i = 0; i < num_thread; i++) {
    pthread_join(threads[i], NULL);
  }
  gettimeofday(&end, NULL);
  start_time = start.tv_sec + start.tv_usec * 1e-6;
  end_time = end.tv_sec + end.tv_usec * 1e-6;
  total_time = end_time - start_time;
  printf("--------------------------------------------------\n");
  printf("Stack size is %d\n", t.size);
  printf("Total time to pop is %Lf\n", total_time);
  printf("Average thread_time to pop is %Lf\n", total_time/num_thread);
  return 0;
}