#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    uint32_t reverseBits(uint32_t n)
    {
        uint32_t res = 0u;
        for (int i = 0; i < 32; ++i)
        {
            res = (res << 1) | (n & 1);
            n >>= 1;
        }
        return res;
    }
};

int main()
{
    Solution sol;
    vector<pair<uint32_t, uint32_t>> q{{43261596u, 964176192u}, {4294967293u, 3221225471u}};
    for(auto e:q)
    {
        cout << (e.second == sol.reverseBits(e.first)) << endl;
    }
    return 0;
}