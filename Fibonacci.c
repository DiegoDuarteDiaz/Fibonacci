#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include <stdbool.h>

// Metodo para realizar el calculo Fibunacci
unsigned long long fib(unsigned long long n)
{
    // Cambiamos variables int por unsigned long 
    // para almacenar enteros largos
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

// Metodo para calcular los factores de los numeros
void Factors(unsigned long long n)
{
    bool firstNumber = true;
    if (n == 1)
    {
        printf("1\n");
        return;
    }
    while (n % 2 == 0)
    {
        if (firstNumber == false)
        {
            printf(" x ");
        }
        else
        {
            firstNumber = false;
        }
        printf("2");
        n = n / 2;
    }
    int aux = sqrtl(n);
    #pragma parallel for shared(n)
    for (int i = 3; i <= aux; i += 2)
    {
        while (n % i == 0)
        {
            if (firstNumber == false)
            {
                printf(" x ");
            }
            else
            {
                firstNumber = false;
            }
            printf("%d", i);
            n = n / i;
        }
    }
    if (n > 2)
    {
        if (firstNumber == false)
        {
            printf(" x ");
        }
        else
        {
            firstNumber = false;
        }
        printf("%llu", n);
    }
    printf("\n");
}

// Metodo para Calcular el resultado 
void CalculateResult(int n)
{
    unsigned long long result;
    
    #pragma omp parallel
    {
        #pragma omp single
        {
            result = fib(unsigned long long(n));
            printf("n: %d - valor: %llu - facotres: ", n, result);
            Factors(result);
        }
    }
    printf("Result in %d\n", result);
}

// Metodo Main del script
int main(int argc, char **argv)
{
    int n;
    char *a = argv[1];
    n = atoi(a);
    for (int i = 1; i<= n; i++)
    {
        CalculateResult(i);
    }
}