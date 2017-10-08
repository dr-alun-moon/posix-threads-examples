/* Fork example */

#include <stdio.h>
#include <unistd.h>

int counter = 0;

void increment(void)
{
    while(1) printf("incrementer %3d\n", ++counter);
}

void decrement(void)
{
    while(1) printf("decrementer %3d\n", --counter);
}

int main ( int argc,  char *argv[] )
{
    pid_t process;
    process = fork();
    if( process ){
        printf("In parent, child id is %d\n",process);
        increment();
    }else{
        printf("In child\n");
        decrement();
    }
}
