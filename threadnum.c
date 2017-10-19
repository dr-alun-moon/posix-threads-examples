#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

void *simple_thr(void *arg) {
  static int r;
  int *n = (int *)arg;
  r = *n *2;
  pthread_exit(&r);
}

int main(void) {
  pthread_t thread;
  int rc;
  int input = 42;
  int *result;

  rc = pthread_create(&thread, NULL, simple_thr, &input);
  assert(rc == 0);
  pthread_join(thread, (void**)&result);
  printf("%d \n " , *result);
  exit(0);
}

