#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include <stdbool.h>

// Metodo para realizar el calculo Fibunacci
unsigned long long fib(unsigned long long n){
    // Cambiamos variables int por unsigned long para almacenar enteros largos
    unsigned long i;
    unsigned long j;
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

int main(int argc, char **argv){
    int n;
    int result;
    char *a = argv[1];
    n = atoi(a);

    #pragma omp parallel
    {
        #pragma omp single
        result = fib(n);
    }
    printf("Result in %d\n", result);
}