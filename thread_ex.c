/* Fork example */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int counter = 0;

void *increment(void *param)
{
    while(1) printf("incrementer %3d\n", ++counter);
}

void *decrement(void *param)
{
    while(1) printf("decrementer %3d\n", --counter);
}

int main ( int argc,  char *argv[] )
{
    pthread_t inc, dec;
    pthread_create(&inc, NULL, increment, NULL);
    pthread_create(&dec, NULL, decrement, NULL);

    while(1){;}

}

