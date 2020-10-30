#include <iostream>
#include <functional>
#include <thread>
#include <mutex>

using namespace std;

class FooBar
{
private:
    int n;
    mutex m1, m2;

public:
    FooBar(int n)
    {
        this->n = n;
        m2.lock();
    }

    void foo(function<void()> printFoo)
    {

        for (int i = 0; i < n; i++)
        {

            // printFoo() outputs "foo". Do not change or remove this line.
            m1.lock();
            printFoo();
            m2.unlock();
        }
    }

    void bar(function<void()> printBar)
    {

        for (int i = 0; i < n; i++)
        {

            // printBar() outputs "bar". Do not change or remove this line.
            m2.lock();
            printBar();
            m1.unlock();
        }
    }
};

void print_Foo()
{
    cout << "foo";
}

void print_Bar()
{
    cout << "bar";
}

int main(int argc, char *argv[])
{
    FooBar q(3);
    thread t1(&FooBar::foo, &q, print_Foo);
    thread t2(&FooBar::bar, &q, print_Bar);
    t1.join();
    t2.join();

    return 0;
}