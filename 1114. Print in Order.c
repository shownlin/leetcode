#include "stdio.h"
#include "stdlib.h"
#include "pthread.h"

typedef struct
{
    // User defined data may be declared here.
    pthread_mutex_t *mutex1;
    pthread_mutex_t *mutex2;

} Foo;

Foo *fooCreate()
{
    Foo *obj = (Foo *)malloc(sizeof(Foo));

    // Initialize user defined data here.
    obj->mutex1 = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
    obj->mutex2 = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(obj->mutex1, NULL);
    pthread_mutex_init(obj->mutex2, NULL);

    pthread_mutex_lock(obj->mutex1);
    pthread_mutex_lock(obj->mutex2);
    return obj;
}

void printFirst()
{
    printf("first");
}

void printSecond()
{
    printf("second");
}

void printThird()
{
    printf("third");
}

void first(Foo *obj)
{

    // printFirst() outputs "first". Do not change or remove this line.
    printFirst();
    pthread_mutex_unlock(obj->mutex1);
    pthread_exit(NULL);
}

void second(Foo *obj)
{

    // printSecond() outputs "second". Do not change or remove this line.
    pthread_mutex_lock(obj->mutex1);
    printSecond();
    pthread_mutex_unlock(obj->mutex2);
    pthread_exit(NULL);
}

void third(Foo *obj)
{

    // printThird() outputs "third". Do not change or remove this line.
    pthread_mutex_lock(obj->mutex2);
    printThird();
    pthread_exit(NULL);
}

void fooFree(Foo *obj)
{
    // User defined data may be cleaned up here.
    pthread_mutex_unlock(obj->mutex1);
    pthread_mutex_unlock(obj->mutex2);
    pthread_mutex_destroy(obj->mutex1);
    pthread_mutex_destroy(obj->mutex2);
    free(obj->mutex1);
    free(obj->mutex2);
    free(obj);
}

int main()
{
    pthread_t t1, t2, t3;
    Foo *f = fooCreate();
    pthread_create(&t1, NULL, first, f);
    pthread_create(&t2, NULL, second, f);
    pthread_create(&t3, NULL, third, f);
    pthread_join(t1, NULL); // 等待子執行緒執行完成
    pthread_join(t2, NULL); // 等待子執行緒執行完成
    pthread_join(t3, NULL); // 等待子執行緒執行完成
    fooFree(f);
    return 0;
}