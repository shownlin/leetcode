#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

class Solution
{
public:
    int superEggDrop(int K, int N){
        vector<vector<int>> dp(K + 1, vector<int>(N + 1, 0));
        // dp[k][m] = N
        // k個雞蛋，m次實驗機會，最多可確定之樓層數
        // dp[k][1] = 1，無論幾顆雞蛋，只有一次實驗機會，僅能確定一層樓
        // dp[1][m] = m，從最低樓層開始測起，最多可試到m層樓
        // 分兩個case，若在第dp[k-1][t-1] + 1層丟一顆蛋
        // case 1: 若蛋破了，則知道在dp[k-1][t-1] + 1層以上全部都是breaking floor，但i以下的dp[k - 1][m - 1]層樓尚未分類
        //         但已知必可分類完成，因此整棟無限高的大樓都可以確定是屬於breaking或non-breaking floor
        // case 2: 若蛋沒破，則知道在dp[k-1][t-1] + 1層以下全部都是non-breaking floor，可以在繼續往樓上測得dp[k][m - 1]層樓的是屬於哪一種floor
        // case 1 若發生，非常好，無限高的樓層皆可被分類，但必須考慮最壞之情況，即case 2，才能計算所有情況下都能正確分類的層數為多少，故如下式：
        // dp[k - 1][m - 1] + dp[k][m - 1] + 1，蛋破則最多可測樓下dp[k - 1][m - 1]層，蛋沒破則往上測dp[k][m - 1]層，加上本層也算一層
        int m = 0;
        while (dp[K][m] < N)
        {
            ++m;
            for (int k = 1; k <= K; ++k)
            {
                dp[k][m] = dp[k - 1][m - 1] + dp[k][m - 1] + 1;
            }
        }
        return m;
    }

    int superEggDrop2(int K, int N){
        vector<vector<int>> m(K + 1, vector<int>(N + 1, INT_MAX));
        function<int(int, int)> dp = [&](int k, int n) {
        if (k <= 0)
            return 0;
        if (k == 1)
            return n;
        if (n <= 1)
            return n;
        int &ans = m[k][n];
        if (ans != INT_MAX)
            return ans;

        int lo = 1, hi = n + 1;
        while (lo < hi)
        {
            int mid = lo + (hi - lo) / 2;
            int broken = dp(k - 1, mid - 1);
            int unbroken = dp(k, n - mid);

            if (broken < unbroken)
                lo = mid + 1;
            else
                hi = mid;
        }
        ans = 1 + max(dp(k - 1, lo - 1), dp(k, n - lo));
        return ans;
    };

    return dp(K, N);
    }
};

int main()
{
    // 排列方式：K個雞蛋，N層樓，輸出答案
    vector<vector<int>> q{ { 1, 2 ,2}, { 2, 6 ,3}, { 3, 14 ,4} };
    Solution sol;

    for (auto it:q)
    {
        cout << ((it[2] == sol.superEggDrop(it[0], it[1])) ? "Success" : "Failure") << " ";
    }
    return 0;
}

