#include <iostream>
#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

class ZeroEvenOdd
{
private:
    int n;
    int curr;
    mutex m;
    condition_variable cv;
    bool zero_printed;

public:
    ZeroEvenOdd(int n) : n(n), curr(0), zero_printed(false)
    {
    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber)
    {
        while (curr < n)
        {
            unique_lock<mutex> l(m);
            cv.wait(l, [this] { return !zero_printed; });
            if (curr < n)
                printNumber(0);
            zero_printed = true;
            cv.notify_all();
            this_thread::yield();
        }
        zero_printed = true;
        cv.notify_all();
    }

    void even(function<void(int)> printNumber)
    {
        while (curr < n)
        {
            unique_lock<mutex> l(m);
            cv.wait(l, [this] { return (curr & 1) == 1 && zero_printed; });
            if (curr == n)
                break;
            printNumber(++curr);
            zero_printed = false;
            cv.notify_all();
            this_thread::yield();
        }
    }

    void odd(function<void(int)> printNumber)
    {
        while (curr < n)
        {
            unique_lock<mutex> l(m);
            cv.wait(l, [this] { return (curr & 1) == 0 && zero_printed; });
            if (curr == n)
                break;
            printNumber(++curr);
            zero_printed = false;
            cv.notify_all();
            this_thread::yield();
        }
    }
};

void printNumber(int x)
{
    cout << x;
}

int main(int argc, char *argv[])
{
    ZeroEvenOdd q(5);
    thread t1(&ZeroEvenOdd::zero, &q, printNumber);
    thread t2(&ZeroEvenOdd::even, &q, printNumber);
    thread t3(&ZeroEvenOdd::odd, &q, printNumber);
    t1.join();
    t2.join();
    t3.join();
    return 0;
}