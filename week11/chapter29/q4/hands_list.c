#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#define MAX_INSERT 1000000

typedef struct __node_t {
  int key;
  struct __node_t* next;
  pthread_mutex_t lock;
} node_t;

typedef struct __list_t {
  node_t* head;
  pthread_mutex_t lock;
  int size;
} list_t;

void list_init(list_t* l) {
  l->head = NULL;
  l->size = 0;
  pthread_mutex_init(&l->lock, NULL);
}

node_t* node_init(int _key) {
  node_t* new = malloc(sizeof(node_t));
  if (new == NULL) {
    perror("malloc");
    return NULL;
  }
  new->key = _key;
  new->next = NULL;
  pthread_mutex_init(&new->lock, NULL);
  return new;
}


void list_insert(list_t* l, int _key) {
  node_t* new = node_init(_key);
  if (new == NULL) {
    return;
  }
  // lock the critical section
  pthread_mutex_lock(&l->lock);
  new->next = l->head;
  l->head = new;
  l->size++;
  pthread_mutex_unlock(&l->lock);
}

int list_lookup(list_t* l, int _key) {
  int rv = -1;
  node_t* current = l->head;
  pthread_mutex_lock(&current->lock);
  while (current != NULL) {
    if (current->key == _key) {
      rv = 0;
      break;
    }
    if (current->next == NULL) {
      break;
    }
    pthread_mutex_lock(&current->next->lock);
    pthread_mutex_unlock(&current->lock);
    current = current->next;
  }
  pthread_mutex_unlock(&current->lock);
  return rv;
}

void* routine_insert(void* arg) {
  list_t* l = (list_t*) arg;
  for (int i = 0; i < MAX_INSERT; i++) {
    list_insert(l, i);
  }
  return NULL;
}
void* routine_lookup(void* arg) {
  list_t* l = (list_t*) arg;
  list_lookup(l, -1);
  return NULL;
}

int main(int argc, char* argv[]) {
  int num_thread = atoi(argv[1]);
  pthread_t threads[num_thread];
  struct timeval start, end;
  list_t l;
  list_init(&l);
  // To meausre look time, gurantteed to find the last item in the llist
  list_insert(&l, -1);
  gettimeofday(&start, NULL);
  for (int i = 0; i < num_thread; i++) {
    pthread_create(&threads[i], NULL, routine_insert, (void*)&l);
  }
  for (int i = 0; i < num_thread; i++) {
    pthread_join(threads[i], NULL);
  }
  gettimeofday(&end, NULL);
  long double start_time = start.tv_sec + start.tv_usec * 1e-6;
  long double end_time = end.tv_sec + end.tv_usec * 1e-6;
  long double total_time = end_time - start_time;
  printf("Total time to insert is %Lf\n", total_time);
  printf("Average thread_time to insert is %Lf\n", total_time/num_thread);
  
  gettimeofday(&start, NULL);
  for (int i = 0; i < num_thread; i++) {
    pthread_create(&threads[i], NULL, routine_lookup, (void*)&l);
  }
  for (int i = 0; i < num_thread; i++) {
    pthread_join(threads[i], NULL);
  }
  gettimeofday(&end, NULL);
  start_time = start.tv_sec + start.tv_usec * 1e-6;
  end_time = end.tv_sec + end.tv_usec * 1e-6;
  total_time = end_time - start_time;
  printf("----------------------------------------------------\n");
  printf("After insert there are total %d\n", l.size);
  printf("Total time to lookup tail %Lf\n", total_time);
  printf("Average thread_time %Lf\n", total_time/num_thread);
  return 0;
}