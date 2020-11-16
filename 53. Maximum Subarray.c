#include "limits.h"

// 基本想法：Kadane演算法 (Dynamic Programming)
// 從nums[0]開始掃到nums[n-1]
// 每次累加一個數字nums[i]進來，如果總和變成負的，代表前面這串數字對於增加總和沒有幫助
// 因此要重新累計新的subarray，而總和是正的代表納入前面這串數字對於增加總和有幫助
// 可以繼續累計下去

int maxSubArray(int *nums, int numsSize)
{

    int sum = 0, answer = INT_MIN;
    for (int i = 0; i < numsSize; ++i)
    {
        sum += nums[i];

        if (answer < sum)
            answer = sum;

        if (sum < 0)
            sum = 0;
    }
    return answer;
}