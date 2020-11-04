#include <iostream>
#include <vector>

using namespace std;

class NumArray
{
private:
    vector<int> prefix_sum;

public:
    NumArray(vector<int> &nums)
    {
        prefix_sum.push_back(0);
        for (int num : nums)
            prefix_sum.push_back(prefix_sum.back() + num);
    }

    int sumRange(int i, int j)
    {
        return prefix_sum.at(j + 1) - prefix_sum.at(i);
    }
};

int main()
{
    vector<int> nums{-2, 0, 3, -5, 2, -1};
    vector<pair<int, int>> q{{0, 2}, {2, 5}, {0, 5}};
    vector<int> ans{1, -1, -3};
    NumArray sol{nums};
    for (int i = 0; i < q.size(); ++i)
    {
        cout << ((sol.sumRange(q[i].first, q[i].second) == ans.at(i))? "Success":"Fail") << endl;
    }
}