#include <iostream>
#include <functional>
#include <thread>
#include <mutex>

using namespace std;

class Foo
{
public:
    mutex l1, l2;
    Foo()
    {
        l1.lock();
        l2.lock();
    }

    void first(function<void()> printFirst)
    {
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        l1.unlock();
    }

    void second(function<void()> printSecond)
    {
        // printSecond() outputs "second". Do not change or remove this line.
        l1.lock();
        printSecond();
        l2.unlock();
    }

    void third(function<void()> printThird)
    {

        // printThird() outputs "third". Do not change or remove this line.
        l2.lock();
        printThird();
    }
};

void print_first()
{
    cout << "first";
}

void print_sceond()
{
    cout << "second";
}

void print_third()
{
    cout << "third";
}

int main(int argc, char * argv[])
{
    Foo q;
    thread t1(&Foo::first, &q, print_first);
    thread t2(&Foo::second, &q, print_sceond);
    thread t3(&Foo::third, &q, print_third);
    t1.join();
    t2.join();
    t3.join();
    return 0;
}