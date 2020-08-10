#include <iostream>
#include <vector>
#include <unordered_map>

using std::cout;
using std::unordered_map;
using std::vector;

class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        unordered_map<int, int> tmp;
        for (int i = 0; i < nums.size(); ++i)
        {
            auto it = tmp.find(target - nums[i]);
            if (it!= tmp.end())
                return vector<int>{it->second, i};
            tmp[nums[i]] = i;
        }
        return nums;
    }
};

int main()
{
    vector<int> nums{2, 7, 11, 15};
    int target{9};
    Solution sol;
    vector<int> ans = sol.twoSum(nums, target);
    for (auto it = ans.begin(); it != ans.end();++it)
    {
        cout << *it << " ";
    }
    return 0;
}

