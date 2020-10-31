#include "stdio.h"
#include "stdbool.h"

bool isPowerOfTwo(int n)
{
    return (n > 0) && !(n & (n - 1));
}

int main(int argc, char **argv)
{
    printf("%s\n", isPowerOfTwo(1) == 1 ? "Correct" : "Incorrect");
    printf("%s\n", isPowerOfTwo(16) == 1 ? "Correct" : "Incorrect");
    printf("%s\n", isPowerOfTwo(3) == 0 ? "Correct" : "Incorrect");
    printf("%s\n", isPowerOfTwo(4) == 1 ? "Correct" : "Incorrect");
    printf("%s\n", isPowerOfTwo(5) == 0 ? "Correct" : "Incorrect");
}