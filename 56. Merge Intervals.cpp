#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:
    vector<vector<int>> merge(vector<vector<int>> &intervals)
    {
        if (intervals.size() < 1)
            return {};
        vector<vector<int>> res;
        sort(intervals.begin(), intervals.end(), [](vector<int> &a, vector<int> &b) { return a[0] < b[0]; });
        res.emplace_back(intervals[0]);
        for (int i = 1; i < intervals.size(); ++i)
        {
            if (res.back()[1] >= intervals[i][0])
                res.back()[1] = (res.back()[1] < intervals[i][1]) ? intervals[i][1] : res.back()[1];
            else
                res.emplace_back(intervals[i]);
        }

        for(auto i : res)
            cout << i[0] << " " << i[1] << endl;
        return res;
    }
};

int main()
{
    vector<vector<int>> q{{1, 3}, {2, 6}, {8, 10}, {15, 18}};
    vector<vector<int>> ans{{1, 6}, {8, 10}, {15, 18}};
    // vector<vector<int>> q{{1, 4}, {4, 5}};
    // vector<vector<int>> ans{{1, 5}};
    Solution sol;
    auto my_ans = sol.merge(q);

    bool flag = 1;
    for (int i = 0; i < ans.size(); ++i)
    {
        if (ans[i] != my_ans[i])
            flag = 0;
    }
    if (ans.size() != my_ans.size())
        flag = 0;
    cout << (flag ? "Success" : "Fail") << endl;

}