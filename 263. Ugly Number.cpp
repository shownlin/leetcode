#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:
    bool isUgly(int num)
    {
        if(!num)
            return false;
        int u[]{2, 3, 5};
        for(auto i : u)
        {
            while(!(num % i))
                num /= i;
        }
        if(num == 1)
            return true;
        return false;
    }
};

/*
// stack-overflow版本，不可用
class Solution
{
public:
    static vector<int> tmp;
    const int u[3]{2, 3, 5};
    bool isUgly(int num)
    {
        if(find(tmp.begin(), tmp.end(), num)!= tmp.end())
            return true;
        for(auto i : u)
        {
            if(!(num % i))
            {
                num /= i;
                if(isUgly(num))
                {
                    tmp.push_back(num);
                    return true;
                }
            }
        }
        return false;
    }
};
vector<int> Solution::tmp {1};*/

int main()
{
    vector<pair<int, bool>> q{{6, true}, {8, true}, {14, false}};
    Solution sol;

    for (auto it : q)
    {
        cout << ((it.second == sol.isUgly(it.first)) ? "Success" : "Failure") << " ";
    }
    return 0;
}
