#include "stdio.h"
#include "stdlib.h"
#include "memory.h"
#define element_n 3
#define add(x, y) ((x) + (y))

void merge(int *nums1, int nums1Size, int m, int *nums2, int nums2Size, int n)
{
    // printf("nums1Size = %d, m = %d nums2Size = %d, n = %d\n", nums1Size, m, nums2Size, n);
    --m;
    --n;
    for (int i = nums1Size - 1; (m >= 0) && (n >= 0); --i)
    {
        if (nums1[m] > nums2[n])
            nums1[i] = nums1[m--];
        else
            nums1[i] = nums2[n--];
    }
    if (n >= 0)
        memcpy(nums1, nums2, sizeof(int) * (n + 1));
}

int main()
{
    int nums1[] = {4, 5, 6, 0, 0, 0}, nums2[] = {1, 2, 3};
    merge(nums1, add(element_n, 3), element_n, nums2, sizeof(nums2) / sizeof(int), sizeof(nums2) / sizeof(int));
    for (int i = 0; i < add(element_n, 3); ++i)
        printf("%d ", nums1[i]);
    return 0;
}