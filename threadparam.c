#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

int globvar = 6;

struct data {
  int value;
  int result;
};

void *simple_thr(void *arg) {
   struct data *param = (struct data*)arg;
   param->result = param->value *2 ;
   pthread_exit(arg);
}

int main(void) {
  pthread_t thread;
  int rc;

  struct data input;
  struct data *result;
  input.value = 42;

  rc = pthread_create(&thread, NULL, simple_thr, &input);
  assert(rc == 0);
  pthread_join(thread, (void**)&result);
  printf("input %d\n", input.value);
  printf("result %d\n", result->result);
  exit(0);
}

