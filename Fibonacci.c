#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int fib(int n){
    int i;
    int j;
    if(n<2)
    {
        return n;
    }
    else
    {
        #pragma omp task shared(i)
        i=fib(n-1);
        #pragma omp task shared(j)
        j=fib(n-2);
        #pragma omp taskwait
        return i+j;
    }
}