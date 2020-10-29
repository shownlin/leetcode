#include <iostream>
#include <vector>
#include <tuple>
#include <unordered_map>

using namespace std;

class Solution
{
public:
    int subarraySum(vector<int> &nums, int k)
    {
        // 利用hash table來達成，建立prefix_len紀錄subarray的總和
        // 如果一個array從0到i的總和訂為s[i]，若i > j
        // 則s[i] - s[j]代表此array從下標i ~ j的subarray之總和
        // 所以此hash table的key為出現過的總和，利用當前總和減去k來查是不是有出現過這樣的subarray
        // 而value就是出現過幾次，代表有多少的prefix subarray可以跟當前遍歷到的數字形成一個全新的subarray
        // 且剛好總和為k( 因為0 ~ i總和是sum，0 ~ j總和是sum - k，那sum - (sum - k) = k符合要求 )
        unordered_map<int, int> prefix_sum{make_pair<int ,int>(0, 1)};
        int sum{0}, count{0};
        for(auto num : nums)
        {
            sum += num;
            if (prefix_sum.find(sum - k) != prefix_sum.end())
                count += prefix_sum[sum - k];
            ++prefix_sum[sum];
        }
        return count;
    }
};


int main()
{
    //陣列、K、答案
    vector<tuple<vector<int>, int, int>> q{{{1, 2, 2}, 2, 2}, {{1, 2, 3}, 3, 2}};
    Solution sol;

    for (auto it : q)
    {
        cout << ((get<2>(it) == sol.subarraySum(get<0>(it), get<1>(it))) ? "Success" : "Failure") << " ";
    }
    return 0;
}
