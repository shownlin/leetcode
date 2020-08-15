#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution
{
public:
    int longestAwesome(string s)
    {
        unordered_map<int, int> status;
        status[0] = -1;
        int mask = 0;
        int ans = 1;
        for (int i = 0; i < s.length(); ++i)
        {
            mask ^= 1 << (s[i] - (int)'0');
            auto even = status.find(mask);
            if (even != status.end())
                ans = max(ans, i - even->second);
            else
                status[mask] = i;
            for (int j = 0; j < 10; ++j)
            {
                auto odd = status.find(mask ^ 1 << j);
                if (odd != status.end())
                    ans = max(ans, i - odd->second);
            }
        }
        return ans;
    }
};

int main()
{
    vector<pair<string, int>> q{{"3242415", 5}, {"12345678", 1}, {"213123", 6}, {"00", 2}, {"350844", 3}, {"373781", 5}};
    Solution sol;

    for (auto it : q)
    {
        cout << ((it.second == sol.longestAwesome(it.first)) ? "Success" : "Failure") << " ";
    }
    return 0;
}
