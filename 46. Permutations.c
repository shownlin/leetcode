#include "stdio.h"
#include "stdlib.h"
#include "memory.h"

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// 計算階乘：有幾種排列結果
int calPermuteSize(int numsSize)
{
    int i = 0;
    int iRetSize = 1;

    for (i = 1; i <= numsSize; i++)
    {
        iRetSize *= i;
    }

    return iRetSize;
}

// cnt用來計算目前已經有幾個答案了
void sub_permute(int **ans, int *cnt, int *nums, int i, int n)
{
    if (i == n)
    {
        ans[*cnt] = (int *)malloc(sizeof(int) * n);
        memcpy(ans[(*cnt)++], nums, sizeof(int) * n);
    }
    for (int j = i; j < n; ++j)
    {
        swap(&nums[i], &nums[j]);
        sub_permute(ans, cnt, nums, i + 1, n);
        swap(&nums[j], &nums[i]);
    }
}

// returnColumnSizes用來指定每一列的行寬，是一個一維陣列，但是用pointer to pointer包起來，要自己malloc裡面那一層
// 為什麼要用pointer to pointer的理由：
// 因為returnColumnSizes本身是call by value，如果直接對returnColumnSizes進行malloc並不會真正改變caller手上的那個指針
int **permute(int *nums, int numsSize, int *returnSize, int **returnColumnSizes)
{
    int num_per = calPermuteSize(numsSize);
    int **ans = (int **)malloc(sizeof(int *) * num_per);
    *returnColumnSizes = (int *)malloc(sizeof(int) * (num_per));
    int cnt = 0;
    sub_permute(ans, &cnt, nums, 0, numsSize);
    for (int i = 0; i < num_per; ++i)
        (*returnColumnSizes)[i] = numsSize;
    *returnSize = num_per;
    return ans;
}

int main()
{
    int nums[] = {1, 2, 3}, numsSize = 3;
    int returnSize, *returnColumnSizes;
    int **ans = permute(nums, numsSize, &returnSize, &returnColumnSizes);
    for (int i = 0; i < returnSize; ++i)
    {
        for (int j = 0; j < returnColumnSizes[i]; ++j)
            printf("%d ", ans[i][j]);
        printf("\n");
        free(ans[i]);
    }
    free(ans);
    free(returnColumnSizes);
}