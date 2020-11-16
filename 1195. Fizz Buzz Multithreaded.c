#include "stdio.h"
#include "stdlib.h"
#include "pthread.h"
#define printFizz() printf("fizz ")
#define printBuzz() printf("buzz ")
#define printFizzBuzz() printf("fizzbuzz ")
#define printNumber(x) printf("%d ", (x))

typedef struct
{
    int n;
    int cur;
    pthread_mutex_t *fizz_mutex;
    pthread_mutex_t *buzz_mutex;
    pthread_mutex_t *fizzbuzz_mutex;
    pthread_mutex_t *number_mutex;
} FizzBuzz;

FizzBuzz *fizzBuzzCreate(int n)
{
    FizzBuzz *obj = (FizzBuzz *)malloc(sizeof(FizzBuzz));
    obj->n = n;
    obj->cur = 0;

    obj->fizz_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(obj->fizz_mutex, NULL);
    pthread_mutex_lock(obj->fizz_mutex);

    obj->buzz_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(obj->buzz_mutex, NULL);
    pthread_mutex_lock(obj->buzz_mutex);

    obj->fizzbuzz_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(obj->fizzbuzz_mutex, NULL);
    pthread_mutex_lock(obj->fizzbuzz_mutex);

    obj->number_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(obj->number_mutex, NULL);
    return obj;
}

// printFizz() outputs "fizz".
void fizz(FizzBuzz *obj)
{
    while (obj->cur < obj->n)
    {
        pthread_mutex_lock(obj->fizz_mutex);
        if (obj->cur % 3 == 0 && obj->cur % 5 != 0)
        {
            printFizz();
            pthread_mutex_unlock(obj->number_mutex);
        }
    }
    pthread_exit(NULL);
}

// printBuzz() outputs "buzz".
void buzz(FizzBuzz *obj)
{
    while (obj->cur < obj->n)
    {
        pthread_mutex_lock(obj->buzz_mutex);
        if (obj->cur % 5 == 0 && obj->cur % 3 != 0)
        {
            printBuzz();
            pthread_mutex_unlock(obj->number_mutex);
        }
    }
    pthread_exit(NULL);
}

// printFizzBuzz() outputs "fizzbuzz".
void fizzbuzz(FizzBuzz *obj)
{
    while (obj->cur < obj->n)
    {
        pthread_mutex_lock(obj->fizzbuzz_mutex);
        if ((obj->cur % 3 == 0) && (obj->cur % 5 == 0))
        {
            printFizzBuzz();
            pthread_mutex_unlock(obj->number_mutex);
        }
    }
    pthread_exit(NULL);
}

// You may call global function `void printNumber(int x)`
// to output "x", where x is an integer.
void number(FizzBuzz *obj)
{
    while (obj->cur < obj->n)
    {
        pthread_mutex_lock(obj->number_mutex);
        if (obj->cur < obj->n)
        {
            ++(obj->cur);
            if ((obj->cur % 3 == 0) && (obj->cur % 5 == 0))
                pthread_mutex_unlock(obj->fizzbuzz_mutex);
            else if (obj->cur % 3 == 0)
                pthread_mutex_unlock(obj->fizz_mutex);
            else if (obj->cur % 5 == 0)
                pthread_mutex_unlock(obj->buzz_mutex);
            else
            {
                printNumber(obj->cur);
                pthread_mutex_unlock(obj->number_mutex);
            }
        }
    }
    pthread_mutex_unlock(obj->fizz_mutex);
    pthread_mutex_unlock(obj->buzz_mutex);
    pthread_mutex_unlock(obj->fizzbuzz_mutex);
    pthread_exit(NULL);
}

void fizzBuzzFree(FizzBuzz *obj)
{
    pthread_mutex_unlock(obj->fizz_mutex);
    pthread_mutex_unlock(obj->buzz_mutex);
    pthread_mutex_unlock(obj->fizzbuzz_mutex);
    pthread_mutex_destroy(obj->fizz_mutex);
    pthread_mutex_destroy(obj->buzz_mutex);
    pthread_mutex_destroy(obj->fizzbuzz_mutex);
    pthread_mutex_destroy(obj->number_mutex);
    free(obj->fizz_mutex);
    free(obj->buzz_mutex);
    free(obj->fizzbuzz_mutex);
    free(obj->number_mutex);
    free(obj);
}

int main()
{
    pthread_t t1, t2, t3, t4;
    FizzBuzz *f = fizzBuzzCreate(15);
    pthread_create(&t1, NULL, number, f);
    pthread_create(&t2, NULL, fizz, f);
    pthread_create(&t3, NULL, buzz, f);
    pthread_create(&t4, NULL, fizzbuzz, f);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    fizzBuzzFree(f);
    return 0;
}