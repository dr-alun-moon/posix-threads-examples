/* Summation.
   Example of multiple threads, combining results with join
*/
#include <stdio.h>

#include <pthread.h>

struct sum_part {
    int from, to;
    int sum;
};

/* thread worker:
   sums numbers over a range
*/
void *sumrange(void * param) {
    struct sum_part *sum = (struct sum_part*)param;
    int n;
    sum->sum = 0;
    for( n=sum->from ; n < sum->to ; n++ )
        sum->sum += n;
    return (void*)sum;
}

int main ( int argc, char *argv[] ) {
    struct sum_part low,high;
    struct sum_part *resA, *resB;
    pthread_t a,b;

    low.from =  0 ; 
    low.to   = 10 ;
    high.from= 10 ;
    high.to  = 20 ;

    pthread_create(&a, NULL, sumrange, (void*)&low);
    pthread_create(&b, NULL, sumrange, (void*)&high);

    pthread_join(a, (void**)&resA);
    pthread_join(b, (void**)&resB);

    printf("total is %3d\n", resA->sum+resB->sum);
}



