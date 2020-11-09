#include "stdio.h"
#include "stdlib.h"

/*
* 解題思路：
* 每個num都共享*2的次數，也就是bit左移的次數，例如[4, 5]，則兩者共同左移兩次就可以了
* 又例如[4, 9]，則9需要左移3次，其中的兩次可以和4共用，因此是由陣列中最大的數所dominate
* 並且每個num中的1 bit都不會憑空出現 例如[7, 9]看成bitstring = ["111", "1001"]，總共出現5個1，這5個1一定不會憑空出現，故每個1都需要一次add operation
* 所以答案就是 最大的數需要的*2次數(即最左邊的bit是第幾位) + 幾個1
*/
int minOperations(int *nums, int numsSize)
{
    int maximum = nums[0];
    int cnt = 0;
    for (int i = 0; i < numsSize; ++i)
    {
        maximum = (maximum < nums[i]) ? nums[i] : maximum;
        cnt += __builtin_popcount(nums[i]);
    }

    int double_time = (maximum > 0) ? (sizeof(int) << 3) - 1 - __builtin_clz(maximum) : 0;
    // printf("%d\n", maximum);
    // printf("%d + %d + %d = %d\n", double_time, cnt, numsSize, double_time + cnt);
    return double_time + cnt;
}

int main()
{
    int a[] = {3, 2, 2, 4};
    int size = 4;

    if (minOperations(a, size) == 7)
        puts("Success");
    else
        puts("Fail");
    return 0;
}